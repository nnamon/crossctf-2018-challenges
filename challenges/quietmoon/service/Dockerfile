FROM ubuntu:latest
ENV user=quietmoon
RUN apt-get update
RUN apt-get install -y xinetd
RUN useradd -m $user
RUN mkdir /thecoven/
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./quietmoon /home/$user/
COPY ./moon.ascii /home/$user/
COPY ./flag /thecoven/flag
COPY ./quietmoonservice /etc/xinetd.d/
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /thecoven/flag
RUN chmod 440 /thecoven/flag
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
