FROM ubuntu:latest
ENV user=adventureuser
RUN apt-get update
RUN apt-get install -y xinetd
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./adventure /home/$user
COPY ./adventureservice /etc/xinetd.d/adventureservice
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
