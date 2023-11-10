# Use Debian bullseye slim as the base image for a smaller footprint
FROM debian:bullseye-slim

# Set the working directory in the container
WORKDIR /usr/src/myapp

# Install build dependencies for CMake and other build essentials
RUN apt-get update && apt-get install -y \
    software-properties-common \
    apt-transport-https \
    lsb-release \
    ca-certificates \
    wget \
    gnupg2 \
    build-essential \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Download CMake source code, verify it, and build from source
RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.7/cmake-3.27.7.tar.gz \
    && tar -zxvf cmake-3.27.7.tar.gz \
    && cd cmake-3.27.7 \
    && ./bootstrap \
    && make \
    && make install

# Copy the current directory contents into the container at /usr/src/myapp
COPY . .

# Create a separate build directory
RUN mkdir build
WORKDIR /usr/src/myapp/build

# Run CMake and make from the build directory
RUN cmake ..
RUN make

# Command to run on container start
CMD ["./p1_recipe_recommender"]
