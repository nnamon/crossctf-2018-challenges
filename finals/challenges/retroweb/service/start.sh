#!/bin/bash

find /var/lib/mysql -type f -exec touch {} \;
service mysql start
service apache2 start &
mysql -uroot -pAdmin2015 -e """
drop database exampleDB;
SET PASSWORD = PASSWORD('9A&*h^F68l9QgzQyc6C4MajY3SHf332I1ENYcVjb');
CREATE USER 'crossctf'@'localhost' IDENTIFIED BY '9A&*h^F68l9QgzQyc6C4MajY3SHf332I1ENYcVjb';
GRANT SELECT, INSERT, CREATE ON crossctf.* TO 'crossctf'@'localhost';
CREATE DATABASE crossctf;
USE crossctf;
CREATE TABLE users (id INT NOT NULL AUTO_INCREMENT, username varchar(30) NOT NULL, password varchar(64) NOT NULL, flag varchar(256), isAdmin INT DEFAULT 0, PRIMARY KEY (id));
INSERT INTO users VALUES (null, 'admin', md5('akszxmciu41534567uasnd217^%$#@$%'), 'CrossCTF{Why_W0uLd_Any0ne_<3_Web?!}', 1);
INSERT INTO users VALUES (null, 'harry', md5('akszxmciu41534567uasnd217^%$#@$%'), '', 1);
INSERT INTO users VALUES (null, 'viggotarasov', md5('akszxmciu41534567uasnd217^%$#@$%'), '', 1);
INSERT INTO users VALUES (null, 'msperkins', md5('akszxmciu41534567uasnd217^%$#@$%'), '', 1);
INSERT INTO users VALUES (null, 'amon', md5('akszxmciu41534567uasnd217^%$#@$%'), '', 1);
INSERT INTO users VALUES (null, 'kaiyuan', md5('akszxmciu41534567uasnd217^%$#@$%'), '', 1);
"""

/bin/bash
