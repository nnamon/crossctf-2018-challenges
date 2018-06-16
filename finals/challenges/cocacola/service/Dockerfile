FROM ubuntu:xenial
ENV user=cocacolauser
RUN apt-get update
RUN apt-get install -y xinetd
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./cocacola /home/$user/
COPY ./flag_page /flag_page
COPY ./cocacolaservice /etc/xinetd.d/cocacolaservice
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /flag_page
RUN chmod 440 /flag_page
EXPOSE 31337
CMD ["/usr/sbin/xinetd", "-d"]
