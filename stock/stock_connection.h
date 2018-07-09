#ifndef STOCK_CONNECTION_H
#define STOCK_CONNECTION_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
bool Stock_connection()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if(!db.open())
    {
        qDebug()<<"open fail";
        return false;
    }
    QSqlQuery query;
    query.exec("create table stock_plan(id int primary key,seller_id int,money float,fee float,time Date)");
    qDebug()<<query.lastError();
    query.exec("create table stock_provider(id int primary key,owner_id int,name varchar,address varchar)");
    qDebug()<<query.lastError();
    query.exec("create table stock_provider_product(id int primary key,provider_id int,name varchar,price float)");
    qDebug()<<query.lastError();
    query.exec("create table stock_plan_detail(id int primary key,plan_id int,product_id int,cnt int,price float,state varchar)");
    qDebug()<<query.lastError();
    query.exec("create table stock_canceledplan(id int primary key,seller_id int,money float,time Date)");
    qDebug()<<query.lastError();
    query.exec("create table stock_canceledplan_detail(id int primary key,plan_id int,product_id int,cnt int,price float)");
    qDebug()<<query.lastError();
    return true;
}

#endif // STOCK_CONNECTION_H

