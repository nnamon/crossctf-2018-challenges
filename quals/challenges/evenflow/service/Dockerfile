FROM ubuntu:latest
ENV user=evenflow
RUN apt-get update
RUN apt-get install -y xinetd python
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./evenflow /home/$user/
COPY ./evenflow.py /home/$user/
COPY ./flag /home/$user/flag
COPY ./evenflowservice /etc/xinetd.d/evenflowservice
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /home/$user/flag
RUN chmod 440 /home/$user/flag
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
