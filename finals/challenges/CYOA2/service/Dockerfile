FROM ubuntu:latest
ENV user=physadventureuser
RUN apt-get update
RUN apt-get install -y xinetd
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./physadventure /home/$user
COPY ./physadventureservice /etc/xinetd.d/physadventureservice
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
