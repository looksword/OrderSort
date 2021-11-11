import plotly.figure_factory as ff
import pandas as pd
import time

order34 = pd.read_excel("results_order.xlsx", sheet_name="灌装制令单", header=0)
order56 = pd.read_excel("results_order.xlsx", sheet_name="包装制令单", header=0)
order7 = pd.read_excel("results_order.xlsx", sheet_name="灌包制令单", header=0)
order2 = pd.read_excel("results_order.xlsx", sheet_name="大货制令单", header=0)


allorder = pd.DataFrame(columns=['Task', 'status', 'Start', 'Finish'])
for i in order56.index:
    timeArray1 = time.localtime(order56["startTimes"][i])
    timeArray2 = time.localtime(order56["startTimes"][i]+order56["changeTimes"][i])
    timeArray3 = time.localtime(order56["endTimes"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    otherStyleTime3 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray3)
    allorder = allorder.append({'Task': '人工包装线',
                                'status': '包装',
                                'Start': pd.to_datetime(otherStyleTime2),
                                'Finish': pd.to_datetime(otherStyleTime3)},
                                 ignore_index=True)
    allorder = allorder.append({'Task': '人工包装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                               ignore_index=True)
for i in order34.index:
    timeArray1 = time.localtime(order34["startTimes"][i])
    timeArray2 = time.localtime(order34["startTimes"][i] + order34["changeTimes"][i])
    timeArray3 = time.localtime(order34["endTimes"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    otherStyleTime3 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray3)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '灌装',
                                'Start': pd.to_datetime(otherStyleTime2),
                                'Finish': pd.to_datetime(otherStyleTime3)},
                                 ignore_index=True)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                               ignore_index=True)
for i in order7.index:
    timeArray1 = time.localtime(order7["startTimes"][i])
    timeArray2 = time.localtime(order7["startTimes"][i] + order7["changeTimes"][i])
    timeArray3 = time.localtime(order7["endTimes"][i])
    timeArray4 = time.localtime(order7["localPourStart"][i])
    timealpha = max(order7["localPourStart"][i] + order7["PourChangeTime"][i],order7["startTimes"][i] + order7["changeTimes"][i])
    timeArray5 = time.localtime(timealpha)
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    otherStyleTime3 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray3)
    otherStyleTime4 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray4)
    otherStyleTime5 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray5)
    allorder = allorder.append({'Task': '人工包装线',
                                'status': '灌包',
                                'Start': pd.to_datetime(otherStyleTime5),
                                'Finish': pd.to_datetime(otherStyleTime3)},
                                 ignore_index=True)
    allorder = allorder.append({'Task': '人工包装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                               ignore_index=True)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '灌包',
                                'Start': pd.to_datetime(otherStyleTime5),
                                'Finish': pd.to_datetime(otherStyleTime3)},
                               ignore_index=True)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime4),
                                'Finish': pd.to_datetime(otherStyleTime5)},
                               ignore_index=True)
for i in order2.index:
    timeArray1 = time.localtime(order2["startTimes"][i])
    timeArray2 = time.localtime(order2["startTimes"][i] + order2["changeTimes"][i])
    timeArray3 = time.localtime(order2["endTimes"][i])
    timeArray4 = time.localtime(order2["startTimes"][i] + order2["changeTimes"][i] - order2["BagChangeTime"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    otherStyleTime3 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray3)
    otherStyleTime4 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray4)
    allorder = allorder.append({'Task': '自动包装线',
                                'status': '大货',
                                'Start': pd.to_datetime(otherStyleTime2),
                                'Finish': pd.to_datetime(otherStyleTime3)},
                                 ignore_index=True)
    allorder = allorder.append({'Task': '自动包装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime4),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                               ignore_index=True)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '大货',
                                'Start': pd.to_datetime(otherStyleTime2),
                                'Finish': pd.to_datetime(otherStyleTime3)},
                               ignore_index=True)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                               ignore_index=True)

allorder = allorder.sort_values(by='Start')
colors = {'大货':'rgb(200,0,200)','包装':'rgb(0,200,0)','灌装':'rgb(0,100,100)','灌包':'rgb(255,205,0)','换型换料':'rgb(200,0,0)'}

fig=ff.create_gantt(allorder,showgrid_x=True,colors=colors,index_col='status',show_colorbar=True,group_tasks=True)

fig.show()

