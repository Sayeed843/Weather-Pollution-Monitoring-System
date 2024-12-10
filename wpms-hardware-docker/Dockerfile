# Use Ubuntu 24.04 as the base image
FROM ubuntu:24.04

# Set the environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install required tools and dependencies
RUN apt-get update && apt-get install -y \
    wget \
    git \
    unzip \
    python3 \
    python3-pip \
    python3-serial \
    build-essential \
    libusb-1.0-0-dev \
    openjdk-11-jdk \
    arduino && \
    apt-get clean

# Install Arduino CLI (Command Line Interface)
RUN wget https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Linux_64bit.tar.gz && \
    tar -xvzf arduino-cli_latest_Linux_64bit.tar.gz && \
    mv arduino-cli /usr/local/bin && \
    rm arduino-cli_latest_Linux_64bit.tar.gz

# Create workspace directory
WORKDIR /workspace

# Install LiquidCrystal_I2C library by Frank de Brabander
RUN mkdir -p /root/Arduino/libraries && \
    git clone https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library.git /root/Arduino/libraries/LiquidCrystal_I2C

# Install DHT library by Adafruit
RUN git clone https://github.com/adafruit/DHT-sensor-library.git /root/Arduino/libraries/DHT && \
    git clone https://github.com/adafruit/Adafruit_Sensor.git /root/Arduino/libraries/Adafruit_Sensor

# Expose workspace volume (optional)
VOLUME ["/workspace"]

# Set Arduino CLI path
ENV PATH="/usr/local/bin:${PATH}"

# Set default command to start the Arduino CLI
CMD ["arduino-cli"]

