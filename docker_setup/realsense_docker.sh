#!/bin/bash

# Set your device ID here
DEVIDE_ID = "8086:0b3a"

# Find the bus and device numbers
BUS=$(lsusb | grep -i "${DEVICE_ID}" | awk '{print $2}')
DEVICE=$(lsusb | grep -i "{DEVICE_ID}" | awk '{print $4}' | tr -d ':')

# Set the permissions for the devices
sudo chmod 666 /dev/bus/usb/${BUS}/${DEVICE}

# Run the docker container
docker run -d --restart=on-failure \
    --privileged=true \
    --name workspace \
    --cap-add=SYS_PTRACE \
    --cap-add=SYS_ADMIN \
    --gpus all  \
    --shm-size=1024m \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    -p 10022:22  \
    -p 14000:4000  \
    -v /dev/bus/usb:/dev/bus/usb \
    jixinyin/realsense_docker:v1
