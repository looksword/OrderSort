import pandas as pd
# import numpy as np
import time
import copy

order34 = pd.read_excel("test34567.xlsx", sheet_name="制令单34", header=0)
order56 = pd.read_excel("test34567.xlsx", sheet_name="制令单56", header=0)
order7 = pd.read_excel("test34567.xlsx", sheet_name="制令单7", header=0)
order_34 = order34['制令单'].map(eval)
order_56 = order56['制令单'].map(eval)
order_7 = order7['制令单'].map(eval)
stock_test = pd.read_excel("test34567.xlsx", sheet_name="库存", header=0)
stock = stock_test['库存'].map(eval)
stockDict = dict()
pourOrder = dict()
for i in order_56.index:
    p = list(order_56[i].keys())[0]
    stockDict[p] = order_56[i][p]
    pourOrder[p] = 0
for i in stock.index:
    p = list(stock[i].keys())[0]
    stockDict[p] = stock[i][p]
for i in order_34.index:
    p = list(order_34[i].keys())[0]
    pourOrder[p] = order_34[i][p]

costpour = pd.read_excel("test34567.xlsx", sheet_name="灌装换型换料", header=0, index_col=0)
costbag = pd.read_excel("test34567.xlsx", sheet_name="包装换型换料", header=0, index_col=0)
cost2 = pd.read_excel("test34567.xlsx", sheet_name="自动包装换型换料", header=0, index_col=0)
# cost7 = pd.read_excel("test34567.xlsx", sheet_name="灌包换型换料", header=0, index_col=0)
# print(cost56['None']['I'])

df = pd.read_excel("test34567.xlsx", sheet_name="销售订单", header=None)[0]
data = df.map(eval).map(frozenset)
data.name = '计数'
counts = data.value_counts()
# 统计产品数目
products = []
for i, c in counts.items():
    products.extend(list(i) * c)
prods = pd.Series(products, name='计数')
# 产品数目
all_products = prods.value_counts().sort_index()
# pd.Series(counts).to_excel('counts.xlsx')
# pd.Series(all_products).to_excel('all.xlsx')
# 在库产品数目
in_products = {p: 0 for p in all_products.index}

ppppp = counts.reset_index().rename(columns={'index': '组合'})
mp = {k: (-len(v)) for k, v in ppppp['组合'].items()}
ps = ppppp.loc[sorted(ppppp.index, key=mp.get)]

bagtime = 30 # 包装线节拍秒数
pourtime = 10 # 灌装线节拍秒数
order2time = 10 # 大货节拍秒数
testalpha = 'A' # 大货前测试产品
order2alpha = 'U' # 大货产品
allsetnum = 400 # 齐套仓库位
bagoncenum = 175 # 包装单次超参数


def inter(a, b):
    if list(set(a) & set(b)):
        return True
    else:
        return False


def timestr(seconds):
    mins, sec = divmod(seconds, 60)
    hour, mins = divmod(mins, 60)
    return "%d:%02d:%02d" % (hour, mins, sec)


def calRate(first, second):
    calrate = first / second
    return "%.2f" % (calrate * 100)


"""def update2():
    for k, v in ps.iterrows():
        if counts[v['组合']] == 0:
            continue
        if (s := min([in_products[x] for x in v["组合"]])) > 0:
            new_count = max(counts[v['组合']] - s, 0)
            delta = counts[v['组合']] - new_count
            assert delta >= 0
            # print("出库",v['组合'],delta)
            counts[v['组合']] = new_count
            for x in v["组合"]:
                in_products[x] -= delta
                assert in_products[x] >= 0"""


def update():
    for k, v in ps.iterrows():
        if counts[v['组合']] == 0:
            continue
        s = min([in_products[xv] for xv in v["组合"]])
        if s > 0:
            if counts[v['组合']] > s:
                delta = s
                # print("出库", v['组合'], delta)
                counts[v['组合']] = counts[v['组合']] - s
                for xv in v['组合']:
                    in_products[xv] -= delta
            else:
                delta = counts[v['组合']]
                # print("出库", v['组合'], delta)
                counts[v['组合']] = 0
                for xv in v['组合']:
                    in_products[xv] -= delta


