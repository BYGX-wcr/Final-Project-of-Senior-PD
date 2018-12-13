create database student_db;
ALTER DATABASE student_db DEFAULT CHARACTER SET utf8;

use student_db;

create table student_t1 (
	sno int primary key,
    sname varchar(20) not null,
    sex char(4) not null,
    birthday date not null,
    nativeplace varchar(80),
    address varchar(80)
);

create table student_t2 (
	sno int primary key,
    sname varchar(20) not null,
    sex char(4) not null,
    birthday date not null,
    nativeplace varchar(80),
    address varchar(80)
);
