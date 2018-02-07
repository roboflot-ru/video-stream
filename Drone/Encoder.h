#pragma once

class Encoder
{
public:
  virtual void Encode(const unsigned char* data, unsigned size) = 0;
};
