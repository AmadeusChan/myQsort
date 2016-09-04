#include "mainwindow.h"
#include "recorder.h"
#include "myqsort.h"
#include <QApplication>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QThread>
#include <QThreadPool>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int t=time(NULL);
    int num_of_arr=1000000,*arr,num_of_core=1;
    std::cout<<"please input the number of core:";
    std::cin>>num_of_core;
    std::cout<<"please input the number of array:";
    std::cin>>num_of_arr;
    //num_of_core=8;
    //num_of_arr=1000000000;
    srand(time(NULL));
    arr=new int[num_of_arr];
    for (int i=0;i<num_of_arr;++i){
        arr[i]=rand();
    }
    QThreadPool *pool=QThreadPool::globalInstance();
    pool->setMaxThreadCount(num_of_core);
    recorder::maxlen=num_of_arr/(num_of_core*5);
    qDebug()<<recorder::maxlen;
    QTimer *timer=new QTimer;
    int cnt=0;
    qDebug()<<time(NULL)-t<<"s";
    t=time(NULL);
    QObject::connect(timer,&QTimer::timeout,[=](){
        qDebug()<<" activate thread:"<<pool->activeThreadCount();
        if (!pool->activeThreadCount()){
            bool flag=true;
            for (int i=1;i<num_of_arr;++i) if (arr[i]<arr[i-1]){
                flag=false;
                break;
            }
            qDebug()<<"result"<<flag;
            qDebug()<<time(NULL)-t<<"s";
            qApp->exit();
        }
    });
    timer->start(1000);
    pool->start(new myQsort(0,num_of_arr-1,arr));

    return a.exec();
}
