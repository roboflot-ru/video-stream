
# video-stream


# Install on board

    git clone https://github.com/roboflot-ru/video-stream.git video
    cd video
    chmod +x install_drone_depends.sh
    ./install_drone_depends.sh



# Autostart on boot

Создаем файл для автостарта

    sudo nano /etc/systemd/system/video.service

С таким содержимым

    [Unit]
    Description=VideoService

    [Service]
    Type=simple
    User=pi
    WorkingDirectory=/home/pi/VideoService/Drone
    ExecStart=/home/pi/VideoService/Drone/VideoService
    Restart=on-abort

    [Install]
    WantedBy=default.target

Обновляем, запускаем

    sudo systemctl daemon-reload
    sudo systemctl enable video
    sudo systemctl start video

