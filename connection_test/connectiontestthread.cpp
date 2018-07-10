#include "connection_test/connectiontestthread.h"
#include "mysql_connection_pool/connectionPool.h"

void ConnectionTestThread::run() {
        // 从数据库连接池里取得连接
    QSqlDatabase db = ConnectionPool::openConnection();
    qDebug() << "In thread run():" << db.connectionName();

    QSqlQuery query(db);
    query.exec("SELECT * FROM goods");

    while (query.next()) {
        qDebug() << query.value("goods_name").toString();
    }

    // 连接使用完后需要释放回数据库连接池
    ConnectionPool::closeConnection(db);
}
