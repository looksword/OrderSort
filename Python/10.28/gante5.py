import plotly.figure_factory as ff
import pandas as pd
import time

cost1 = pd.read_excel("results_order.xlsx", sheet_name="12交集", header=0)
cost2 = pd.read_excel("results_order.xlsx", sheet_name="123交集", header=0)
cost3 = pd.read_excel("results_order.xlsx", sheet_name="人工包装线非", header=0)
cost4 = pd.read_excel("results_order.xlsx", sheet_name="灌装线非", header=0)


allorder = pd.DataFrame(columns=['Task', 'status', 'Start', 'Finish'])
for i in cost1.index:
    timeArray1 = time.localtime(cost1["start1"][i])
    timeArray2 = time.localtime(cost1["change2"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    allorder = allorder.append({'Task': '换型换料',
                                'status': '2线4人',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                                 ignore_index=True)

for i in cost2.index:
    timeArray1 = time.localtime(cost2["start1"][i])
    timeArray2 = time.localtime(cost2["change2"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    allorder = allorder.append({'Task': '换型换料',
                                'status': '3线3人',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                                 ignore_index=True)

for i in cost3.index:
    timeArray1 = time.localtime(cost3["start1"][i])
    timeArray2 = time.localtime(cost3["change2"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    allorder = allorder.append({'Task': '换型换料',
                                'status': '1线4人',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                                 ignore_index=True)
for i in cost4.index:
    timeArray1 = time.localtime(cost4["start1"][i])
    timeArray2 = time.localtime(cost4["change1"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    allorder = allorder.append({'Task': '换型换料',
                                'status': '1线4人',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                                 ignore_index=True)

allorder = allorder.sort_values(by='Start')
colors = {'1线4人':'rgb(0,200,0)','2线4人':'rgb(0,100,100)','3线3人':'rgb(255,69,0)'}

fig=ff.create_gantt(allorder,showgrid_x=True,colors=colors,index_col='status',show_colorbar=True,group_tasks=True)

fig.show()

