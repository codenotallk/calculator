use report_db;

show databases;

show tables;

select * from reports_tb;

insert into reports_tb (type, value_1, value_2, result, data) values ('subb', 10, 5, 5,
1724421223);

select * from reports_tb where data between 1724421180 and 1724421840 order by id desc limit 20 offset 0

## Delete
delete from reports_tb;

## Count items on database

select count(*) as amount from reports_tb;