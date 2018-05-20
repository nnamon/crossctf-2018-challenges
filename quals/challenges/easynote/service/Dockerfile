FROM ubuntu:17.10

RUN apt-get update && apt-get -y dist-upgrade
RUN apt-get install -y xinetd dos2unix

WORKDIR /home/easynote
ADD easynote .
RUN chmod 555 ./easynote
RUN chmod 555 .
RUN chmod 555 /home

ADD flag /flag.txt
RUN chmod 444 /flag.txt

RUN useradd -ms /bin/bash easynote
ADD easynote.xinetd /etc/xinetd.d/easynote
RUN dos2unix /etc/xinetd.d/easynote
RUN chmod 444 /etc/xinetd.d/easynote
RUN echo "easynote                          54245/tcp" >> /etc/services

RUN service xinetd restart

RUN chown -R root:root .

EXPOSE 54245

CMD service xinetd restart && sleep infinity
