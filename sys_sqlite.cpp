#include "sys_sqlite.h"
#include "globaldata.h"

void createConnectSqlite()
{
    // 查看数据库中可用的驱动
    qDebug()<<"可用的驱动：";
    QStringList drivers = QSqlDatabase::drivers();
    foreach (QString driver, drivers) {
        qDebug()<<driver;
    }

    // 创建连接，使用默认的SqLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    qDebug()<<db.databaseName();
    bool ok = db.open();
    if(ok)
        qDebug()<<"数据库连接成功";
    else
        qDebug()<<"数据库连接失败";

    // 创建数据库表
    // 表名
    QString userTable = "Sys_User";
    QString staffTable = "Sys_Staff";
    QString sellerTable = "Sys_Seller";

    // 建表语句
    QString createUserSql = "create table Sys_User"
                            "("
                            "User_Id integer primary key, "
                            "User_Name varchar(20), "
                            "User_Pwd varchar(20), "
                            "User_Email varchar(20), "
                            "User_Is_Admin int"
                            ")";

    QString createStaffSql = "create table Sys_Staff"
                             "("
                             "Staff_Id varchar(10) primary key, "
                             "Staff_Name varchar(20), "
                             "Staff_Deperment varchar(20), "
                             "Staff_Position varchar(20), "
                             "Staff_Status varchar(20), "
                             "Staff_Phone varchar(20), "
                             "Staff_Date varchar(30), "
                             "Staff_Image varchar(50), "
                             "Staff_Description varchar(50)"
                             ")";

    QString createSellerSql = "create table Sys_Seller"
                              "("
                              "Seller_Id integer primary key, "
                              "Seller_Name varchar(20), "
                              "Seller_Phone varchar(20), "
                              "Seller_Addr varchar(30)"
                              ")";

    createTable(createUserSql, userTable);
    createTable(createStaffSql, staffTable);
    createTable(createSellerSql, sellerTable);
    //    db.close();
}

/*
 * 创建数据库表的函数
 *
*/
void createTable(QString createSql, QString tableName)
{
    QSqlQuery query;
    //    qDebug()<<createSql;
    query.exec(createSql);
    if(isTableExist(tableName))
    {
        qDebug()<< tableName+"表已经存在，无须重新创建！";
    }
    else
    {
        if(!query.exec(createSql))
        {
            qDebug()<<"创建"+ tableName +"失败！";
            qDebug()<<query.lastError();
        }
        else
        {
            qDebug()<<"创建"+ tableName +"成功！";
        }
    }

}

/*
 * 判断要创建的数据库表是否存在
 *
 *
*/
bool isTableExist(QString tableName)
{
    QSqlDatabase database;
    QSqlQuery query(database);
    bool isTableExist = query.exec(
                QString(
                    "select count(*) from sqlite_master "
                    "where type='table' and name='%1'").arg(tableName));
    return isTableExist;
}

/*
 *
 * 判断用户是否存在
 *
 * */
bool userCheck(QString inputText, int num)
{
    bool exists;

    QSqlQuery query;
    QString checkName;
    switch(num)
    {
    case SYS_USER_NUMBER:
        checkName = QString("select ifnull("
                            "(select User_Name "
                            "from Sys_User "
                            "where User_Name = '%1' "
                            "limit 1), "
                            "0)")
                .arg(inputText);
        break;
    case SYS_STAFF_NUMBER:
        checkName = QString("select ifnull("
                            "(select Staff_Name "
                            "from Sys_Staff "
                            "where Staff_Name = '%1' "
                            "limit 1), "
                            "0)")
                .arg(inputText);
        break;
    case SYS_SELLER_NUMCER:
        checkName = QString("select ifnull("
                            "(select Seller_Name "
                            "from Sys_Seller "
                            "where Seller_Name = '%1' "
                            "limit 1), "
                            "0)")
                .arg(inputText);
        break;
    default:
        break;
    }

    query.exec(checkName);

    while(query.next())
    {
        if("0" == query.value(0).toString())
            exists = true;
        else
            exists = false;
    }
    return exists;
}

/*
 *
 * 判断用户密码是否正确
 *
 * */
bool pwdCheck(QString name, QString inputText)
{
    bool flag;

    QSqlQuery query;
    QString checkName = QString("(select User_Pwd "
                                "from Sys_User "
                                "where User_Name = '%1' "
                                "limit 1)")
            .arg(name);
    query.exec(checkName);

    while(query.next())
    {
        qDebug()<<query.value(0).toString();
        if(inputText == query.value(0).toString())
            flag = true;
        else
            flag = false;
    }
    return flag;
}


/*
 *
 * 判断用户身份是否正确
 *
 * */
bool identityCheck(QString name, int inputText)
{
    bool flag;

    QSqlQuery query;
    QString checkName = QString("select User_Is_Admin "
                                "from Sys_User "
                                "where User_Name = '%1' "
                                "limit 1")
            .arg(name);
    query.exec(checkName);

    while(query.next())
    {
        if(inputText == query.value(0).toInt())
            flag = true;
        else
            flag = false;
    }
    return flag;
}

/*
 *
 * 由于卖家身份和用户应该是一样的
 * 一个卖家肯定有一个相应的用户
 * 此处只是模拟系统，不用检测是否
 * 卖家存在，因为一定存在
 * */
void recordSeller(QString input)
{
    QSqlQuery query;
    QString recordSqlSeller = QString("select * "
                                      "from Sys_Seller "
                                      "where Seller_Name = '%1' "
                                      "limit 1")
            .arg(input);
    query.exec(recordSqlSeller);

    while(query.next())
    {
        User::id = query.value(0).toInt();
        User::name = query.value(1).toString();
        User::phone = query.value(2).toString();
        User::addr = query.value(3).toString();
    }
}

/*  数据库操作函数
 *
 *
 * */
void sqlOperator(QString sql)
{
    QSqlQuery query;
    query.exec(sql);
}


/*
 *
 * 根据查询条件来判断职工是否存在
 *
 * */
bool checkExist(QString input, int number)
{
    bool flag;

    QSqlQuery query;
    QString checkSql;

    switch (number) {
    case STAFF_ID_NUMBER:
        checkSql = QString("select ifnull("
                            "(select Staff_Id "
                            "from Sys_Staff "
                            "where Staff_Id = '%1' "
                            "limit 1), "
                            "0)")
                .arg(input);
        break;
    case STAFF_DEPENTMENT_NUMBER:
        checkSql = QString("select ifnull("
                            "(select Staff_Deperment "
                            "from Sys_Staff "
                            "where Staff_Deperment = '%1' "
                            "limit 1), "
                            "0)")
                .arg(input);
        break;
    case STAFF_NAME_NUMBER:
        checkSql = QString("select ifnull("
                            "(select Staff_Name "
                            "from Sys_Staff "
                            "where Staff_Name = '%1' "
                            "limit 1), "
                            "0)")
                .arg(input);
        break;
    default:
        break;
    }


    query.exec(checkSql);

    while(query.next())
    {
        if(input == query.value(0).toInt())
            flag = false;
        else
            flag = true;
    }
    return flag;
}

/*
 *
 * 根据条件查询职工的信息
 *
 * */
void queryInfor(QString input)
{
    if(STAFF_ID == input)
    {

    }
    if(STAFF_NAME == input)
    {

    }
    if(STAFF_DEPENTMENT == input)
    {

    }
}
