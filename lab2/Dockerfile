FROM archlinux:latest

RUN pacman -Syu --noconfirm && pacman -S --noconfirm \
    coreutils \
    procps \
    util-linux \
    bash

WORKDIR /app

COPY script.sh /app/script.sh
RUN chmod +x /app/script.sh

CMD ["./script.sh"]
