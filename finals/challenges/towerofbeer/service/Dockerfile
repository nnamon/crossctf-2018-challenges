FROM ubuntu:latest
ENV user=towerofbeeruser
RUN apt-get update
RUN apt-get install -y xinetd
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./towerofbeer /home/$user/towerofbeer
COPY ./flag1 /home/$user/flag1
COPY ./flag2 /home/$user/flag2
COPY ./towerofbeerservice /etc/xinetd.d/towerofbeerservice
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /home/$user/flag1
RUN chown root:$user /home/$user/flag2
RUN chmod 440 /home/$user/flag1
RUN chmod 440 /home/$user/flag2
EXPOSE 16666
CMD ["/usr/sbin/xinetd", "-d"]
