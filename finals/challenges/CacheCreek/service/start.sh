#!/bin/bash

find /var/lib/mysql -type f -exec touch {} \;
service mysql start
service apache2 start &
mysql -uroot -pAdmin2015 -e """
drop database exampleDB;
SET PASSWORD = PASSWORD('9A&*h^F68l9QgzQyc6C4MajY3SHf332I1ENYcVjb');
CREATE USER 'crossctf'@'localhost' IDENTIFIED BY '9A&*h^F68l9QgzQyc6C4MajY3SHf332I1ENYcVjb';
GRANT SELECT, INSERT, CREATE, UPDATE ON crossctf.* TO 'crossctf'@'localhost';
CREATE DATABASE crossctf;
USE crossctf;
CREATE TABLE users (id INT NOT NULL AUTO_INCREMENT, username varchar(30) NOT NULL, password varchar(64) NOT NULL, profile varchar(255) NOT NULL, PRIMARY KEY (id));
INSERT INTO users VALUES (null, 'admin', md5('C4MajY3SHf332I1ENYcVjb'), 'nothing to see here');
"""

/bin/bash
