FROM ubuntu:xenial
ENV user=slowmo
RUN apt-get update
RUN apt-get install -y xinetd qemu
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./slowmo /home/$user/
COPY ./flag /home/$user/
COPY ./run.sh /home/$user/
COPY ./service /etc/xinetd.d/service
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /home/$user/flag
RUN chmod 440 /home/$user/flag
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
