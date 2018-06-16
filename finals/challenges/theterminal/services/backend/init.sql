create table accounts(username varchar(255), password varchar(255));
insert into accounts values ("tomhanks", "krakozia");
insert into accounts values ("admin", "YOUCANNOTGUESSTHISPASSWORD");
create table posts(title varchar(1024), author varchar(255), body text);
insert into posts values ("Hello World!", "admin", "This is the first post ever!");
insert into posts values ("Help", "tomhanks", "Please save me.");
insert into posts values ("Bounty", "admin", "I will give you a billion dollars if you can posts as me!");
