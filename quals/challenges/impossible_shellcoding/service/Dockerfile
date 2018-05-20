FROM ubuntu:17.10

RUN apt-get update && apt-get -y dist-upgrade
RUN apt-get install -y xinetd dos2unix

WORKDIR /home/impossible_shellcoding
ADD impossible_shellcoding .
RUN chmod 555 ./impossible_shellcoding
RUN chmod 555 .
RUN chmod 555 /home

ADD flag.txt /flag.txt
RUN chmod 444 /flag.txt

RUN useradd -ms /bin/bash impossible_shellcoding
ADD impossible_shellcoding.xinetd /etc/xinetd.d/impossible_shellcoding
RUN dos2unix /etc/xinetd.d/impossible_shellcoding
RUN chmod 444 /etc/xinetd.d/impossible_shellcoding
RUN echo "impossible_shellcoding                  34643/tcp" >> /etc/services

RUN service xinetd restart

RUN chown -R root:root .

EXPOSE 34643

CMD service xinetd restart && sleep infinity
