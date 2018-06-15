FROM ubuntu:latest
ENV user=ftlog
RUN apt-get update
RUN apt-get install -y xinetd qemu
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./ftlog /home/$user/
COPY ./flag /home/$user/
COPY ./run.sh /home/$user/
COPY ./ftlogservice /etc/xinetd.d/ftlogservice
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /home/$user/flag
RUN chmod 440 /home/$user/flag
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
