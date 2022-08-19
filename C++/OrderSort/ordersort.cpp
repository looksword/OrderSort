#include "ordersort.h"

//OrderSort::OrderSort()
//{
//}

//QList<OutputOrder> OrderSort::SortOrder(QList<SalesOrder> salesorder,QList<AllOrder> allorder,QList<Stock> stock)
//{
//}

//QString OrderSort::timestr(const int seconds)
//{
//}

//int OrderSort::SortOrder(char * buffer1,char * buffer2,char * buffer3,char * outputchar)
//{
//}

int SortOrder(char * buffer1,char * buffer2,char * buffer3,char * buffer4)
{
    try {
        if(buffer1 == nullptr || buffer2 == nullptr || buffer3 == nullptr)
        {
            return 0;
        }
        QByteArray qbyte1;
        qbyte1 = QByteArray(buffer1);
        QByteArray qbyte2;
        qbyte2 = QByteArray(buffer2);
        QByteArray qbyte3;
        qbyte3 = QByteArray(buffer3);

        QJsonParseError jsonError;
        QList<SalesOrder> SalesOrders;
        QJsonDocument document1 = QJsonDocument::fromJson(qbyte1,&jsonError);
        if(!document1.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if(document1.isArray())
            {
                QJsonArray array = document1.array();
                int nSize = array.size();
                //printf("nSize1 len%d\n",nSize);
                for(int i = 0;i < nSize;i++)
                {
                    if(array.at(i).isObject())
                    {
                        QJsonObject object = array.at(i).toObject();
                        SalesOrder newSalesOrder;
                        if(object.contains("SalesIndex"))
                        {
                            QJsonValue value = object.value("SalesIndex");
                            if(value.isString())
                            {
                                QString salesindex = value.toString();
                                newSalesOrder.SalesIndex = salesindex;
                            }
                        }
                        if(object.contains("ProductIndex"))
                        {
                            QJsonValue value = object.value("ProductIndex");
                            if(value.isArray())
                            {
                                QList<QString> productindexs;
                                QJsonArray array1 = value.toArray();
                                int nSize1 = array1.size();
                                for(int j = 0;j < nSize1;j++)
                                {
                                    QJsonValue value = array1.at(j);
                                    if(value.isString())
                                    {
                                        QString productindex = value.toString();
                                        productindexs.append(productindex);
                                    }
                                }
                                newSalesOrder.ProductIndex = productindexs;
                            }
                        }
                        if(object.contains("WorkOrder"))
                        {
                            QJsonValue value = object.value("WorkOrder");
                            if(value.isArray())
                            {
                                QList<QString> workorders;
                                QJsonArray array1 = value.toArray();
                                int nSize1 = array1.size();
                                for(int j = 0;j < nSize1;j++)
                                {
                                    QJsonValue value = array1.at(j);
                                    if(value.isString())
                                    {
                                        QString workorder = value.toString();
                                        workorders.append(workorder);
                                    }
                                }
                                newSalesOrder.WorkOrder = workorders;
                            }
                        }
                        if(newSalesOrder.ProductIndex.length() != newSalesOrder.WorkOrder.length())
                        {
                            return 6;
                        }
                        SalesOrders.append(newSalesOrder);
                    }
                }
            }
        }
        if(SalesOrders.length() == 0)
        {
            qbyte1.clear();
            qbyte2.clear();
            qbyte3.clear();
            return 2;
        }
        //printf("SalesOrders len%d\n",SalesOrders.length());
        QList<AllOrder> AllOrders;
        QJsonDocument document2 = QJsonDocument::fromJson(qbyte2,&jsonError);
        if(!document2.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if(document2.isArray())
            {
                QJsonArray array = document2.array();
                int nSize = array.size();
                for(int i = 0;i < nSize;i++)
                {
                    if(array.at(i).isObject())
                    {
                        QJsonObject object = array.at(i).toObject();
                        AllOrder newallOrder;
                        if(object.contains("Index"))
                        {
                            QJsonValue value = object.value("Index");
                            if(value.isString())
                            {
                                QString Index = value.toString();
                                newallOrder.Index = Index;
                            }
                        }
                        if(object.contains("OrderType"))
                        {
                            QJsonValue value = object.value("OrderType");
                            if(value.isDouble())
                            {
                                int OrderType = value.toInt();
                                newallOrder.OrderType = OrderType;
                            }
                        }
                        if(object.contains("ProductIndex"))
                        {
                            QJsonValue value = object.value("ProductIndex");
                            if(value.isArray())
                            {
                                QList<QString> productindexs;
                                QJsonArray array1 = value.toArray();
                                int nSize1 = array1.size();
                                for(int j = 0;j < nSize1;j++)
                                {
                                    QJsonValue value = array1.at(j);
                                    if(value.isString())
                                    {
                                        QString productindex = value.toString();
                                        productindexs.append(productindex);
                                    }
                                }
                                newallOrder.ProductIndex = productindexs;
                            }
                        }
                        if(object.contains("ProductNum"))
                        {
                            QJsonValue value = object.value("ProductNum");
                            if(value.isArray())
                            {
                                QList<int> ProductNum;
                                QJsonArray array1 = value.toArray();
                                int nSize1 = array1.size();
                                for(int j = 0;j < nSize1;j++)
                                {
                                    QJsonValue value = array1.at(j);
                                    if(value.isDouble())
                                    {
                                        int productnum = value.toInt();
                                        ProductNum.append(productnum);
                                    }
                                }
                                newallOrder.ProductNum = ProductNum;
                            }
                        }
                        if(object.contains("Process"))
                        {
                            QJsonValue value = object.value("Process");
                            if(value.isArray())
                            {
                                QList<Process> AllProcess;
                                QJsonArray array1 = value.toArray();
                                int nSize1 = array1.size();
                                for(int j = 0;j < nSize1;j++)
                                {
                                    QJsonObject object1 = array1.at(j).toObject();
                                    Process newProcess;
                                    if(object1.contains("ProcessStep"))
                                    {
                                        QJsonValue value1 = object1.value("ProcessStep");
                                        if(value1.isString())
                                        {
                                            QString ProcessStep = value1.toString();
                                            newProcess.ProcessStep = ProcessStep;
                                        }
                                    }
                                    if(object1.contains("ProcessType"))
                                    {
                                        QJsonValue value1 = object1.value("ProcessType");
                                        if(value1.isDouble())
                                        {
                                            int ProcessType = value1.toInt();
                                            newProcess.ProcessType = ProcessType;
                                        }
                                    }
                                    if(object1.contains("Materiel"))
                                    {
                                        QJsonValue value1 = object1.value("Materiel");
                                        if(value1.isArray())
                                        {
                                            QList<QString> Materiels;
                                            QJsonArray array1 = value1.toArray();
                                            int nSize1 = array1.size();
                                            for(int j = 0;j < nSize1;j++)
                                            {
                                                QJsonValue value2 = array1.at(j);
                                                if(value2.isString())
                                                {
                                                    QString Materiel = value2.toString();
                                                    Materiels.append(Materiel);
                                                }
                                            }
                                            newProcess.Materiel = Materiels;
                                        }
                                    }
                                    if(object1.contains("TRestTime"))
                                    {
                                        QJsonValue value1 = object1.value("TRestTime");
                                        if(value1.isDouble())
                                        {
                                            int TRestTime = value1.toInt();
                                            newProcess.TRestTime = TRestTime;
                                        }
                                    }
                                    else
                                    {
                                        newProcess.TRestTime = 0;
                                    }
                                    if(object1.contains("MRestTime"))
                                    {
                                        QJsonValue value1 = object1.value("MRestTime");
                                        if(value1.isDouble())
                                        {
                                            int MRestTime = value1.toInt();
                                            newProcess.MRestTime = MRestTime;
                                        }
                                    }
                                    else
                                    {
                                        newProcess.MRestTime = 0;
                                    }
                                    AllProcess.append(newProcess);
                                }
                                newallOrder.AllProcess = AllProcess;
                            }
                        }
                        if(object.contains("WorkOrder"))
                        {
                            QJsonValue value = object.value("WorkOrder");
                            if(value.isArray())
                            {
                                QList<QString> workorders;
                                QJsonArray array1 = value.toArray();
                                int nSize1 = array1.size();
                                for(int j = 0;j < nSize1;j++)
                                {
                                    QJsonValue value = array1.at(j);
                                    if(value.isString())
                                    {
                                        QString workorder = value.toString();
                                        workorders.append(workorder);
                                    }
                                }
                                newallOrder.WorkOrder = workorders;
                            }
                        }
                        if(object.contains("DependProductIndex"))
                        {
                            QJsonValue value = object.value("DependProductIndex");
                            if(value.isString())
                            {
                                QString DependProductIndex = value.toString();
                                newallOrder.DependProductIndex = DependProductIndex;
                            }
                        }
                        AllOrders.append(newallOrder);
                    }
                }
            }
        }
        if(AllOrders.length() == 0)
        {
            qbyte1.clear();
            qbyte2.clear();
            qbyte3.clear();
            return 3;
        }
        //printf("AllOrders len%d\n",AllOrders.length());
        QList<Stock> Stocks;
        QJsonDocument document3 = QJsonDocument::fromJson(qbyte3,&jsonError);
        if(!document3.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if(document3.isArray())
            {
                QJsonArray array = document3.array();
                int nSize = array.size();
                for(int i = 0;i < nSize;i++)
                {
                    if(array.at(i).isObject())
                    {
                        QJsonObject object = array.at(i).toObject();
                        Stock newStock;
                        if(object.contains("ProductIndex"))
                        {
                            QJsonValue value = object.value("ProductIndex");
                            if(value.isString())
                            {
                                QString ProductIndex = value.toString();
                                newStock.ProductIndex = ProductIndex;
                            }
                        }
                        if(object.contains("ProductNum"))
                        {
                            QJsonValue value = object.value("ProductNum");
                            if(value.isDouble())
                            {
                                int ProductNum = value.toInt();
                                newStock.ProductNum = ProductNum;
                            }
                        }
                        Stocks.append(newStock);
                    }
                }
            }
        }
        //printf("Stocks len%d\n",Stocks.length());

        //
        qbyte1.clear();
        qbyte2.clear();
        qbyte3.clear();

        int bagtime = 30;
        int pourtime = 10;
        //int order2time = 10;
        //QString testalpha = "A";
        //QString order2alpha = "U";
        int allsetnum = 400;
        int bagoncenum = 175;
        int pouroncenum = 100;
        QMap<QString,SalesOrder> SalesMap;//销售订单溯源
        QMap<QString,order_34> order34;
        QList<ProductOrder> order56;
        QList<ProductOrder> order7;
        QMap<QString,int> StockMap;//备货仓内
        QMap<QString,int> In_Product;//齐套仓内
        QList<CountOrder> CountList;//相同产品订单
        QList<OutputOrder> outputorder;//结果
        QMap<QString,QList<Process>> BagCost;
        QMap<QString,QList<Process>> PourCost;
        bool EqualSalesOrder = false;
        foreach(SalesOrder sorder, SalesOrders)
        {
            if(!SalesMap.contains(sorder.SalesIndex))
            {
                SalesMap.insert(sorder.SalesIndex,sorder);
            }
            else
            {
                EqualSalesOrder = true;//销售订单编号相同
            }
            bool HaveEqual = true;
            QMap<QString,int> newProductMap;
            foreach(QString index, sorder.ProductIndex)
            {
                if(newProductMap.contains(index))
                {
                    newProductMap[index]++;
                }
                else
                {
                    newProductMap.insert(index,1);
                }
            }
            for(int i = 0;i < CountList.length();i++)
            {
                foreach(QString oldpro,CountList[i].ProductMap.keys())
                {
                    if(!newProductMap.contains(oldpro))
                    {
                        HaveEqual = false;
                        break;
                    }
                    if(newProductMap[oldpro] != CountList[i].ProductMap[oldpro])
                    {
                        HaveEqual = false;
                        break;
                    }
                }
                if(HaveEqual)
                {
                    foreach(QString newpro,newProductMap.keys())
                    {
                        if(!CountList[i].ProductMap.contains(newpro))
                        {
                            HaveEqual = false;
                            break;
                        }
                        if(CountList[i].ProductMap[newpro] != CountList[i].ProductMap[newpro])
                        {
                            HaveEqual = false;
                            break;
                        }
                    }
                    if(HaveEqual)
                    {
                        CountList[i].OrderNum++;
                        CountList[i].SalesIndex.append(sorder.SalesIndex);
                    }
                }
            }
            if(!HaveEqual || CountList.length() == 0)
            {
                CountOrder product;
                product.ProductMap = newProductMap;
                QList<QString> newSalesIndex;
                newSalesIndex.append(sorder.SalesIndex);
                product.SalesIndex= newSalesIndex;
                product.OrderNum = 1;
                CountList.append(product);
            }
        }
        if(EqualSalesOrder)
        {
            SalesMap.clear();
            CountList.clear();
            return 5;
        }
        //printf("CountList len%d\n",CountList.length());
        std::sort(CountList.begin(), CountList.end(),[](const CountOrder & infoA, const CountOrder & infoB){return infoA.ProductMap.keys().count() > infoB.ProductMap.keys().count();});
        //qSort(CountList.begin(), CountList.end(),[](const CountOrder &infoA,const CountOrder &infoB){return infoA.ProductSet.count() > infoB.ProductSet.count();});
        foreach(AllOrder aorder, AllOrders)
        {
            if(aorder.OrderType == 3 || aorder.OrderType == 4)
            {
                if(!order34.contains(aorder.ProductIndex[0]))
                {
                    order_34 neworder34;
                    neworder34.OrderType = aorder.OrderType;
                    neworder34.ProductNum = aorder.ProductNum[0];
                    QList<QString> newworkorder(aorder.WorkOrder);
                    neworder34.WorkOrder = newworkorder;
                    order34.insert(aorder.ProductIndex[0],neworder34);
                }
                if(!PourCost.contains(aorder.ProductIndex[0]))
                {
                    QList<Process> newProcess(aorder.AllProcess);
                    PourCost.insert(aorder.ProductIndex[0],newProcess);
                }
                if(!StockMap.contains(aorder.ProductIndex[0]))
                {
                    StockMap.insert(aorder.ProductIndex[0],0);
                }
            }
            if(aorder.OrderType == 5 || aorder.OrderType == 6)
            {
                ProductOrder newproduct;
                QMap<QString,int> productnum;
                for(int i = 0;i < aorder.ProductIndex.length();i++)
                {
                    if(!productnum.contains(aorder.ProductIndex[i]))
                    {
                        productnum.insert(aorder.ProductIndex[i], aorder.ProductNum[i]);
                    }
                    if(!In_Product.contains(aorder.ProductIndex[i]))
                    {
                        In_Product.insert(aorder.ProductIndex[i], 0);
                    }
                    if(!BagCost.contains(aorder.ProductIndex[i]))
                    {
                        QList<Process> newProcess(aorder.AllProcess);
                        BagCost.insert(aorder.ProductIndex[i],newProcess);
                    }
                }
                newproduct.OrderType = aorder.OrderType;
                newproduct.ProductNum = productnum;
                newproduct.DependProductIndex = aorder.DependProductIndex;
                order56.append(newproduct);
            }
            if(aorder.OrderType == 7)
            {
                ProductOrder newproduct;
                QMap<QString,int> productnum;
                for(int i = 0;i < aorder.ProductIndex.length();i++)
                {
                    if(!productnum.contains(aorder.ProductIndex[i]))
                    {
                        productnum.insert(aorder.ProductIndex[i], aorder.ProductNum[i]);
                    }
                    if(!In_Product.contains(aorder.ProductIndex[i]))
                    {
                        In_Product.insert(aorder.ProductIndex[i], 0);
                    }
                    if(!BagCost.contains(aorder.ProductIndex[i]))
                    {
                        QList<Process> newProcess(aorder.AllProcess);
                        BagCost.insert(aorder.ProductIndex[i],newProcess);
                    }
                    if(!PourCost.contains(aorder.ProductIndex[i]))
                    {
                        QList<Process> newProcess(aorder.AllProcess);
                        PourCost.insert(aorder.ProductIndex[i],newProcess);
                    }
                }
                newproduct.OrderType = aorder.OrderType;
                newproduct.ProductNum = productnum;
                newproduct.DependProductIndex = aorder.DependProductIndex;
                order7.append(newproduct);
            }
        }
        foreach(Stock st, Stocks)
        {
            if(!StockMap.contains(st.ProductIndex))
            {
                StockMap.insert(st.ProductIndex,st.ProductNum);
            }
            else
            {
                StockMap[st.ProductIndex] += st.ProductNum;
            }
        }

        //
    //    foreach(SalesOrder salesorder,SalesOrders)
    //    {
    //        salesorder.ProductIndex.clear();
    //        salesorder.WorkOrder.clear();
    //    }
        SalesOrders.clear();
    //    foreach(AllOrder allorder,AllOrders)
    //    {
    //        allorder.ProductIndex.clear();
    //        foreach(Process process, allorder.AllProcess)
    //        {
    //            process.Materiel.clear();
    //        }
    //        allorder.AllProcess.clear();
    //    }
        AllOrders.clear();
        Stocks.clear();

        bool First56 = true;
        //bool NotExplode = true;
        QString LastBagOrder = "";
        QString LastPourOrder = "";
        int Index = 0;
        int orderBagStart = 0;
        int orderPourStart = 0;
        QMap<QString, QList<QString>> SalesIndexs;
        int Not7Set = 0;
        int NoNum = 0;
        while(true)
        {
            //计算制令单56剩余
            int sum56 = 0;
            for(int i = 0;i < order56.length();i++)
            {
                foreach(QString product, order56[i].ProductNum.keys())
                {
                    sum56 += order56[i].ProductNum[product];
                }
            }
            //计算制令单7剩余
            int sum7 = 0;
            for(int i = 0;i < order7.length();i++)
            {
                foreach(QString product, order7[i].ProductNum.keys())
                {
                    sum7 += order7[i].ProductNum[product];
                }
            }
            if ((sum56 == 0) && (sum7 == 0))
            {
                break;
            }
            if (((sum56 != 0) && First56) || sum7 == 0)
            {
                //遍历计算各制令单入库数量、可出库数量、灌装数量、换型换料时长
                //int max_count = 0;
                int max_num = 0;
                int max_i = 0;
                int max_cost56 = 0;
                int max_cost34 = 0;
                double max_cost_rate = 0;
                int max_ordernum = 0;
                int max_pournum = 0;
                int max_waittime = 0;
                for(int i = 0;i < order56.length();i++)
                {
                    QString p = order56[i].ProductNum.firstKey();
                    if(order56[i].ProductNum[p] == 0)
                    {
                        continue;
                    }
                    int total = 0;
                    int ordernum = 0;
                    QMap<QString,int> New_product;//在库产品
                    foreach(QString product,In_Product.keys())
                    {
                        if(In_Product[product] > 0)
                        {
                            New_product.insert(product,In_Product[product]);
                        }
                    }
                    for(int j = 0;j < CountList.length();j++)
                    {
                        if(CountList[j].OrderNum == 0)
                        {
                            continue;
                        }
                        if(!CountList[j].ProductMap.contains(p))
                        {
                            continue;
                        }
                        bool allinproduct = true;//是否都在库
                        foreach(QString product,CountList[j].ProductMap.keys())
                        {
                            if(product == p)
                            {
                                continue;
                            }
                            if(!New_product.contains(product))
                            {
                                allinproduct = false;
                            }
                        }
                        if(!allinproduct)
                        {
                            continue;
                        }

                        if(CountList[j].ProductMap.keys().count() == 1)
                        {
                            total += CountList[j].ProductMap[p];
                            ordernum += CountList[j].ProductMap[p];
                        }
                        else
                        {
                            int min_num = CountList[j].OrderNum;
                            foreach(QString product,CountList[j].ProductMap.keys())
                            {
                                if(product == p)
                                {
                                    continue;
                                }
                                int permitnum = int(New_product[product] / CountList[j].ProductMap[product]);
                                if(min_num > permitnum)
                                {
                                    min_num = permitnum;
                                }
                            }
                            foreach(QString product,CountList[j].ProductMap.keys())
                            {
                                if(product == p)
                                {
                                    continue;
                                }
                                New_product[product] -= min_num;
                            }
                            foreach(QString product,CountList[j].ProductMap.keys())
                            {
                                if(product == p)
                                {
                                    ordernum += CountList[j].ProductMap[product];
                                    continue;
                                }
                                total += min_num * CountList[j].ProductMap[product];
                            }
                        }
                    }
                    //printf("total:%d\n",total);
                    //printf("ordernum:%d\n",ordernum);
                    New_product.clear();
                    if(total > 0)
                    {
                        int test_min_order_num = ordernum;
                        test_min_order_num = test_min_order_num > bagoncenum ? test_min_order_num : bagoncenum;
                        int test_max_order_num = test_min_order_num < order56[i].ProductNum[p] ? test_min_order_num : order56[i].ProductNum[p];
                        int newpournum = 0;
                        int maxpournum = 0;
                        int costtime56 = 0;
                        int costtime34 = 0;
                        int bagwaittime = 0;
                        QString frontp = order56[i].DependProductIndex;
                        if(LastBagOrder == "" || !BagCost.contains(LastBagOrder))
                        {
                            for(int j = 0; j < BagCost[p].length();j++)
                            {
                                if(BagCost[p][j].ProcessType == 3)
                                {//3:包装
                                    int mLen = BagCost[p][j].Materiel.length();
                                    costtime56 += BagCost[p][j].MRestTime * mLen;
                                    costtime56 += BagCost[p][j].TRestTime;// * mLen;
                                }
                            }
                        }
                        else
                        {
                            QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                            for(int j = 0; j < BagCost[LastBagOrder].length();j++)
                            {
                                lastStepset.insert(BagCost[LastBagOrder][j].ProcessStep, BagCost[LastBagOrder][j].Materiel);
                            }
                            for(int j = 0; j < BagCost[p].length();j++)
                            {
                                if(BagCost[p][j].ProcessType == 3)
                                {//3:包装
                                    if(!lastStepset.contains(BagCost[p][j].ProcessStep))
                                    {
                                        int mLen = BagCost[p][j].Materiel.length();
                                        costtime56 += BagCost[p][j].MRestTime * mLen;
                                        costtime56 += BagCost[p][j].TRestTime;// * mLen;
                                    }
                                    else
                                    {
                                        QSet<QString> lastmaterielset;//上一工艺所需物料
                                        for(int k = 0; k < lastStepset[LastBagOrder].length();k++)
                                        {
                                            lastmaterielset << lastStepset[LastBagOrder][k];
                                        }
                                        for(int k = 0; k < BagCost[p][j].Materiel.length();k++)
                                        {
                                            int mLen = 0;
                                            if(!lastmaterielset.contains(BagCost[p][j].Materiel[k]))
                                            {
                                                mLen ++;
                                            }
                                            costtime56 += BagCost[p][j].MRestTime * mLen;
                                            costtime56 += BagCost[p][j].TRestTime;// * mLen;
                                        }
                                    }
                                }
                            }
                            lastStepset.clear();
                        }
                        if(LastPourOrder == "" || !PourCost.contains(LastPourOrder))
                        {
                            for(int j = 0; j < PourCost[frontp].length();j++)
                            {
                                if(PourCost[frontp][j].ProcessType == 2)
                                {//2:灌装
                                    int mLen = PourCost[frontp][j].Materiel.length();
                                    costtime34 += PourCost[frontp][j].MRestTime * mLen;
                                    costtime34 += PourCost[frontp][j].TRestTime;// * mLen;
                                }
                            }
                        }
                        else
                        {
                            QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                            for(int j = 0; j < PourCost[LastPourOrder].length();j++)
                            {
                                lastStepset.insert(PourCost[LastPourOrder][j].ProcessStep, PourCost[LastPourOrder][j].Materiel);
                            }
                            for(int j = 0; j < PourCost[frontp].length();j++)
                            {
                                if(PourCost[frontp][j].ProcessType == 3)
                                {//3:包装
                                    if(!lastStepset.contains(PourCost[frontp][j].ProcessStep))
                                    {
                                        int mLen = PourCost[frontp][j].Materiel.length();
                                        costtime34 += PourCost[frontp][j].MRestTime * mLen;
                                        costtime34 += PourCost[frontp][j].TRestTime;// * mLen;
                                    }
                                    else
                                    {
                                        QSet<QString> lastmaterielset;//上一工艺所需物料
                                        for(int k = 0; k < lastStepset[LastPourOrder].length();k++)
                                        {
                                            lastmaterielset << lastStepset[LastPourOrder][k];
                                        }
                                        for(int k = 0; k < PourCost[frontp][j].Materiel.length();k++)
                                        {
                                            int mLen = 0;
                                            if(!lastmaterielset.contains(PourCost[frontp][j].Materiel[k]))
                                            {
                                                mLen ++;
                                            }
                                            costtime34 += PourCost[frontp][j].MRestTime * mLen;
                                            costtime34 += PourCost[frontp][j].TRestTime;// * mLen;
                                        }
                                    }
                                }
                            }
                            lastStepset.clear();
                        }
                        if(StockMap.contains(frontp))
                        {
                            if(test_max_order_num > StockMap[frontp])
                            {
                                if(orderBagStart > orderPourStart + costtime34 * 60)
                                {
                                    newpournum = int((orderBagStart - orderPourStart - costtime34 * 60) / pourtime);
                                    maxpournum = newpournum;
                                    newpournum = newpournum < order56[i].ProductNum[p] - StockMap[frontp] ? newpournum : order56[i].ProductNum[p] - StockMap[frontp];
                                    maxpournum = maxpournum < order34[frontp].ProductNum ? maxpournum : order34[frontp].ProductNum;
                                }
                                else if((sum7 == 0) || (Not7Set == 1))
                                {
                                    int waittime = orderPourStart - orderBagStart;
                                    if(waittime < 0)
                                    {
                                        waittime = 0;
                                    }
                                    bagwaittime = costtime34 * 60 + waittime;
                                    newpournum = test_max_order_num - StockMap[frontp];
                                    maxpournum = newpournum > order34[frontp].ProductNum ? newpournum : order34[frontp].ProductNum;
                                }
                            }
                            else
                            {
                                if(orderBagStart > orderPourStart + costtime34 * 60)
                                {
                                    maxpournum = int((orderBagStart - orderPourStart - costtime34 * 60) / pourtime);
                                    maxpournum = maxpournum < order34[frontp].ProductNum ? maxpournum : order34[frontp].ProductNum;
                                }
                            }
                            test_max_order_num = test_max_order_num < StockMap[frontp] + newpournum ? test_max_order_num : StockMap[frontp] + newpournum;
                        }
                        int permitnum = 0;
                        foreach(QString product,In_Product.keys())
                        {
                            permitnum += In_Product[product];
                        }
                        permitnum = allsetnum - permitnum + total;
                        int test_next_order_num = test_max_order_num < permitnum ? test_max_order_num : permitnum;
                        double cost_rate = static_cast<double>(static_cast<double>(test_next_order_num * bagtime) / (bagwaittime + costtime56 * 60 + test_next_order_num * bagtime));
                        if(cost_rate > max_cost_rate)
                        {
                            max_num = total;
                            max_i = i;
                            //max_count = cmap[1] + cmap[2] + cmap[3] + cmap[4] + cmap[5];
                            max_pournum = maxpournum;
                            max_ordernum = test_next_order_num;
                            max_cost56 = costtime56;
                            max_cost34 = costtime34;
                            max_cost_rate = cost_rate;
                            max_waittime = bagwaittime;
                        }
                    }
                }
                //printf("max_num:%d\n",max_num);
                //printf("max_pournum:%d\n",max_pournum);
                //printf("max_i:%d\n",max_i);
                if(max_num == 0)
                {
                    //可出库数量为0
                    NoNum++;
                    //计算剩余库存中可直接入库数量,进仓
                    int nostock56 = 0;
                    for(int i = 0;i < order56.length();i++)
                    {
                        QString p = order56[i].ProductNum.firstKey();
                        QString frontp = order56[i].DependProductIndex;
                        if(StockMap.contains(frontp))
                        {
                            if((order56[i].ProductNum[p] <= StockMap[frontp]) && (StockMap[frontp] > 0))
                            {
                                nostock56 += order56[i].ProductNum[p];
                            }
                        }
                        else
                        {
                            nostock56 += order56[i].ProductNum[p];
                        }
                    }
                    int permitnum = 0;
                    foreach(QString product,In_Product.keys())
                    {
                        permitnum += In_Product[product];
                    }
                    if((nostock56 < 400 - permitnum) && (nostock56 > 0))
                    {
                        for(int i = 0;i < order56.length();i++)
                        {
                            QString p = order56[i].ProductNum.firstKey();
                            QString frontp = order56[i].DependProductIndex;
                            if(order56[i].ProductNum[p] == 0)
                            {
                                continue;
                            }
                            bool CanPro = true;
                            if(StockMap.contains(frontp))
                            {
                                if(order56[i].ProductNum[p] > StockMap[frontp])
                                {
                                    CanPro = false;
                                }
                            }
                            if(CanPro)
                            {
                                //进仓
                                int testcosttime56 = 0;
                                int next_order_num = order56[i].ProductNum[p];
                                if(LastBagOrder == "" || !BagCost.contains(LastBagOrder))
                                {
                                    for(int j = 0; j < BagCost[p].length();j++)
                                    {
                                        if(BagCost[p][j].ProcessType == 3)
                                        {//3:包装
                                            int mLen = BagCost[p][j].Materiel.length();
                                            testcosttime56 += BagCost[p][j].MRestTime * mLen;
                                            testcosttime56 += BagCost[p][j].TRestTime;// * mLen;
                                        }
                                    }
                                }
                                else
                                {
                                    QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                                    for(int j = 0; j < BagCost[LastBagOrder].length();j++)
                                    {
                                        lastStepset.insert(BagCost[LastBagOrder][j].ProcessStep, BagCost[LastBagOrder][j].Materiel);
                                    }
                                    for(int j = 0; j < BagCost[p].length();j++)
                                    {
                                        if(BagCost[p][j].ProcessType == 3)
                                        {//3:包装
                                            if(!lastStepset.contains(BagCost[p][j].ProcessStep))
                                            {
                                                int mLen = BagCost[p][j].Materiel.length();
                                                testcosttime56 += BagCost[p][j].MRestTime * mLen;
                                                testcosttime56 += BagCost[p][j].TRestTime;// * mLen;
                                            }
                                            else
                                            {
                                                QSet<QString> lastmaterielset;//上一工艺所需物料
                                                for(int k = 0; k < lastStepset[LastBagOrder].length();k++)
                                                {
                                                    lastmaterielset << lastStepset[LastBagOrder][k];
                                                }
                                                for(int k = 0; k < BagCost[p][j].Materiel.length();k++)
                                                {
                                                    int mLen = 0;
                                                    if(!lastmaterielset.contains(BagCost[p][j].Materiel[k]))
                                                    {
                                                        mLen ++;
                                                    }
                                                    testcosttime56 += BagCost[p][j].MRestTime * mLen;
                                                    testcosttime56 += BagCost[p][j].TRestTime;// * mLen;
                                                }
                                            }
                                        }
                                    }
                                    lastStepset.clear();
                                }
                                In_Product[p] += next_order_num;
                                //更新 在库 齐套出库
                                for(int j = 0;j < CountList.length();j++)
                                {
                                    if(CountList[j].OrderNum == 0)
                                    {
                                        continue;
                                    }
                                    int s = 400;
                                    foreach(QString product, CountList[j].ProductMap.keys())
                                    {
                                        int actualnum = int(In_Product[product] / CountList[j].ProductMap[product]);
                                        if(actualnum < s)
                                        {
                                            s = actualnum;
                                        }
                                    }
                                    if(s > 0)
                                    {
                                        int delta = 0;
                                        if(CountList[j].OrderNum > s)
                                        {
                                            delta = s;
                                            CountList[j].OrderNum -= s;
                                            foreach(QString product, CountList[j].ProductMap.keys())
                                            {
                                                In_Product[product] -= delta * CountList[j].ProductMap[product];
                                            }
                                        }
                                        else
                                        {
                                            delta = CountList[j].OrderNum;
                                            CountList[j].OrderNum = 0;
                                            foreach(QString product, CountList[j].ProductMap.keys())
                                            {
                                                In_Product[product] -= delta * CountList[j].ProductMap[product];
                                            }
                                        }
                                        //printf("delta1:%d\n",delta);
                                        for(int k = 0;k < delta;k++)
                                        {
                                            QString salesindex = CountList[j].SalesIndex.front();
                                            int xlen = SalesMap[salesindex].ProductIndex.count();
                                            for(int x = 0;x < xlen;x++)
                                            {
                                                QString newproduct = SalesMap[salesindex].ProductIndex[x];
                                                QString newwork = SalesMap[salesindex].WorkOrder[x];
                                                if(SalesIndexs.contains(newproduct))
                                                {
                                                    SalesIndexs[newproduct].append(newwork);
                                                }
                                                else
                                                {
                                                    QList<QString> newworkorder;
                                                    newworkorder.append(newwork);
                                                    SalesIndexs.insert(newproduct,newworkorder);
                                                }
                                            }
                                            CountList[j].SalesIndex.pop_front();
                                        }
                                    }
                                }
                                //printf("order:%s\n",p.toLatin1().data());
                                //printf("num:%d\n",next_order_num);
                                Index++;
                                //记录 order56 1
                                //
                                //int sec1 = orderBagStart + testcosttime56 * 60;
                                //int sec2 = testcosttime56 * 60;
                                //int sec3 = orderBagStart + testcosttime56 * 60 + next_order_num * bagtime;
                                QString tstr1 = QString("%1").arg(orderBagStart + testcosttime56 * 60);
                                QString tstr2 = QString("%1").arg(testcosttime56);// * 60);
                                QString tstr3 = QString("%1").arg(orderBagStart + testcosttime56 * 60 + next_order_num * bagtime);
                                //
                                OutputOrder neworder;
                                neworder.Index = QString("%1").arg(Index);
                                neworder.OrderType = order56[i].OrderType;
                                QList<QString> productindex;
                                productindex.append(p);
                                neworder.ProductIndex = productindex;
                                QList<int> productnum;
                                productnum.append(next_order_num);
                                neworder.ProductNum = productnum;
                                QList<QString> workorder;
                                neworder.WorkOrder = workorder;
                                neworder.BagStartTime = tstr1;
                                neworder.PourStartTime = "";
                                neworder.BagRestTime = tstr2;
                                neworder.PourRestTime = "";
                                neworder.EndTime = tstr3;


                                //合并连续的相同制令单
                                bool act_equal = false;
                                if(outputorder.length() > 0)
                                {
                                    if(outputorder.last().OrderType == neworder.OrderType)
                                    {
                                        if(outputorder.last().ProductIndex.length() == neworder.ProductIndex.length())
                                        {
                                            act_equal = true;
                                            int newlen = neworder.ProductIndex.length();
                                            for(int xlen = 0;xlen < newlen;xlen++)
                                            {
                                                if(outputorder.last().ProductIndex[xlen] != neworder.ProductIndex[xlen])
                                                {
                                                    act_equal = false;
                                                }
                                            }
                                        }
                                    }
                                }
                                if(!act_equal)
                                {
                                    outputorder.append(neworder);
                                }
                                else
                                {
                                    int newlen = outputorder.last().ProductNum.length();
                                    for(int xlen = 0;xlen < newlen;xlen++)
                                    {
                                        outputorder.last().ProductNum[xlen] += neworder.ProductNum[xlen];
                                    }
                                    outputorder.last().EndTime = neworder.EndTime;
                                }


                                //
                                orderBagStart += testcosttime56 * 60 + next_order_num * bagtime;
                                order56[i].ProductNum[p] -= next_order_num;
                                QString frontp = order56[i].DependProductIndex;
                                if(StockMap.contains(frontp))
                                {
                                    StockMap[frontp] -= next_order_num;
                                }
                                LastBagOrder = p;
                            }
                        }
                    }
                    else
                    {
                        if(sum7 == 0)
                        {//无灌包单,需等灌装再包装
                            int new_pournum = 0;
                            QString product = "";
                            foreach(QString temp_pourproduct, order34.keys())
                            {
                                if(order34[temp_pourproduct].ProductNum > new_pournum)
                                {
                                    new_pournum = order34[product].ProductNum;
                                    product = temp_pourproduct;
                                }
                            }

                            int costtime34 = 0;
                            if(LastPourOrder == "" || !PourCost.contains(LastPourOrder))
                            {
                                for(int j = 0; j < PourCost[product].length();j++)
                                {
                                    if(PourCost[product][j].ProcessType == 2)
                                    {//2:灌装
                                        int mLen = PourCost[product][j].Materiel.length();
                                        costtime34 += PourCost[product][j].MRestTime * mLen;
                                        costtime34 += PourCost[product][j].TRestTime;// * mLen;
                                    }
                                }
                            }
                            else
                            {
                                QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                                for(int j = 0; j < PourCost[LastPourOrder].length();j++)
                                {
                                    lastStepset.insert(PourCost[LastPourOrder][j].ProcessStep, PourCost[LastPourOrder][j].Materiel);
                                }
                                for(int j = 0; j < PourCost[product].length();j++)
                                {
                                    if(PourCost[product][j].ProcessType == 3)
                                    {//3:包装
                                        if(!lastStepset.contains(PourCost[product][j].ProcessStep))
                                        {
                                            int mLen = PourCost[product][j].Materiel.length();
                                            costtime34 += PourCost[product][j].MRestTime * mLen;
                                            costtime34 += PourCost[product][j].TRestTime;// * mLen;
                                        }
                                        else
                                        {
                                            QSet<QString> lastmaterielset;//上一工艺所需物料
                                            for(int k = 0; k < lastStepset[LastPourOrder].length();k++)
                                            {
                                                lastmaterielset << lastStepset[LastPourOrder][k];
                                            }
                                            for(int k = 0; k < PourCost[product][j].Materiel.length();k++)
                                            {
                                                int mLen = 0;
                                                if(!lastmaterielset.contains(PourCost[product][j].Materiel[k]))
                                                {
                                                    mLen ++;
                                                }
                                                costtime34 += PourCost[product][j].MRestTime * mLen;
                                                costtime34 += PourCost[product][j].TRestTime;// * mLen;
                                            }
                                        }
                                    }
                                }
                                lastStepset.clear();
                            }

                            Index++;
                            //记录 order4
                            //
                            QString nstr1 = QString("%1").arg(orderPourStart + costtime34 * 60);
                            QString nstr2 = QString("%1").arg(costtime34);
                            QString nstr3 = QString("%1").arg(orderPourStart + costtime34 * 60 + new_pournum * pourtime);
                            //
                            OutputOrder neworder;
                            neworder.Index = QString("%1").arg(Index);
                            neworder.OrderType = order34[product].OrderType;
                            QList<QString> productindex;
                            productindex.append(product);
                            neworder.ProductIndex = productindex;
                            QList<int> productnum;
                            productnum.append(new_pournum);
                            neworder.ProductNum = productnum;
                            QList<QString> workorder;
                            neworder.WorkOrder = workorder;
                            neworder.BagStartTime = "";
                            neworder.PourStartTime = nstr1;
                            neworder.BagRestTime = "";
                            neworder.PourRestTime = nstr2;
                            neworder.EndTime = nstr3;
                            neworder.DependIndex = "";
                            outputorder.append(neworder);
                            orderPourStart += new_pournum * pourtime + costtime34 * 60;
                            LastPourOrder = product;

                            StockMap[product] += new_pournum;
                            order34[product].ProductNum -= new_pournum;
                        }
                        else
                        {
                            First56 = false;
                        }
                    }
                }
                else
                {//否则,进仓
                    NoNum = 0;
                    QString p = order56[max_i].ProductNum.firstKey();
                    In_Product[p] += max_ordernum;
                    //更新 在库 齐套出库
                    for(int j = 0;j < CountList.length();j++)
                    {
                        if(CountList[j].OrderNum == 0)
                        {
                            continue;
                        }
                        int s = 400;
                        foreach(QString product, CountList[j].ProductMap.keys())
                        {
                            int actualnum = int(In_Product[product] / CountList[j].ProductMap[product]);
                            if(actualnum < s)
                            {
                                s = actualnum;
                            }
                        }
                        if(s > 0)
                        {
                            int delta = 0;
                            if(CountList[j].OrderNum > s)
                            {
                                delta = s;
                                CountList[j].OrderNum -= s;
                                foreach(QString product, CountList[j].ProductMap.keys())
                                {
                                    In_Product[product] -= delta * CountList[j].ProductMap[product];
                                }
                            }
                            else
                            {
                                delta = CountList[j].OrderNum;
                                CountList[j].OrderNum = 0;
                                foreach(QString product, CountList[j].ProductMap.keys())
                                {
                                    In_Product[product] -= delta * CountList[j].ProductMap[product];
                                }
                            }
                            //printf("delta2:%d\n",delta);

                            for(int k = 0;k < delta;k++)
                            {
                                QString salesindex = CountList[j].SalesIndex.front();
                                int xlen = SalesMap[salesindex].ProductIndex.count();
                                for(int x = 0;x < xlen;x++)
                                {
                                    QString newproduct = SalesMap[salesindex].ProductIndex[x];
                                    QString newwork = SalesMap[salesindex].WorkOrder[x];
                                    if(SalesIndexs.contains(newproduct))
                                    {
                                        SalesIndexs[newproduct].append(newwork);
                                    }
                                    else
                                    {
                                        QList<QString> newworkorder;
                                        newworkorder.append(newwork);
                                        SalesIndexs.insert(newproduct,newworkorder);
                                    }
                                }
                                CountList[j].SalesIndex.pop_front();
                            }
                        }
                    }
                    //printf("order:%s\n",p.toLatin1().data());
                    //printf("num:%d\n",max_ordernum);
                    Index++;
                    //记录 order56 2
                    //
                    //int sec1 = orderPourStart + max_waittime + max_cost34 * 60;
                    //int sec2 = max_cost34 * 60;
                    //int sec3 = orderPourStart + max_waittime + max_cost34 * 60 + max_pournum * pourtime;
                    QString tstr1 = QString("%1").arg(orderBagStart + max_waittime + max_cost56 * 60);
                    QString tstr2 = QString("%1").arg(max_cost56);// * 60);
                    QString tstr3 = QString("%1").arg(orderBagStart + max_waittime + max_cost56 * 60 + max_ordernum * bagtime);
                    //
                    OutputOrder neworder;
                    neworder.Index = QString("%1").arg(Index);
                    neworder.OrderType = order56[max_i].OrderType;
                    QList<QString> productindex;
                    productindex.append(p);
                    neworder.ProductIndex = productindex;
                    QList<int> productnum;
                    productnum.append(max_ordernum);
                    neworder.ProductNum = productnum;
                    QList<QString> workorder;
                    neworder.WorkOrder = workorder;
                    neworder.BagStartTime = tstr1;
                    neworder.PourStartTime = "";
                    neworder.BagRestTime = tstr2;
                    neworder.PourRestTime = "";
                    neworder.EndTime = tstr3;
                    neworder.DependIndex = "";


                    //合并连续的相同制令单
                    bool act_equal = false;
                    if(outputorder.length() > 0)
                    {
                        if(outputorder.last().OrderType == neworder.OrderType)
                        {
                            if(outputorder.last().ProductIndex.length() == neworder.ProductIndex.length())
                            {
                                act_equal = true;
                                int newlen = neworder.ProductIndex.length();
                                for(int xlen = 0;xlen < newlen;xlen++)
                                {
                                    if(outputorder.last().ProductIndex[xlen] != neworder.ProductIndex[xlen])
                                    {
                                        act_equal = false;
                                    }
                                }
                            }
                        }
                    }
                    if(!act_equal)
                    {
                        outputorder.append(neworder);
                    }
                    else
                    {
                        int newlen = outputorder.last().ProductNum.length();
                        for(int xlen = 0;xlen < newlen;xlen++)
                        {
                            outputorder.last().ProductNum[xlen] += neworder.ProductNum[xlen];
                        }
                        outputorder.last().EndTime = neworder.EndTime;
                    }


                    //
                    QString frontp = order56[max_i].DependProductIndex;
                    if(max_pournum > 0)
                    {
                        StockMap[frontp] = StockMap[frontp] - max_ordernum + max_pournum;
                        Index++;
                        //记录 order4
                        //
                        QString nstr1 = QString("%1").arg(orderPourStart + max_cost34 * 60);
                        QString nstr2 = QString("%1").arg(max_cost34);
                        QString nstr3 = QString("%1").arg(orderPourStart + max_cost34 * 60 + max_pournum * pourtime);
                        //
                        OutputOrder neworder;
                        neworder.Index = QString("%1").arg(Index);
                        neworder.OrderType = order34[frontp].OrderType;
                        QList<QString> productindex;
                        productindex.append(frontp);
                        neworder.ProductIndex = productindex;
                        QList<int> productnum;
                        productnum.append(max_pournum);
                        neworder.ProductNum = productnum;
                        QList<QString> workorder;
                        neworder.WorkOrder = workorder;
                        neworder.BagStartTime = "";
                        neworder.PourStartTime = nstr1;
                        neworder.BagRestTime = "";
                        neworder.PourRestTime = nstr2;
                        neworder.EndTime = nstr3;
                        neworder.DependIndex = QString("%1").arg(Index - 1);


                        //合并连续的相同制令单
                        bool act_equal = false;
                        if(outputorder.length() > 0)
                        {
                            if(outputorder.last().OrderType == neworder.OrderType)
                            {
                                if(outputorder.last().ProductIndex.length() == neworder.ProductIndex.length())
                                {
                                    act_equal = true;
                                    int newlen = neworder.ProductIndex.length();
                                    for(int xlen = 0;xlen < newlen;xlen++)
                                    {
                                        if(outputorder.last().ProductIndex[xlen] != neworder.ProductIndex[xlen])
                                        {
                                            act_equal = false;
                                        }
                                    }
                                }
                            }
                        }
                        if(!act_equal)
                        {
                            outputorder.append(neworder);
                        }
                        else
                        {
                            int newlen = outputorder.last().ProductNum.length();
                            for(int xlen = 0;xlen < newlen;xlen++)
                            {
                                outputorder.last().ProductNum[xlen] += neworder.ProductNum[xlen];
                            }
                            outputorder.last().EndTime = neworder.EndTime;
                        }
                    }
                    order56[max_i].ProductNum[p] -= max_ordernum;
                    order34[frontp].ProductNum -= max_pournum;
                    LastBagOrder = p;
                    if(max_pournum > 0)
                    {
                        orderPourStart += max_pournum * pourtime + max_cost34 * 60;
                        LastPourOrder = frontp;
                    }
                    orderBagStart += max_ordernum * bagtime + max_cost56 * 60 + max_waittime;
                }
            }
            if (((sum7 != 0) && !First56) || sum56 == 0)
            {
                //遍历计算各制令单入库数量、可出库数量、灌装数量、换型换料时长
                //int max_count = 0;
                int max_num = 0;
                int max_i = 0;
                QMap<QString,int> max_count;
                int max_cost56 = 0;
                int max_cost7 = 0;
                double max_cost_rate = 0;
                int max_localpourstart = 0;
                for(int i = 0;i < order7.length();i++)
                {
                    int tempsum = 0;
                    foreach(int tempnum,order7[i].ProductNum.values())
                    {
                        tempsum += tempnum;
                    }
                    if(tempsum == 0)
                    {
                        continue;
                    }
                    int total = 0;
                    QMap<QString,int> New_product;//在库产品
                    foreach(QString product,In_Product.keys())
                    {
                        if(In_Product[product] > 0)
                        {
                            New_product.insert(product,In_Product[product]);
                        }
                    }
                    QSet<QString> thisset;//当前制令单产品
                    QMap<QString,int> thiscount;
                    foreach(QString tempp,order7[i].ProductNum.keys())
                    {
                        thisset << tempp;
                        thiscount.insert(tempp,0);
                    }
                    for(int j = 0;j < CountList.length();j++)
                    {
                        if(CountList[j].OrderNum == 0)
                        {
                            continue;
                        }
                        QSet<QString> newset;
                        foreach(QString newpro, CountList[j].ProductMap.keys())
                        {
                            newset << newpro;
                        }
                        QSet<QString> interset = newset & thisset;
                        if(interset.count() == 0)
                        {
                            continue;
                        }
                        bool allinproduct = true;//是否都在库
                        foreach(QString product,newset)
                        {
                            if(thisset.contains(product))
                            {
                                continue;
                            }
                            if(!New_product.contains(product))
                            {
                                allinproduct = false;
                            }
                        }
                        if(!allinproduct)
                        {
                            continue;
                        }

                        int min_num = CountList[j].OrderNum;
                        foreach(QString product,CountList[j].ProductMap.keys())
                        {
                            if(thisset.contains(product))
                            {
                                continue;
                            }
                            int permitnum = int(New_product[product] / CountList[j].ProductMap[product]);
                            if(min_num > permitnum)
                            {
                                min_num = permitnum;
                            }
                        }
                        if(min_num > 0)
                        {
                            foreach(QString product,CountList[j].ProductMap.keys())
                            {
                                if(thisset.contains(product))
                                {
                                    thiscount[product] += min_num * CountList[j].ProductMap[product];
                                    total += min_num * CountList[j].ProductMap[product];//22.8.8  更新（漏记单个齐套）
                                    continue;
                                }
                                New_product[product] -= min_num * CountList[j].ProductMap[product];
                            }
                        }
                    }
                    New_product.clear();
                    if(total > 0)
                    {
                        int permitnum = 0;
                        foreach(QString product,In_Product.keys())
                        {
                            permitnum += In_Product[product];
                        }
                        int test_next_order_num = allsetnum - permitnum + total;
                        int costtime56 = 0;
                        int costtime7 = 0;
                        int localpourstart = orderBagStart;
                        QString localLastBagOrder = LastBagOrder;
                        QString localLastPourOrder = LastPourOrder;
                        foreach(QString product,thisset)
                        {
                            if(thiscount[product] > 0)
                            {
                                if(localLastBagOrder == "" || !BagCost.contains(localLastBagOrder))
                                {
                                    for(int j = 0; j < BagCost[product].length();j++)
                                    {
                                        if(BagCost[product][j].ProcessType == 3)
                                        {//3:包装
                                            int mLen = BagCost[product][j].Materiel.length();
                                            costtime56 += BagCost[product][j].MRestTime * mLen;
                                            costtime56 += BagCost[product][j].TRestTime;// * mLen;
                                        }
                                    }
                                }
                                else
                                {
                                    QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                                    for(int j = 0; j < BagCost[localLastBagOrder].length();j++)
                                    {
                                        lastStepset.insert(BagCost[localLastBagOrder][j].ProcessStep, BagCost[localLastBagOrder][j].Materiel);
                                    }
                                    for(int j = 0; j < BagCost[product].length();j++)
                                    {
                                        if(BagCost[product][j].ProcessType == 3)
                                        {//3:包装
                                            if(!lastStepset.contains(BagCost[product][j].ProcessStep))
                                            {
                                                int mLen = BagCost[product][j].Materiel.length();
                                                costtime56 += BagCost[product][j].MRestTime * mLen;
                                                costtime56 += BagCost[product][j].TRestTime;// * mLen;
                                            }
                                            else
                                            {
                                                QSet<QString> lastmaterielset;//上一工艺所需物料
                                                for(int k = 0; k < lastStepset[localLastBagOrder].length();k++)
                                                {
                                                    lastmaterielset << lastStepset[localLastBagOrder][k];
                                                }
                                                for(int k = 0; k < BagCost[product][j].Materiel.length();k++)
                                                {
                                                    int mLen = 0;
                                                    if(!lastmaterielset.contains(BagCost[product][j].Materiel[k]))
                                                    {
                                                        mLen ++;
                                                    }
                                                    costtime56 += BagCost[product][j].MRestTime * mLen;
                                                    costtime56 += BagCost[product][j].TRestTime;// * mLen;
                                                }
                                            }
                                        }
                                    }
                                }
                                if(localLastPourOrder == "" || !PourCost.contains(localLastPourOrder))
                                {
                                    for(int j = 0; j < PourCost[product].length();j++)
                                    {
                                        if(PourCost[product][j].ProcessType == 2)
                                        {//2:灌装
                                            int mLen = PourCost[product][j].Materiel.length();
                                            costtime7 += PourCost[product][j].MRestTime * mLen;
                                            costtime7 += PourCost[product][j].TRestTime;// * mLen;
                                        }
                                    }
                                }
                                else
                                {
                                    QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                                    for(int j = 0; j < PourCost[localLastPourOrder].length();j++)
                                    {
                                        lastStepset.insert(PourCost[localLastPourOrder][j].ProcessStep, PourCost[localLastPourOrder][j].Materiel);
                                    }
                                    for(int j = 0; j < PourCost[product].length();j++)
                                    {
                                        if(PourCost[product][j].ProcessType == 3)
                                        {//3:包装
                                            if(!lastStepset.contains(PourCost[product][j].ProcessStep))
                                            {
                                                int mLen = PourCost[product][j].Materiel.length();
                                                costtime7 += PourCost[product][j].MRestTime * mLen;
                                                costtime7 += PourCost[product][j].TRestTime;// * mLen;
                                            }
                                            else
                                            {
                                                QSet<QString> lastmaterielset;//上一工艺所需物料
                                                for(int k = 0; k < lastStepset[localLastPourOrder].length();k++)
                                                {
                                                    lastmaterielset << lastStepset[localLastPourOrder][k];
                                                }
                                                for(int k = 0; k < PourCost[product][j].Materiel.length();k++)
                                                {
                                                    int mLen = 0;
                                                    if(!lastmaterielset.contains(PourCost[product][j].Materiel[k]))
                                                    {
                                                        mLen ++;
                                                    }
                                                    costtime7 += PourCost[product][j].MRestTime * mLen;
                                                    costtime7 += PourCost[product][j].TRestTime;// * mLen;
                                                }
                                            }
                                        }
                                    }
                                }
                                if(localLastPourOrder == LastPourOrder)
                                {
                                    if(orderPourStart < orderBagStart)
                                    {
                                        int lasttime = 0;
                                        lasttime = orderBagStart - orderPourStart > costtime7 * 60 ? costtime7 * 60 : orderBagStart - orderPourStart;
                                        localpourstart = orderBagStart - lasttime;
                                    }
                                }
                                localLastBagOrder = product;
                                localLastPourOrder = product;
                            }
                        }
                        double cost_rate = static_cast<double>(static_cast<double>(test_next_order_num * bagtime) / (costtime56 * 60 + test_next_order_num * bagtime));
                        if(cost_rate > max_cost_rate)
                        {
                            max_num = total;
                            max_i = i;
                            max_count = thiscount;
                            max_cost56 = costtime56;
                            max_cost7 = costtime7;
                            max_cost_rate = cost_rate;
                            max_localpourstart = localpourstart;
                        }
                    }
                }
                if(max_num == 0)
                {
                    //可出库数量为0
                    NoNum++;
                    //计算剩余库存中可直接入库数量,进仓
                    Not7Set = 1;
                    int permitnum = 0;
                    foreach(QString product,In_Product.keys())
                    {
                        permitnum += In_Product[product];
                    }
                    if(sum7 < allsetnum - permitnum)
                    {
                        for(int i = 0;i < order7.length();i++)
                        {
                            int tempsum = 0;
                            foreach(int tempnum,order7[i].ProductNum.values())
                            {
                                tempsum += tempnum;
                            }
                            if(tempsum == 0)
                            {
                                continue;
                            }
                            int localpourstart = orderBagStart;
                            QString localLastBagOrder = LastBagOrder;
                            QString localLastPourOrder = LastPourOrder;
                            int costtime56 = 0;
                            int costtime7 = 0;
                            foreach(QString product,order7[i].ProductNum.keys())
                            {
                                if(order7[i].ProductNum[product] > 0)
                                {
                                    int next_order_num = order7[i].ProductNum[product];
                                    if(localLastBagOrder == "" || !BagCost.contains(localLastBagOrder))
                                    {
                                        for(int j = 0; j < BagCost[product].length();j++)
                                        {
                                            if(BagCost[product][j].ProcessType == 3)
                                            {//3:包装
                                                int mLen = BagCost[product][j].Materiel.length();
                                                costtime56 += BagCost[product][j].MRestTime * mLen;
                                                costtime56 += BagCost[product][j].TRestTime;// * mLen;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                                        for(int j = 0; j < BagCost[localLastBagOrder].length();j++)
                                        {
                                            lastStepset.insert(BagCost[localLastBagOrder][j].ProcessStep, BagCost[localLastBagOrder][j].Materiel);
                                        }
                                        for(int j = 0; j < BagCost[product].length();j++)
                                        {
                                            if(BagCost[product][j].ProcessType == 3)
                                            {//3:包装
                                                if(!lastStepset.contains(BagCost[product][j].ProcessStep))
                                                {
                                                    int mLen = BagCost[product][j].Materiel.length();
                                                    costtime56 += BagCost[product][j].MRestTime * mLen;
                                                    costtime56 += BagCost[product][j].TRestTime;// * mLen;
                                                }
                                                else
                                                {
                                                    QSet<QString> lastmaterielset;//上一工艺所需物料
                                                    for(int k = 0; k < lastStepset[localLastBagOrder].length();k++)
                                                    {
                                                        lastmaterielset << lastStepset[localLastBagOrder][k];
                                                    }
                                                    for(int k = 0; k < BagCost[product][j].Materiel.length();k++)
                                                    {
                                                        int mLen = 0;
                                                        if(!lastmaterielset.contains(BagCost[product][j].Materiel[k]))
                                                        {
                                                            mLen ++;
                                                        }
                                                        costtime56 += BagCost[product][j].MRestTime * mLen;
                                                        costtime56 += BagCost[product][j].TRestTime;// * mLen;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if(localLastPourOrder == "" || !PourCost.contains(localLastPourOrder))
                                    {
                                        for(int j = 0; j < PourCost[product].length();j++)
                                        {
                                            if(PourCost[product][j].ProcessType == 2)
                                            {//2:灌装
                                                int mLen = PourCost[product][j].Materiel.length();
                                                costtime7 += PourCost[product][j].MRestTime * mLen;
                                                costtime7 += PourCost[product][j].TRestTime;// * mLen;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                                        for(int j = 0; j < PourCost[localLastPourOrder].length();j++)
                                        {
                                            lastStepset.insert(PourCost[localLastPourOrder][j].ProcessStep, PourCost[localLastPourOrder][j].Materiel);
                                        }
                                        for(int j = 0; j < PourCost[product].length();j++)
                                        {
                                            if(PourCost[product][j].ProcessType == 3)
                                            {//3:包装
                                                if(!lastStepset.contains(PourCost[product][j].ProcessStep))
                                                {
                                                    int mLen = PourCost[product][j].Materiel.length();
                                                    costtime7 += PourCost[product][j].MRestTime * mLen;
                                                    costtime7 += PourCost[product][j].TRestTime;// * mLen;
                                                }
                                                else
                                                {
                                                    QSet<QString> lastmaterielset;//上一工艺所需物料
                                                    for(int k = 0; k < lastStepset[localLastPourOrder].length();k++)
                                                    {
                                                        lastmaterielset << lastStepset[localLastPourOrder][k];
                                                    }
                                                    for(int k = 0; k < PourCost[product][j].Materiel.length();k++)
                                                    {
                                                        int mLen = 0;
                                                        if(!lastmaterielset.contains(PourCost[product][j].Materiel[k]))
                                                        {
                                                            mLen ++;
                                                        }
                                                        costtime7 += PourCost[product][j].MRestTime * mLen;
                                                        costtime7 += PourCost[product][j].TRestTime;// * mLen;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if(localLastPourOrder == LastPourOrder)
                                    {
                                        if(orderPourStart < orderBagStart)
                                        {
                                            int lasttime = 0;
                                            lasttime = orderBagStart - orderPourStart > costtime7 * 60 ? costtime7 * 60 : orderBagStart - orderPourStart;
                                            localpourstart = orderBagStart - lasttime;
                                        }
                                    }
                                    localLastBagOrder = product;
                                    localLastPourOrder = product;
                                    In_Product[product] += next_order_num;
                                }
                            }
                            //更新 在库 齐套出库
                            for(int j = 0;j < CountList.length();j++)
                            {
                                if(CountList[j].OrderNum == 0)
                                {
                                    continue;
                                }
                                int s = 400;
                                foreach(QString product, CountList[j].ProductMap.keys())
                                {
                                    int actualnum = int(In_Product[product] / CountList[j].ProductMap[product]);
                                    if(actualnum < s)
                                    {
                                        s = actualnum;
                                    }
                                }
                                if(s > 0)
                                {
                                    int delta = 0;
                                    if(CountList[j].OrderNum > s)
                                    {
                                        delta = s;
                                        CountList[j].OrderNum -= s;
                                        foreach(QString product, CountList[j].ProductMap.keys())
                                        {
                                            In_Product[product] -= delta * CountList[j].ProductMap[product];
                                        }
                                    }
                                    else
                                    {
                                        delta = CountList[j].OrderNum;
                                        CountList[j].OrderNum = 0;
                                        foreach(QString product, CountList[j].ProductMap.keys())
                                        {
                                            In_Product[product] -= delta * CountList[j].ProductMap[product];
                                        }
                                    }
                                    for(int k = 0;k < delta;k++)
                                    {
                                        QString salesindex = CountList[j].SalesIndex.front();
                                        int xlen = SalesMap[salesindex].ProductIndex.count();
                                        for(int x = 0;x < xlen;x++)
                                        {
                                            QString newproduct = SalesMap[salesindex].ProductIndex[x];
                                            QString newwork = SalesMap[salesindex].WorkOrder[x];
                                            if(SalesIndexs.contains(newproduct))
                                            {
                                                SalesIndexs[newproduct].append(newwork);
                                            }
                                            else
                                            {
                                                QList<QString> newworkorder;
                                                newworkorder.append(newwork);
                                                SalesIndexs.insert(newproduct,newworkorder);
                                            }
                                        }
                                        CountList[j].SalesIndex.pop_front();
                                    }
                                }
                            }
                            Index++;
                            int tempsum2 = 0;
                            foreach(int tempnum,order7[i].ProductNum.values())
                            {
                                tempsum2 += tempnum;
                            }
                            int tempbagtimealpha = localpourstart + costtime7 * 60 > orderBagStart + costtime56 * 60 ? localpourstart + costtime7 * 60 : orderBagStart + costtime56 * 60;
                            tempbagtimealpha = tempbagtimealpha + tempsum2 * bagtime;
                            //记录 order7
                            //
                            //int sec1 = orderBagStart;
                            //int sec2 = localpourstart;
                            //int sec3 = costtime56 * 60;
                            //int sec4 = costtime7 * 60;
                            //int sec5 = tempbagtimealpha;
                            QString tstr1 = QString("%1").arg(orderBagStart);
                            QString tstr2 = QString("%1").arg(localpourstart);
                            QString tstr3 = QString("%1").arg(costtime56);
                            QString tstr4 = QString("%1").arg(costtime7);
                            QString tstr5 = QString("%1").arg(tempbagtimealpha);
                            //
                            OutputOrder neworder;
                            neworder.Index = QString("%1").arg(Index);
                            neworder.OrderType = order7[i].OrderType;
                            QList<QString> productindex;
                            foreach(QString product,order7[i].ProductNum.keys())
                            {
                                productindex.append(product);
                            }
                            neworder.ProductIndex = productindex;
                            QList<int> productnum;
                            foreach(int tempnum,order7[i].ProductNum.values())
                            {
                                productnum.append(tempnum);
                            }
                            neworder.ProductNum = productnum;
                            QList<QString> workorder;
                            neworder.WorkOrder = workorder;
                            neworder.BagStartTime = tstr1;
                            neworder.PourStartTime = tstr2;
                            neworder.BagRestTime = tstr3;
                            neworder.PourRestTime = tstr4;
                            neworder.EndTime = tstr5;
                            neworder.DependIndex = "";

                            //合并连续的相同制令单
                            bool act_equal = false;
                            if(outputorder.length() > 0)
                            {
                                if(outputorder.last().OrderType == neworder.OrderType)
                                {
                                    if(outputorder.last().ProductIndex.length() == neworder.ProductIndex.length())
                                    {
                                        act_equal = true;
                                        int newlen = neworder.ProductIndex.length();
                                        for(int xlen = 0;xlen < newlen;xlen++)
                                        {
                                            if(outputorder.last().ProductIndex[xlen] != neworder.ProductIndex[xlen])
                                            {
                                                act_equal = false;
                                            }
                                        }
                                    }
                                }
                            }
                            if(!act_equal)
                            {
                                outputorder.append(neworder);
                            }
                            else
                            {
                                int newlen = outputorder.last().ProductNum.length();
                                for(int xlen = 0;xlen < newlen;xlen++)
                                {
                                    outputorder.last().ProductNum[xlen] += neworder.ProductNum[xlen];
                                }
                                outputorder.last().EndTime = neworder.EndTime;
                            }

                            //
                            orderBagStart = tempbagtimealpha;
                            orderPourStart = orderBagStart;
                            foreach(QString product,order7[i].ProductNum.keys())
                            {
                                order7[i].ProductNum[product] = 0;
                            }
                        }
                    }
                    else
                    {
                        First56 = true;
                    }
                }
                else
                {//否则,进仓
                    NoNum = 0;
                    Not7Set = 0;
                    int test_sum = 0;
                    int actual_sum = 0;
                    foreach(QString product, max_count.keys())
                    {
                        actual_sum += max_count[product];
                        test_sum += order7[max_i].ProductNum[product];
                    }
                    int permitnum = 0;
                    foreach(QString product,In_Product.keys())
                    {
                        permitnum += In_Product[product];
                    }
                    int last_order_num = allsetnum - permitnum + max_num - actual_sum;
                    int extra_len = max_count.count();
                    int max_order_num = 0;
                    QMap<QString,int> next_count;
                    foreach(QString product, max_count.keys())
                    {
                        if(max_count.count() > 1)
                        {
                            int extra_order_num = 0;
                            if (test_sum >= allsetnum - permitnum + max_num)
                            {
                                if(order7[max_i].ProductNum[product] - max_count[product] < int(last_order_num / extra_len))
                                {
                                    extra_order_num = order7[max_i].ProductNum[product] - max_count[product];
                                    if (extra_order_num < 0)
                                    {
                                        extra_order_num = 0;
                                    }
                                }
                                else
                                {
                                    extra_order_num = int(last_order_num / extra_len);
                                    if (extra_order_num < 0)
                                    {
                                        extra_order_num = 0;
                                    }
                                }
                                max_order_num = max_count[product] + extra_order_num;
                                last_order_num -= extra_order_num;
                                extra_len -= 1;
                            }
                            else
                            {
                                max_order_num = order7[max_i].ProductNum[product];
                            }
                        }
                        else
                        {
                            if(max_order_num < max_count[product])
                            {
                                max_order_num = max_count[product];
                            }
                            if(max_order_num < pouroncenum)
                            {
                                max_order_num = pouroncenum;
                            }
                            if(max_order_num > last_order_num)
                            {
                                max_order_num = last_order_num;
                            }
                            if(max_order_num > order7[max_i].ProductNum[product])
                            {
                                max_order_num = order7[max_i].ProductNum[product];
                            }
                        }
                        In_Product[product] += max_order_num;
                        next_count.insert(product, max_order_num);
                    }
                    //更新 在库 齐套出库
                    for(int j = 0;j < CountList.length();j++)
                    {
                        if(CountList[j].OrderNum == 0)
                        {
                            continue;
                        }
                        int s = 400;
                        foreach(QString product, CountList[j].ProductMap.keys())
                        {
                            int actualnum = int(In_Product[product] / CountList[j].ProductMap[product]);
                            if(actualnum < s)
                            {
                                s = actualnum;
                            }
                        }
                        if(s > 0)
                        {
                            int delta = 0;
                            if(CountList[j].OrderNum > s)
                            {
                                delta = s;
                                CountList[j].OrderNum -= s;
                                foreach(QString product, CountList[j].ProductMap.keys())
                                {
                                    In_Product[product] -= delta * CountList[j].ProductMap[product];
                                }
                            }
                            else
                            {
                                delta = CountList[j].OrderNum;
                                CountList[j].OrderNum = 0;
                                foreach(QString product, CountList[j].ProductMap.keys())
                                {
                                    In_Product[product] -= delta * CountList[j].ProductMap[product];
                                }
                            }
                            for(int k = 0;k < delta;k++)
                            {
                                QString salesindex = CountList[j].SalesIndex.front();
                                int xlen = SalesMap[salesindex].ProductIndex.count();
                                for(int x = 0;x < xlen;x++)
                                {
                                    QString newproduct = SalesMap[salesindex].ProductIndex[x];
                                    QString newwork = SalesMap[salesindex].WorkOrder[x];
                                    if(SalesIndexs.contains(newproduct))
                                    {
                                        SalesIndexs[newproduct].append(newwork);
                                    }
                                    else
                                    {
                                        QList<QString> newworkorder;
                                        newworkorder.append(newwork);
                                        SalesIndexs.insert(newproduct,newworkorder);
                                    }
                                }
                                CountList[j].SalesIndex.pop_front();
                            }
                        }
                    }
                    Index++;
                    //记录 order7
                    int next_num = 0;
                    foreach(QString product, next_count.keys())
                    {
                        next_num += next_count[product];
                    }
                    int tempbagtimealpha = max_localpourstart + max_cost7 * 60;
                    if(tempbagtimealpha < orderBagStart + max_cost56 * 60)
                    {
                        tempbagtimealpha = orderBagStart + max_cost56 * 60;
                    }
                    tempbagtimealpha += next_num * bagtime;
                    //记录 order7
                    //
                    //int sec1 = orderBagStart;
                    //int sec2 = max_localpourstart;
                    //int sec3 = max_cost56 * 60;
                    //int sec4 = max_cost7 * 60;
                    //int sec5 = tempbagtimealpha;
                    QString tstr1 = QString("%1").arg(orderBagStart);
                    QString tstr2 = QString("%1").arg(max_localpourstart);
                    QString tstr3 = QString("%1").arg(max_cost56);
                    QString tstr4 = QString("%1").arg(max_cost7);
                    QString tstr5 = QString("%1").arg(tempbagtimealpha);
                    //
                    OutputOrder neworder;
                    neworder.Index = QString("%1").arg(Index);
                    neworder.OrderType = order7[max_i].OrderType;
                    QList<QString> productindex;
                    QList<int> productnum;
                    foreach(QString product,order7[max_i].ProductNum.keys())
                    {
                        productindex.append(product);
                        productnum.append(next_count[product]);//22.8.8 更新
                    }
                    neworder.ProductIndex = productindex;
                    neworder.ProductNum = productnum;
                    QList<QString> workorder;
                    neworder.WorkOrder = workorder;
                    neworder.BagStartTime = tstr1;
                    neworder.PourStartTime = tstr2;
                    neworder.BagRestTime = tstr3;
                    neworder.PourRestTime = tstr4;
                    neworder.EndTime = tstr5;
                    neworder.DependIndex = "";


                    //合并连续的相同制令单
                    bool act_equal = false;
                    if(outputorder.length() > 0)
                    {
                        if(outputorder.last().OrderType == neworder.OrderType)
                        {
                            if(outputorder.last().ProductIndex.length() == neworder.ProductIndex.length())
                            {
                                act_equal = true;
                                int newlen = neworder.ProductIndex.length();
                                for(int xlen = 0;xlen < newlen;xlen++)
                                {
                                    if(outputorder.last().ProductIndex[xlen] != neworder.ProductIndex[xlen])
                                    {
                                        act_equal = false;
                                    }
                                }
                            }
                        }
                    }
                    if(!act_equal)
                    {
                        outputorder.append(neworder);
                    }
                    else
                    {
                        int newlen = outputorder.last().ProductNum.length();
                        for(int xlen = 0;xlen < newlen;xlen++)
                        {
                            outputorder.last().ProductNum[xlen] += neworder.ProductNum[xlen];
                        }
                        outputorder.last().EndTime = neworder.EndTime;
                    }


                    //
                    orderBagStart = tempbagtimealpha;
                    orderPourStart = orderBagStart;
                    foreach(QString product, next_count.keys())
                    {
                        order7[max_i].ProductNum[product] -= next_count[product];
                    }
                    QString p = order7[max_i].ProductNum.firstKey();
                    LastBagOrder = p;
                    LastPourOrder = p;
                }
                max_count.clear();
            }
            if(NoNum > 10)
            {
                SalesMap.clear();
                order34.clear();
                order56.clear();
                order7.clear();
                StockMap.clear();
                In_Product.clear();
                CountList.clear();
                outputorder.clear();
                BagCost.clear();
                PourCost.clear();
                SalesIndexs.clear();
                return 9;
            }
        }
        //printf("finished Order\n");
        //printf("Sales len%d\n",SalesIndexs.keys().length());
    //    foreach(QString product, SalesIndexs.keys())
    //    {
    //        foreach(QString salesindex,SalesIndexs[product])
    //        {
    //            printf("product:%s , work:%s\n",product.toLatin1().data(),salesindex.toLatin1().data());
    //        }
    //    }
        foreach(QString product, order34.keys())
        {//剩余制令单34排产
            int new_pournum = order34[product].ProductNum;
            if(new_pournum == 0)
            {
                continue;
            }

            int costtime34 = 0;
            if(LastPourOrder == "" || !PourCost.contains(LastPourOrder))
            {
                for(int j = 0; j < PourCost[product].length();j++)
                {
                    if(PourCost[product][j].ProcessType == 2)
                    {//2:灌装
                        int mLen = PourCost[product][j].Materiel.length();
                        costtime34 += PourCost[product][j].MRestTime * mLen;
                        costtime34 += PourCost[product][j].TRestTime;// * mLen;
                    }
                }
            }
            else
            {
                QMap<QString,QList<QString>> lastStepset;//上一制令单工艺路线
                for(int j = 0; j < PourCost[LastPourOrder].length();j++)
                {
                    lastStepset.insert(PourCost[LastPourOrder][j].ProcessStep, PourCost[LastPourOrder][j].Materiel);
                }
                for(int j = 0; j < PourCost[product].length();j++)
                {
                    if(PourCost[product][j].ProcessType == 3)
                    {//3:包装
                        if(!lastStepset.contains(PourCost[product][j].ProcessStep))
                        {
                            int mLen = PourCost[product][j].Materiel.length();
                            costtime34 += PourCost[product][j].MRestTime * mLen;
                            costtime34 += PourCost[product][j].TRestTime;// * mLen;
                        }
                        else
                        {
                            QSet<QString> lastmaterielset;//上一工艺所需物料
                            for(int k = 0; k < lastStepset[LastPourOrder].length();k++)
                            {
                                lastmaterielset << lastStepset[LastPourOrder][k];
                            }
                            for(int k = 0; k < PourCost[product][j].Materiel.length();k++)
                            {
                                int mLen = 0;
                                if(!lastmaterielset.contains(PourCost[product][j].Materiel[k]))
                                {
                                    mLen ++;
                                }
                                costtime34 += PourCost[product][j].MRestTime * mLen;
                                costtime34 += PourCost[product][j].TRestTime;// * mLen;
                            }
                        }
                    }
                }
                lastStepset.clear();
            }

            Index++;
            //记录 order4
            //
            QString nstr1 = QString("%1").arg(orderPourStart + costtime34 * 60);
            QString nstr2 = QString("%1").arg(costtime34);
            QString nstr3 = QString("%1").arg(orderPourStart + costtime34 * 60 + new_pournum * pourtime);
            //
            OutputOrder neworder;
            neworder.Index = QString("%1").arg(Index);
            neworder.OrderType = order34[product].OrderType;
            QList<QString> productindex;
            productindex.append(product);
            neworder.ProductIndex = productindex;
            QList<int> productnum;
            productnum.append(new_pournum);
            neworder.ProductNum = productnum;
            QList<QString> workorder;
            neworder.WorkOrder = workorder;
            neworder.BagStartTime = "";
            neworder.PourStartTime = nstr1;
            neworder.BagRestTime = "";
            neworder.PourRestTime = nstr2;
            neworder.EndTime = nstr3;
            neworder.DependIndex = "";
            outputorder.append(neworder);
            orderPourStart += new_pournum * pourtime + costtime34 * 60;
            LastPourOrder = product;

            StockMap[product] += new_pournum;
            order34[product].ProductNum -= new_pournum;
        }
        for(int i = 0;i < outputorder.count();i++)
        {
            int plen = outputorder[i].ProductIndex.count();
            for(int j = 0;j < plen;j++)
            {
                if(outputorder[i].OrderType == 3 || outputorder[i].OrderType == 4)
                {
                    QString p = outputorder[i].ProductIndex.first();
                    QString newwork = order34[p].WorkOrder.front();
                    outputorder[i].WorkOrder.append(newwork);
                    continue;
                }
                QString product = outputorder[i].ProductIndex[j];
                int pnum = outputorder[i].ProductNum[j];
                //printf("product:%s\n",product.toLatin1().data());
                //printf("len:%d\n",pnum);
                for(int n = 0;n < pnum;n++)
                {
                    if(SalesIndexs[product].length() == 0)
                    {
                        return 6;
                    }
                    QString newwork = SalesIndexs[product].front();
                    outputorder[i].WorkOrder.append(newwork);
                    SalesIndexs[product].pop_front();
                }
            }
        }
        //printf("finished Sales");
        QJsonArray newArray;
        foreach(OutputOrder newoutorder, outputorder)
        {
            QJsonObject newobject;
            newobject.insert("Index",newoutorder.Index);
            newobject.insert("OrderType",newoutorder.OrderType);
            QJsonArray newArray1;
            foreach(QString productindex, newoutorder.ProductIndex)
            {
                newArray1.append(productindex);
            }
            newobject.insert("ProductIndex",newArray1);
            QJsonArray newArray2;
            foreach(int productnum, newoutorder.ProductNum)
            {
                newArray2.append(productnum);
            }
            newobject.insert("ProductNum",newArray2);
            QJsonArray newArray3;
            foreach(QString workorder, newoutorder.WorkOrder)
            {
                newArray3.append(workorder);
            }
            newobject.insert("WorkOrder",newArray3);
            newobject.insert("BagStartTime",newoutorder.BagStartTime);
            newobject.insert("PourStartTime",newoutorder.PourStartTime);
            newobject.insert("BagRestTime",newoutorder.BagRestTime);
            newobject.insert("PourRestTime",newoutorder.PourRestTime);
            newobject.insert("EndTime",newoutorder.EndTime);
            newobject.insert("DependIndex",newoutorder.DependIndex);

            //printf("%s",newoutorder.ProductIndex.front().toLatin1().data());

            newArray.append(newobject);
        }
        QJsonDocument document;
        document.setArray(newArray);
        QByteArray qbyte = document.toJson(QJsonDocument::Compact);
        //printf("finished Json");
        //
    //    foreach(SalesOrder salesorder,SalesMap.values())
    //    {
    //        salesorder.ProductIndex.clear();
    //        salesorder.WorkOrder.clear();
    //    }
        SalesMap.clear();
        order34.clear();
    //    foreach(ProductOrder productorder, order56)
    //    {
    //        productorder.ProductNum.clear();
    //    }
        order56.clear();
    //    foreach(ProductOrder productorder, order7)
    //    {
    //        productorder.ProductNum.clear();
    //    }
        order7.clear();
        StockMap.clear();
        In_Product.clear();
    //    foreach(CountOrder countorder, CountList)
    //    {
    //        countorder.ProductMap.clear();
    //        countorder.SalesIndex.clear();
    //    }
        CountList.clear();
    //    foreach(OutputOrder oorder, outputorder)
    //    {
    //        oorder.ProductIndex.clear();
    //        oorder.WorkOrder.clear();
    //    }
        outputorder.clear();
        BagCost.clear();
        PourCost.clear();
        SalesIndexs.clear();
        //printf("finished clear");
        char *outputchar;
        outputchar = qbyte.data();
        //printf("len:%d\n",strlen(outputchar));
        memcpy(buffer4,outputchar,strlen(outputchar));
        buffer4[strlen(outputchar)] = '\0';
    } catch (...) {
        return 777;
    }
    return 1;
}
