SQL: 
create table clientesparad (
    id number(4),
    nome varchar(55),
    idade number(3),
    valor_devido number(6,2),
    primary key (id)
)

insert into clientesparad values (1, 'Augusto', 21, 300.99)
insert into clientesparad values (2, 'Rafael', 21, 330.99)
insert into clientesparad values (3, 'Jair', 21, 500.69)

select * from clientesparad
select * from clientesparad WHERE id = 1
DELETE from clientesparad WHERE id = 3
