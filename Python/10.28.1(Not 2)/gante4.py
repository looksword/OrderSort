import plotly.figure_factory as ff
import pandas as pd
import time

cost1 = pd.read_excel("results_order.xlsx", sheet_name="交集", header=0)
cost2 = pd.read_excel("results_order.xlsx", sheet_name="包装线非", header=0)
cost3 = pd.read_excel("results_order.xlsx", sheet_name="灌装线非", header=0)


allorder = pd.DataFrame(columns=['Task', 'status', 'Start', 'Finish'])
for i in cost1.index:
    timeArray1 = time.localtime(cost1["start1"][i])
    timeArray2 = time.localtime(cost1["change1"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    allorder = allorder.append({'Task': '包装线',
                                'status': '并行换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                                 ignore_index=True)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '并行换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                               ignore_index=True)
for i in cost2.index:
    timeArray1 = time.localtime(cost2["start1"][i])
    timeArray2 = time.localtime(cost2["change1"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    allorder = allorder.append({'Task': '包装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                                 ignore_index=True)
for i in cost3.index:
    timeArray1 = time.localtime(cost3["start1"][i])
    timeArray2 = time.localtime(cost3["change1"][i])
    otherStyleTime1 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray1)
    otherStyleTime2 = time.strftime('%Y-%m-%d %H:%M:%S', timeArray2)
    allorder = allorder.append({'Task': '灌装线',
                                'status': '换型换料',
                                'Start': pd.to_datetime(otherStyleTime1),
                                'Finish': pd.to_datetime(otherStyleTime2)},
                                 ignore_index=True)

allorder = allorder.sort_values(by='Start')
colors = {'换型换料':'rgb(0,200,0)','并行换型换料':'rgb(0,100,100)'}

fig=ff.create_gantt(allorder,showgrid_x=True,colors=colors,index_col='status',show_colorbar=True,group_tasks=True)

fig.show()

