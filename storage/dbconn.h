#ifndef DBCONN_H
#define DBCONN_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>

// 仓库信息表
static QString storage_info = "create table Storage_info("
                              "storageID integer,"
                              "storageName varchar(10),"
                              "capacity integer,"
                              "remain integer,"
                              "sellerID integer,"
                              "primary key(storageID),"
                              "foreign key(sellerID) references Sys_Seller(Seller_Id)"
                              ")";
// 库存商品信息表
static QString storage_product = "create table Storage_product("
                                 "storageID integer,"
                                 "productID integer,"
                                 "amount integer,"
                                 "primary key(storageID,productID),"
                                 "foreign key(storageID) references Storage_info(storageID),"
                                 "foreign key(productID) references stock_provider_product(id)"
                                 ")";

// 出库记录表
static QString order_record = "create table Storage_order_record("
                              "orderID integer,"
                              "productID integer,"
                              "orderDate datetime,"
                              "amount integer,"
                              "primary key(orderID),"
                              "foreign key(productID) references stock_provider_product(id)"
                              ")";


// 卖家信息表
static QString seller = "create table Sys_Seller("
                        "Seller_Id integer,"
                        "Seller_Name varchar(10),"
                        "primary key(Seller_Id)"
                        ")";
// 商品信息表
static QString product = "create table stock_provider_product("
                         "id integer,"
                         "name integer,"
                         "price float,"
                         "primary key(id)"
                         ")";


// 界面显示view
static QString main_view = "create view Main_view as "
                           "select si.storageName, s.Seller_Name, p.name, sp.amount "
                           "from Sys_Seller s, stock_provider_product p, Storage_info si, Storage_product sp "
                           "where si.sellerID = s.Seller_Id "
                           "and sp.storageID = si.storageID "
                           "and sp.productID = p.id";


// 建立数据库连接
static bool createConn()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        return false;
    }
    // 建表
    QSqlQuery query(db);
    query.exec(seller);
    if (query.lastError().isValid()) qDebug() << query.lastError().text();
    query.exec(product);
    if (query.lastError().isValid()) qDebug() << query.lastError().text();
    query.exec(storage_info);
    if (query.lastError().isValid()) qDebug() << query.lastError().text();
    query.exec(storage_product);
    if (query.lastError().isValid()) qDebug() << query.lastError().text();
    query.exec(order_record);
    if (query.lastError().isValid()) qDebug() << query.lastError().text();
    query.exec(main_view);
    if (query.lastError().isValid()) qDebug() << query.lastError().text();

    return true;
}


#endif // DBCONN_H

