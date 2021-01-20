FROM gcc:9.3.0

COPY ext/catch2.h /usr/include

RUN apt-get update && \
  DEBIAN_FRONTEND=noninteractive apt-get install -y cmake clang-format
