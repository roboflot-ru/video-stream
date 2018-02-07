#include "RaspberryEncoder.h"

#include <iostream>

extern "C" {
#include "bcm_host.h"
}

#define VIDEO_ENCODE_PORT_IN 200
#define VIDEO_ENCODE_PORT_OUT 201

RaspberryEncoder::RaspberryEncoder(unsigned width, unsigned height, unsigned bitrate, unsigned fps, PacketHandler& packetHandler)
  : Width(width)
  , Height(height)
  , Bitrate(bitrate)
  , Fps(fps)
  , Handler(packetHandler)
{
  bcm_host_init();

  ILCLIENT_T* client = ilclient_init();
  OMX_Init();
  ilclient_create_component(client, &VideoEncode, "video_encode",
    (ILCLIENT_CREATE_FLAGS_T)(ILCLIENT_DISABLE_ALL_PORTS |
    ILCLIENT_ENABLE_INPUT_BUFFERS |
    ILCLIENT_ENABLE_OUTPUT_BUFFERS));

  OMX_PARAM_PORTDEFINITIONTYPE def;
  memset(&def, 0, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
  def.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
  def.nVersion.nVersion = OMX_VERSION;
  def.nPortIndex = VIDEO_ENCODE_PORT_IN;

  OMX_GetParameter(ILC_GET_HANDLE(VideoEncode), OMX_IndexParamPortDefinition, &def);

  def.format.video.nFrameWidth = Width;
  def.format.video.nFrameHeight = Height;
  def.format.video.xFramerate = Fps << 16;
  def.format.video.nSliceHeight = def.format.video.nFrameHeight;
  def.format.video.nStride = def.format.video.nFrameWidth;
  def.format.video.eColorFormat = OMX_COLOR_FormatYUV420PackedPlanar;

  int r = OMX_SetParameter(ILC_GET_HANDLE(VideoEncode),
    OMX_IndexParamPortDefinition,
    &def);

  OMX_VIDEO_PARAM_PORTFORMATTYPE format;
  memset(&format, 0, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
  format.nSize = sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE);
  format.nVersion.nVersion = OMX_VERSION;
  format.nPortIndex = VIDEO_ENCODE_PORT_OUT;
  format.eCompressionFormat = OMX_VIDEO_CodingAVC;

  r = OMX_SetParameter(ILC_GET_HANDLE(VideoEncode),
    OMX_IndexParamVideoPortFormat,
    &format);


  OMX_VIDEO_PARAM_BITRATETYPE bitrateType;
  memset(&bitrateType, 0, sizeof(OMX_VIDEO_PARAM_BITRATETYPE));
  bitrateType.nSize = sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE);
  bitrateType.nVersion.nVersion = OMX_VERSION;
  bitrateType.eControlRate = OMX_Video_ControlRateVariable;
  bitrateType.nTargetBitrate = Bitrate;
  bitrateType.nPortIndex = VIDEO_ENCODE_PORT_OUT;
  r = OMX_SetParameter(ILC_GET_HANDLE(VideoEncode),
    OMX_IndexParamVideoBitrate, &bitrateType);


  ilclient_change_component_state(VideoEncode, OMX_StateIdle);
  ilclient_enable_port_buffers(VideoEncode, VIDEO_ENCODE_PORT_IN, NULL, NULL, NULL);
  ilclient_enable_port_buffers(VideoEncode, VIDEO_ENCODE_PORT_OUT, NULL, NULL, NULL);
  ilclient_change_component_state(VideoEncode, OMX_StateExecuting);
}

void RaspberryEncoder::Encode(const unsigned char* data, unsigned size)
{
  OMX_BUFFERHEADERTYPE* buf = ilclient_get_input_buffer(VideoEncode, VIDEO_ENCODE_PORT_IN, 1);
  if (!buf)
  {
    std::cout << "Failed to get input buffer " << std::endl;
    return;
  }

  buf->nFilledLen = size;
  memcpy(buf->pBuffer, data, buf->nFilledLen);
  OMX_ERRORTYPE err = OMX_EmptyThisBuffer(ILC_GET_HANDLE(VideoEncode), buf);
  if (err != OMX_ErrorNone)
  {
    std::cout << "Failed to empty input buffer, error " << err << std::endl;
    return;
  }

  OMX_BUFFERHEADERTYPE* out = ilclient_get_output_buffer(VideoEncode, VIDEO_ENCODE_PORT_OUT, 1);
  if (!out)
  {
    std::cout << "Failed to get output buffer " << std::endl;
    return;
  }

  err = OMX_FillThisBuffer(ILC_GET_HANDLE(VideoEncode), out);
  if (err != OMX_ErrorNone)
  {
    std::cout << "Failed to fill output buffer, error " << err << std::endl;
    return;
  }

  Handler.Handle(out->pBuffer, out->nFilledLen);
}
