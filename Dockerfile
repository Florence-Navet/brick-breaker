FROM gcc:15.2.0

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libsfml-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app
