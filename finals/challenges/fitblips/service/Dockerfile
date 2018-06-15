FROM ubuntu:latest
ENV user=fitblips
RUN apt-get update
RUN apt-get install -y xinetd python-pip
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./fitblips.py /home/$user/
COPY ./requirements.txt /home/$user/
COPY ./flag.py /home/$user/
COPY ./flag /home/$user/
COPY ./fitblipsservice /etc/xinetd.d/
RUN pip install -r /home/$user/requirements.txt
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /home/$user/flag
RUN chmod 440 /home/$user/flag
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
