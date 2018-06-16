FROM ubuntu:xenial
ENV user=theterminal
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install -y xinetd apache2 python vim python-pip sqlite3 gunicorn netcat
RUN pip install -U pip
RUN pip install -U flask
RUN pip install -U flask-cors
RUN pip install -U pillow
RUN mkdir /service/
COPY start_services.sh /service/start_services.sh
RUN useradd -m $user
RUN echo "$user     hard    nproc       20" >> /etc/security/limits.conf
COPY ./the_flag_is_here_not_elsewhere /home/$user/the_flag_is_here_not_elsewhere
RUN rm -rf /var/www/html/*
ADD site/ /var/www/html/
ADD backend /backend
RUN chown -R root:$user /home/$user
RUN chmod -R 750 /home/$user
RUN chown root:$user /home/$user/the_flag_is_here_not_elsewhere
RUN chmod 440 /home/$user/the_flag_is_here_not_elsewhere
EXPOSE 80
EXPOSE 8082
CMD ["/bin/bash", "/service/start_services.sh"]
