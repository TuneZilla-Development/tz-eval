FROM debian:sid-20230612 AS deps

RUN DEBIAN_FRONTEND=noninteractive apt-get update -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y ca-certificates checkinstall build-essential perl wget apt-utils libz-mingw-w64-dev gcc-mingw-w64-i686

FROM deps AS builder

ARG CI_COMMIT_SHA="????????????????????????????????????????"
ARG CI_COMMIT_SHORT_SHA="????????"

COPY . /app

RUN cd /app \
  && make clean \
  && make CFLAGS="-I/usr/i686-w64-mingw32/include" VERSION_COMMIT="\"${CI_COMMIT_SHORT_SHA}\"" VERSION_COMMIT_FULL="\"${CI_COMMIT_SHA}\"" VERSION_DIRTY=0

FROM scratch as export

# Copy all files
COPY --from=builder /app/client.exe /client.exe

ENTRYPOINT ["none"]