FROM ubuntu:latest
ENV user=moonmoon
RUN apt-get update
RUN apt-get install -y xinetd
RUN useradd -m $user
RUN mkdir /thecoven/
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./bloodmoon /home/$user/
COPY ./moon.ascii /home/$user/
COPY ./flag /thecoven_of_kings/flagtastic
COPY ./bloodmoonservice /etc/xinetd.d/
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /thecoven_of_kings/flagtastic
RUN chmod 440 /thecoven_of_kings/flagtastic
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
