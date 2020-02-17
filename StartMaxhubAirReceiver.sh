#! /bin/bash

# 如果找不到MaxhubAirReceiver程序，或者同一个用户下已经启动了改程序，那就正常退出
# 如果发现已经被其他用户启动了，那么就结束掉该程序，然后正常退出

last_user=`ps aux | grep xxx | grep -v grep | awk '{print $1}'`
current_user=`who | awk '{print $1}'`

if [ -z $last_user ]
then
    exit 0;
elif [ $last_user == $current_user ] 
then
    ps aux | grep xxx | grep -v grep | awk '{print $2}' | xargs kill -9;
else
    exit 0;
fi
