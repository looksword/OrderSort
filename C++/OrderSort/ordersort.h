#ifndef ORDERSORT_H
#define ORDERSORT_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QMap>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonValue>
#include <exception>

typedef struct timespan
{
    int start;
    int rest;
    int end;
}TimeSpan;

class SalesOrder
{
public:
    QString SalesIndex;//销售订单编号
    QList<QString> ProductIndex;//产品编号数组
    QList<QString> WorkOrder;//工单编号数组
};

class Process
{
public:
    QString ProcessStep;//工序编码
    int ProcessType;//工序类型(3:包装线,2:灌装线)
    QList<QString> Materiel;//工序对应物料编码
    int TRestTime;//工序对应物料换型时长
    int MRestTime;//工序对应物料换料时长
};

class AllOrder
{
public:
    QString Index;//制令单序号
    int OrderType;//制令单类型
    QList<QString> ProductIndex;//制令单中对应产品编码
    QList<int> ProductNum;//制令单中对应产品数量
    QList<Process> AllProcess;//制令单工艺路线
    QList<QString> WorkOrder;//工单编号
    QString DependProductIndex;//对应依赖产品编码
};

class Stock
{
public:
    QString ProductIndex;//库存中对应产品编码
    int ProductNum;//库存中对应产品数量
};

class CountOrder
{
public:
    QMap<QString,int> ProductMap;//销售订单中对应产品编码
    QList<QString> SalesIndex;//销售订单编号
    int OrderNum;//销售订单数量
};

class ProductOrder
{
public:
    int OrderType;
    QMap<QString,int> ProductNum;//制令单中对应产品、数量
    QString DependProductIndex;//对应依赖产品编码
};

class order_34
{
public:
    int OrderType;
    int ProductNum;
    QList<QString> WorkOrder;
};

//class CostBag
//{
//public:
//    QList<QString> BagProcessStep;//工序对应物料编码
//    QList<int> BagTReplaceTime;//工序对应物料换型时长
//    QList<int> BagMReplaceTime;//工序对应物料换料时长
//};

//class CostPour
//{
//public:
//    QList<QString> PourProcessStep;//工序对应物料编码
//    QList<int> PourTReplaceTime;//工序对应物料换型时长
//    QList<int> PourMReplaceTime;//工序对应物料换料时长
//};

//class ORDERSORT_EXPORT OutputOrder
class OutputOrder
{
public:
    QString Index;//制令单序号
    int OrderType;//制令单类型
    QList<QString> ProductIndex;//制令单中对应产品编码(此处产品编码不重复)
    QList<int> ProductNum; //制令单中对应产品数量
    QList<QString> WorkOrder;//制令单中工单编号数组(工单编号数组本身即按照齐套出库顺序排序)
    QString BagStartTime;//制令单包装线开始时间(00:00:00开始,供参考)
    QString PourStartTime;//灌装线开始时间
    QString BagRestTime;//制令单包装线换型换料时长
    QString PourRestTime;//制令单灌装线换型换料时长
    QString EndTime;//制令单结束时间
	QString DependIndex;//虚拟制令单依赖制令单编号
};

//class ORDERSORT_EXPORT OrderSort
//{
//public:
//    OrderSort();
//    static QList<OutputOrder> SortOrder(QList<SalesOrder>,QList<AllOrder>,QList<Stock>);
//    static bool sortCountOrder(const CountOrder&,const CountOrder&);
//    static QString timestr(const int seconds);
//    static int SortOrder(char *,char *,char *,char *);
//};

extern "C" __declspec(dllexport) int SortOrder(char *,char *,char *,char *);

#endif // ORDERSORT_H