if __name__ == '__main__':
    start = time.time()
    First56 = True
    NotExplode = True
    results = []
    LastOrder = 'None'
    LastBagOrder = 'None'
    LastPourOrder = 'None'
    Lastcost2Order = 'None'
    all5order = pd.DataFrame(columns=['index', 'order', 'type', 'startTime', 'changeTime', 'endTime', 'startTimes', 'changeTimes', 'endTimes', 'rate', 'WholeSet'])
    all7order = pd.DataFrame(columns=['index', 'order', 'type', 'startTime', 'changeTime', 'endTime', 'startTimes', 'changeTimes', 'endTimes', 'localPourStart', 'PourChangeTime', 'rate', 'WholeSet'])
    all4order = pd.DataFrame(columns=['index', 'order', 'type', 'startTime', 'changeTime', 'endTime', 'startTimes', 'changeTimes', 'endTimes', 'rate', 'Stock'])
    all2order = pd.DataFrame(columns=['index', 'order', 'type', 'startTime', 'changeTime', 'endTime', 'startTimes', 'changeTimes', 'endTimes', 'BagChangeTime', 'rate'])
    order4index = 0
    order56index = 0
    order7index = 0
    order2index = 0
    orderBagStart = 0
    orderPourStart = 0

    allbagttime = 0
    allbagctime = 0
    allbagtime = 0
    allpourttime = 0
    allpourctime = 0
    allpourtime = 0
    allorder2ttime = 0
    allorder2ctime = 0
    allorder2time = 0

    while True:
        sum56 = 0
        for x in order_56.index:
            for y in order_56[x].keys():
                sum56 += order_56[x][y]
        sum7 = 0
        for x in order_7.index:
            for y in order_7[x].keys():
                sum7 += order_7[x][y]
        # if sum56 == 0 or sum7 == 0:
        #     LastOrder = 'None'
        if sum56 == 0 and sum7 == 0:
            break
        if (sum56 != 0 and First56) or sum7 == 0:
            max_count = 0
            max_num = 0
            max_i = 0
            max_cost56 = 0
            max_cost34 = 0
            max_cost_rate = 0
            max_ordernum = 0
            max_pournum = 0
            for i in order_56.index:
                if sum(order_56[i].values()) == 0:
                    continue
                p = list(order_56[i].keys())[0]
                now_products = {pi: m for pi, m in in_products.items() if m > 0}
                index56 = counts.index.map(lambda xm: p in xm and all((j == p or j in now_products) for j in xm))
                df = counts[index56].reset_index()
                df['len'] = df['index'].map(len)
                sort_df = sorted(df['index'], key=lambda xl: -len(xl))
                cMap = {o: 0 for o in range(1, 6)}
                cMap.update(df.groupby('len').sum()['计数'].to_dict())
                cMap[2] = 0
                cMap[3] = 0
                cMap[4] = 0
                cMap[5] = 0
                for ppp in sort_df:
                    if len(ppp) > 1:
                        min_num = counts.get(frozenset(ppp), 0)
                        for xp in ppp:
                            if xp == p:
                                continue
                            min_num = min(now_products[xp], min_num)
                        if min_num < 0:
                            min_num = 0
                        for xp in ppp:
                            if xp == p:
                                continue
                            now_products[xp] -= min_num
                        cMap[len(ppp)] += min_num
                total = sum([cMap[5] * 5, cMap[4] * 4, cMap[3] * 3, cMap[2] * 2, cMap[1]])
                if total > 0:
                    test_min_order_num = max(sum(cMap), bagoncenum)
                    test_max_order_num = min(test_min_order_num, order_56[i][p])
                    newpournum = 0
                    maxPourNum = 0
                    costTime56 = costbag[LastBagOrder][p]
                    costTime34 = costpour[LastPourOrder][p]
                    if test_max_order_num > stockDict[p]:
                        if orderBagStart > orderPourStart + costTime34 * 60:
                            newpournum = min(int((orderBagStart - orderPourStart - costTime34 * 60) / pourtime),
                                             order_56[i][p] - stockDict[p])
                            maxPourNum = min(int((orderBagStart - orderPourStart - costTime34 * 60) / pourtime),
                                             pourOrder[p])
                    else:
                        if orderBagStart > orderPourStart + costTime34 * 60:
                            # if order_56[i][p] > 0:
                            #    if stockDict[p] < order_56[i][p]:
                            maxPourNum = min(int((orderBagStart - orderPourStart - costTime34 * 60) / pourtime), pourOrder[p])
                    test_max_order_num = min(test_max_order_num, stockDict[p] + newpournum)
                    test_next_order_num = min(test_max_order_num, allsetnum - sum(in_products.values()) + total)
                    cost_rate = test_next_order_num * bagtime / (costTime56 * 60 + test_next_order_num * bagtime)
                    # if total > max_num:
                    if cost_rate > max_cost_rate:
                        max_num = total
                        max_i = i
                        max_count = sum(cMap)
                        max_pournum = maxPourNum
                        max_ordernum = test_next_order_num
                        max_cost56 = costTime56
                        max_cost34 = costTime34
                        max_cost_rate = cost_rate
            if max_num == 0:
                nostock56 = 0
                for x in order_56.index:
                    for y in order_56[x].keys():
                        if order_56[x][y] < stockDict[y]:
                            nostock56 += order_56[x][y]
                # if sum56 < allsetnum - sum(in_products.values()):
                if nostock56 < allsetnum - sum(in_products.values()) & nostock56 > 0:
                    # print("剩余所有制令单56可全部放入齐套仓")
                    for i in order_56.index:
                        next_count = dict()
                        y = list(order_56[i].keys())[0]
                        if order_56[i][y] == 0:
                            continue
                        if order_56[i][y] < stockDict[y]:
                            next_order = y
                            next_order_num = order_56[i][y]
                            in_products[next_order] += int(next_order_num)
                            next_count[next_order] = int(next_order_num)
                            results.append(next_count)
                            update()
                            # print("齐套仓库存峰值:", sum(in_products.values()))
                            all5order = all5order.append({'index': order56index,
                                                          'order': next_count,
                                                          'type': 5,
                                                          'startTime': timestr(orderBagStart),
                                                          'changeTime': timestr(costbag[LastBagOrder][next_order]*60),
                                                          'endTime': timestr(orderBagStart +
                                                                             costbag[LastBagOrder][next_order] * 60 +
                                                                             sum(next_count.values()) * bagtime),
                                                          'startTimes': orderBagStart,
                                                          'changeTimes': (costbag[LastBagOrder][next_order] * 60),
                                                          'endTimes': (orderBagStart +
                                                                       costbag[LastBagOrder][next_order] * 60 +
                                                                       sum(next_count.values()) * bagtime),
                                                          'rate': calRate(sum(next_count.values()) * bagtime, costbag[LastBagOrder][next_order] * 60 + sum(next_count.values()) * bagtime),
                                                          'WholeSet': sum(in_products.values())},
                                                         ignore_index=True)
                            order56index += 1
                            print({'index': order56index,
                                   'type': 5,
                                   'startTime': timestr(orderBagStart),
                                   'changeTime': timestr(costbag[LastBagOrder][next_order]*60),
                                   'endTime': timestr(orderBagStart +
                                                      costbag[LastBagOrder][next_order] * 60 +
                                                      sum(next_count.values()) * bagtime),
                                   'order': next_count,
                                   'WholeSet': sum(in_products.values())})
                            allbagttime += sum(next_count.values()) * bagtime
                            allbagctime += costbag[LastBagOrder][next_order] * 60
                            allbagtime += costbag[LastBagOrder][next_order] * 60 + sum(next_count.values()) * bagtime
                            orderBagStart += costbag[LastBagOrder][next_order] * 60 + sum(next_count.values()) * bagtime
                            order_56[i][next_order] -= next_order_num
                            stockDict[y] -= next_order_num
                            LastBagOrder = next_order
                else:
                    # print("剩余所有制令单56不可全部放入齐套仓")
                    First56 = False
                    LastPourOrder = 'None'
                # LastOrder = 'None'
            else:
                next_count = dict()
                next_pour = dict()
                next_order = list(order_56[max_i].keys())[0]
                next_order_num = max_ordernum
                in_products[next_order] += int(next_order_num)
                next_count[next_order] = int(next_order_num)
                next_pour[next_order] = int(max_pournum)
                results.append(next_count)
                update()
                if sum(in_products.values()) > allsetnum:
                    print("爆仓!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
                    NotExplode = False
                # print("齐套仓库存峰值:", sum(in_products.values()))
                all5order = all5order.append({'index': order56index,
                                              'order': next_count,
                                              'type': 5,
                                              'startTime': timestr(orderBagStart),
                                              'changeTime': timestr(max_cost56 * 60),
                                              'endTime': timestr(orderBagStart +
                                                                 max_cost56 * 60 +
                                                                 sum(next_count.values()) * bagtime),
                                              'startTimes': orderBagStart,
                                              'changeTimes': (max_cost56 * 60),
                                              'endTimes': (orderBagStart +
                                                           max_cost56 * 60 +
                                                           sum(next_count.values()) * bagtime),
                                              'rate': calRate(sum(next_count.values()) * bagtime, max_cost56 * 60 + sum(next_count.values()) * bagtime),
                                              'WholeSet': sum(in_products.values())},
                                             ignore_index=True)
                order56index += 1
                print({'index': order56index,
                       'type': 5,
                       'startTime': timestr(orderBagStart),
                       'changeTime': timestr(max_cost56 * 60),
                       'endTime': timestr(orderBagStart +
                                          max_cost56 * 60 +
                                          sum(next_count.values()) * bagtime),
                       'order': next_count,
                       'WholeSet': sum(in_products.values())})
                stockDict[next_order] = stockDict[next_order] - max_ordernum + max_pournum
                nowStockDict = copy.deepcopy(stockDict)
                if max_pournum > 0:
                    all4order = all4order.append({'index': order4index,
                                                  'order': next_pour,
                                                  'type': 4,
                                                  'startTime': timestr(orderPourStart),
                                                  'changeTime': timestr(max_cost34 * 60),
                                                  'endTime': timestr(orderPourStart +
                                                                     max_cost34 * 60 +
                                                                     max_pournum * pourtime),
                                                  'startTimes': orderPourStart,
                                                  'changeTimes': (max_cost34 * 60),
                                                  'endTimes': (orderPourStart +
                                                               max_cost34 * 60 +
                                                               max_pournum * pourtime),
                                                  'rate': calRate(max_pournum * pourtime, max_cost34 * 60 + max_pournum * pourtime),
                                                  'Stock': nowStockDict},
                                                 ignore_index=True)
                    order4index += 1
                    print({'index': order4index, 'type': 4, 'startTime': timestr(orderPourStart), 'order': next_pour, 'Stock': sum(nowStockDict.values())})
                order_56[max_i][next_order] -= next_order_num
                pourOrder[next_order] -= max_pournum
                LastOrder = next_order
                LastBagOrder = next_order
                if max_pournum > 0:
                    allpourttime += max_pournum * pourtime
                    allpourctime += max_cost34 * 60
                    allpourtime += max_cost34 * 60 + max_pournum * pourtime
                    orderPourStart += max_pournum * pourtime + max_cost34 * 60
                    LastPourOrder = next_order
                    # if sum(pourOrder.values()) == 0:
                    #    First56 = False
                allbagttime += max_ordernum * bagtime
                allbagctime += max_cost56 * 60
                allbagtime += max_cost56 * 60 + max_ordernum * bagtime
                orderBagStart += max_ordernum * bagtime + max_cost56 * 60

        if (sum7 != 0 and not First56) or sum56 == 0:
            max_count = dict()
            max_num = 0
            max_i = 0
            max_cost7bag = 0
            max_cost7pour = 0
            max_cost_rate = 0
            max_localpourstart = 0
            for i in order_7.index:
                if sum(order_7[i].values()) == 0:
                    continue
                findProducts = order_7[i]
                p = list(order_7[i].keys())
                count = {x: 0 for x in p}
                now_products = {p: m for p, m in in_products.items() if m > 0}
                index1 = counts.index.map(lambda xm:
                                          inter(p, xm) and all((j in findProducts or j in now_products) for j in xm))
                df = counts[index1].reset_index()
                df['len'] = df['index'].map(len)
                sort_df = sorted(df['index'], key=lambda xl: -len(xl))
                cMap = {o: 0 for o in range(1, 6)}
                cMap.update(df.groupby('len').sum()['计数'].to_dict())
                cMap[2] = 0
                cMap[3] = 0
                cMap[4] = 0
                cMap[5] = 0
                for ppp in sort_df:
                    min_num = counts.get(frozenset(ppp), 0)
                    for xp in ppp:
                        if xp in p:
                            continue
                        min_num = min(now_products[xp], min_num)
                    if min_num < 0:
                        min_num = 0
                    for xp in ppp:
                        if xp in p:
                            continue
                        now_products[xp] -= min_num
                    for xp in ppp:
                        if xp in p:
                            count[xp] += min_num
                    if len(ppp) == 1:
                        continue
                    cMap[len(ppp)] += min_num
                total = sum([cMap[5] * 5, cMap[4] * 4, cMap[3] * 3, cMap[2] * 2, cMap[1]])
                if total > 0:
                    test_next_order_num = allsetnum - sum(in_products.values()) - total  # - sum(count.values())
                    # print("评估制令单数量", test_next_order_num, "评估预计出库数量", total, "制令单", count)
                    costtime7bag = 0
                    costtime7pour = 0
                    localpourstart = orderBagStart
                    localLastBagOrder = LastBagOrder
                    localLastPourOrder = LastPourOrder
                    for xp in p:
                        if count[xp] > 0:
                            if localLastPourOrder == LastPourOrder:
                                costtime7bag += costbag[localLastBagOrder][xp]
                                costtime7pour += costpour[localLastPourOrder][xp]
                                if orderPourStart < orderBagStart:
                                    # costtime7pour -= min((orderBagStart - orderPourStart) / 60, costpour[localLastPourOrder][xp])
                                    localpourstart = orderBagStart - min(orderBagStart - orderPourStart,costpour[localLastPourOrder][xp] * 60)
                            else:
                                costtime7bag += costbag[localLastBagOrder][xp]
                                costtime7pour += costpour[localLastPourOrder][xp]
                            # print("test:", localLastOrder, xp, cost7[localLastOrder][xp])
                            localLastBagOrder = xp
                            localLastPourOrder = xp
                    cost_rate = test_next_order_num * bagtime / (costtime7bag * 60 + test_next_order_num * bagtime)
                    # if total > max_num:
                    if cost_rate > max_cost_rate:
                        max_num = total
                        max_i = i
                        max_count = count
                        max_cost7bag = costtime7bag
                        max_cost7pour = costtime7pour
                        max_cost_rate = cost_rate
                        max_localpourstart = localpourstart
            if max_num == 0:
                if sum7 < allsetnum - sum(in_products.values()):
                    # print("剩余所有制令单7可全部放入齐套仓")
                    for i in order_7.index:
                        next_count = dict()
                        if sum(order_7[i].values()) == 0:
                            continue
                        costtime7bag = 0
                        costpour7pour = 0
                        localpourstart = orderBagStart
                        for newtype in list(order_7[i].keys()):
                            if order_7[i][newtype] != 0:
                                next_count[newtype] = int(order_7[i][newtype])
                                in_products[newtype] += int(next_count[newtype])
                                if newtype == LastPourOrder:
                                    costtime7bag += costbag[LastBagOrder][newtype]
                                    costpour7pour += costpour[LastPourOrder][newtype]
                                    if orderPourStart < orderBagStart:
                                        # costpour7pour -= min((orderBagStart - orderPourStart) / 60, costpour[LastPourOrder][newtype])
                                        localpourstart = orderBagStart - min(orderBagStart - orderPourStart, costpour[LastPourOrder][newtype] * 60)
                                else:
                                    costtime7bag += costbag[LastBagOrder][newtype]
                                    costpour7pour += costpour[LastPourOrder][newtype]
                                LastBagOrder = newtype
                                LastPourOrder = newtype
                        results.append(next_count)
                        update()
                        # print("齐套仓库存峰值:", sum(in_products.values()))
                        all7order = all7order.append({'index': order7index,
                                                      'order': next_count,
                                                      'type': 7,
                                                      'startTime': timestr(orderBagStart),
                                                      'changeTime': timestr(costtime7bag * 60),
                                                      'endTime': timestr(max(localpourstart + costpour7pour * 60, orderBagStart + max_cost7bag * 60) +
                                                                         sum(next_count.values()) * bagtime),
                                                      'startTimes': orderBagStart,
                                                      'changeTimes': (costtime7bag * 60),
                                                      'endTimes': (max(localpourstart + costpour7pour * 60, orderBagStart + max_cost7bag * 60) +
                                                                   sum(next_count.values()) * bagtime),
                                                      'localPourStart':localpourstart,
                                                      'PourChangeTime':(costpour7pour * 60),
                                                      'rate': calRate(sum(next_count.values()) * bagtime, costtime7bag * 60 + sum(next_count.values()) * bagtime),
                                                      'WholeSet': sum(in_products.values())},
                                                     ignore_index=True)
                        order7index += 1
                        allpourttime += sum(next_count.values()) * bagtime
                        allpourctime += costpour7pour * 60
                        allpourtime += costpour7pour * 60 + sum(next_count.values()) * bagtime
                        allbagttime += sum(next_count.values()) * bagtime
                        allbagctime += costtime7bag * 60
                        allbagtime += costtime7bag * 60 + sum(next_count.values()) * bagtime
                        tempbagtimealpha = max(localpourstart + costpour7pour * 60,orderBagStart + max_cost7bag * 60) + sum(next_count.values()) * bagtime
                        orderBagStart = tempbagtimealpha
                        orderPourStart = orderBagStart
                        print({'index': order7index,
                               'type': 7,
                               'startTime': timestr(orderBagStart),
                               'changeTime': timestr(costtime7bag * 60),
                               'endTime': timestr(orderBagStart +
                                                  costtime7bag * 60 +
                                                  sum(next_count.values()) * bagtime),
                               'order': next_count,
                               'WholeSet': sum(in_products.values())})
                        for order, order_num in next_count.items():
                            order_7[i][order] -= order_num
                else:
                    # print("剩余所有制令单7不可全部放入齐套仓")
                    First56 = True
                # LastOrder = 'None'
            else:
                if max_localpourstart - orderPourStart > max(costpour['None'][order2alpha], cost2['None'][order2alpha]):
                    Last2order = 'None'
                    if order2index == 0:
                        Last2order = 'None'
                        order2num = int((max_localpourstart - orderPourStart - costpour['None'][order2alpha] * 60) / order2time)
                    else:
                        Last2order = testalpha
                        order2num = int(
                            (max_localpourstart - orderPourStart - costpour[Last2order][order2alpha] * 60) / order2time)
                    all2order = all2order.append({'index': order2index,
                                                  'order': {order2alpha: order2num},
                                                  'type': 2,
                                                  'startTime': timestr(orderPourStart),
                                                  'changeTime': timestr(costpour[Last2order][order2alpha] * 60),
                                                  'endTime': timestr(orderPourStart +
                                                                     costpour[Last2order][order2alpha] * 60 +
                                                                     order2num * order2time),
                                                  'startTimes': orderPourStart,
                                                  'changeTimes': (costpour[Last2order][order2alpha] * 60),
                                                  'endTimes': (orderPourStart +
                                                               costpour[Last2order][order2alpha] * 60 +
                                                               order2num * order2time),
                                                  'BagChangeTime': cost2[Lastcost2Order][order2alpha] * 60,
                                                  'rate': calRate(order2num * order2time,
                                                                  costpour[Last2order][order2alpha] * 60 +
                                                                  order2num * order2time)},
                                                 ignore_index=True)
                    order2index += 1
                    allpourttime += order2num * order2time
                    allpourctime += costpour[Last2order][order2alpha] * 60
                    allpourtime += costpour[Last2order][order2alpha] * 60 + order2num * order2time
                    allorder2ttime += order2num * order2time
                    allorder2ctime += cost2[Lastcost2Order][order2alpha] * 60
                    allorder2time += cost2[Lastcost2Order][order2alpha] * 60 + order2num * order2time
                    Lastcost2Order = order2alpha
                next_count = dict()
                test_sum = 0
                for order in max_count.keys():
                    test_sum += order_7[max_i][order]
                in_test_sum = sum(in_products.values())
                last_order_num = allsetnum - sum(in_products.values()) + max_num - sum(max_count.values())  # 额外可入库
                extra_len = len(max_count)
                for order, order_num in max_count.items():
                    extra_order_num = 0
                    if test_sum >= allsetnum - in_test_sum + max_num:
                        if order_7[max_i][order] - order_num < int(last_order_num / extra_len):
                            # print("走剩余量")
                            extra_order_num = max(order_7[max_i][order] - order_num, 0)
                        else:
                            # print("走计算量")
                            extra_order_num = max(int(last_order_num / extra_len), 0)  # - order_num
                        max_order_num = order_num + extra_order_num
                        # print("total", max_num, "order_num", order_num, "extra_order_num", extra_order_num)
                        last_order_num -= extra_order_num
                        extra_len -= 1
                    else:
                        # print("走所有量")
                        max_order_num = order_7[max_i][order]
                        # print("total", max_num, "order_7", order_7[max_i][order])
                    in_products[order] += int(max_order_num)
                    next_count[order] = int(max_order_num)
                    # print("剩余", last_order_num)
                results.append(next_count)
                update()
                if sum(in_products.values()) > allsetnum:
                    print("爆仓!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
                    NotExplode = False
                # print("齐套仓库存峰值:", sum(in_products.values()))
                all7order = all7order.append({'index': order7index,
                                              'order': next_count,
                                              'type': 7,
                                              'startTime': timestr(orderBagStart),
                                              'changeTime': timestr(max_cost7bag * 60),
                                              'endTime': timestr(max(max_localpourstart + max_cost7pour * 60, orderBagStart + max_cost7bag * 60) +
                                                                 sum(next_count.values()) * bagtime),
                                              'startTimes': orderBagStart,
                                              'changeTimes': (max_cost7bag * 60),
                                              'endTimes': (max(max_localpourstart + max_cost7pour * 60, orderBagStart + max_cost7bag * 60) +
                                                           sum(next_count.values()) * bagtime),
                                              'localPourStart': max_localpourstart,
                                              'PourChangeTime': (max_cost7pour * 60),
                                              'rate': calRate(sum(next_count.values()) * bagtime, max_cost7bag * 60 + sum(next_count.values()) * bagtime),
                                              'WholeSet': sum(in_products.values())},
                                             ignore_index=True)
                order7index += 1
                print({'index': order7index,
                       'type': 7,
                       'startTime': timestr(orderBagStart),
                       'changeTime': timestr(max_cost7bag * 60),
                       'endTime': timestr(orderBagStart +
                                          max_cost7bag * 60 +
                                          sum(next_count.values()) * bagtime),
                       'order': next_count,
                       'WholeSet': sum(in_products.values())})
                allpourttime += sum(next_count.values()) * bagtime
                allpourctime += max_cost7pour * 60
                allpourtime += max_cost7pour * 60 + sum(next_count.values()) * bagtime
                allbagttime += sum(next_count.values()) * bagtime
                allbagctime += max_cost7bag * 60
                allbagtime += max_cost7bag * 60 + sum(next_count.values()) * bagtime
                tempbagtimealpha = max(max_localpourstart + max_cost7pour * 60, orderBagStart + max_cost7bag * 60) + sum(next_count.values()) * bagtime
                orderBagStart = tempbagtimealpha
                orderPourStart = orderBagStart
                for order, order_num in next_count.items():
                    order_7[max_i][order] -= order_num
                LastOrder = list(next_count.keys())[0]
                LastBagOrder = list(next_count.keys())[0]
                LastPourOrder = list(next_count.keys())[0]
        # print("齐套仓库存峰值:", sum(in_products.values()))
    if orderBagStart - orderPourStart > max(costpour['None'][order2alpha], cost2['None'][order2alpha]):
        Last2order = 'None'
        if order2index == 0:
            Last2order = 'None'
            order2num = int((orderBagStart - orderPourStart - costpour['None'][order2alpha] * 60) / order2time)
        else:
            Last2order = testalpha
            order2num = int((orderBagStart - orderPourStart - costpour[Last2order][order2alpha] * 60) / order2time)
        all2order = all2order.append({'index': order2index,
                                      'order': {order2alpha: order2num},
                                      'type': 2,
                                      'startTime': timestr(orderPourStart),
                                      'changeTime': timestr(costpour[Last2order][order2alpha] * 60),
                                      'endTime': timestr(orderPourStart +
                                                         costpour[Last2order][order2alpha] * 60 +
                                                         order2num * order2time),
                                      'startTimes': orderPourStart,
                                      'changeTimes': (costpour[Last2order][order2alpha] * 60),
                                      'endTimes': (orderPourStart +
                                                   costpour[Last2order][order2alpha] * 60 +
                                                   order2num * order2time),
                                      'BagChangeTime': cost2[Lastcost2Order][order2alpha] * 60,
                                      'rate': calRate(order2num * order2time,
                                                      costpour[Last2order][order2alpha] * 60 +
                                                      order2num * order2time)},
                                     ignore_index=True)
        allpourttime += order2num * order2time
        allpourctime += costpour[Last2order][order2alpha] * 60
        allpourtime += costpour[Last2order][order2alpha] * 60 + order2num * order2time
        allorder2ttime += order2num * order2time
        allorder2ctime += cost2[Lastcost2Order][order2alpha] * 60
        allorder2time += cost2[Lastcost2Order][order2alpha] * 60 + order2num * order2time
        Lastcost2Order = order2alpha
    end = time.time()
    print('end')
    print("贪心运行时间:%.2f秒" % (end - start))
    if NotExplode:
        Summary = pd.DataFrame(columns=['人工包装线制作用时', '人工包装线换型换料用时', '人工包装线总用时','人工包装线效率', '灌装线制作用时', '灌装线换型换料用时', '灌装线总用时','灌装线效率','自动包装线制作用时', '自动包装线换型换料用时', '自动包装线总用时','自动包装线效率'])
        Summary = Summary.append({'人工包装线制作用时': "%.2f" % (allbagttime/60),
                                  '人工包装线换型换料用时': "%.2f" % (allbagctime/60),
                                  '人工包装线总用时': "%.2f" % (allbagtime/60),
                                  '人工包装线效率': calRate(allbagttime, allbagtime),
                                  '灌装线制作用时': "%.2f" % (allpourttime/60),
                                  '灌装线换型换料用时': "%.2f" % (allpourctime/60),
                                  '灌装线总用时': "%.2f" % (allpourtime/60),
                                  '灌装线效率': calRate(allpourttime, allpourtime),
                                  '自动包装线制作用时': "%.2f" % (allorder2ttime / 60),
                                  '自动包装线换型换料用时': "%.2f" % (allorder2ctime / 60),
                                  '自动包装线总用时': "%.2f" % (allorder2time / 60),
                                  '自动包装线效率': calRate(allorder2ttime, allorder2time)},
                                 ignore_index=True)
        pd.Series(results).to_excel('test_results.xlsx')
        writer = pd.ExcelWriter('results_order.xlsx')
        all5order.to_excel(writer, "包装制令单")
        all7order.to_excel(writer, "灌包制令单")
        all4order.to_excel(writer, "灌装制令单")
        all2order.to_excel(writer, "大货制令单")
        Summary.to_excel(writer, "汇总")
        writer.save()
        print('制令单数量:', len(results))
