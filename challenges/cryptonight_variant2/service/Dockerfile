FROM ubuntu:latest
ENV user=cryptonightuser
RUN apt-get update
RUN apt-get install -y xinetd python-pip
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./cryptonight.py /home/$user/
COPY ./flag.py /home/$user/
COPY ./flag /home/$user/
COPY ./_pycryptonight.so /home/$user/
COPY ./pycryptonight/ /home/$user/pycryptonight
COPY ./cryptonightservice /etc/xinetd.d/
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /home/$user/flag
RUN chmod 440 /home/$user/flag
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
