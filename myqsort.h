#ifndef MYQSORT_H
#define MYQSORT_H

#include <QRunnable>
#include <algorithm>
#include <QThreadPool>

#include "recorder.h"

class myQsort:public QRunnable{
    int begin,end,*arr;
public:
    myQsort(int begin_,int end_,int *arr_):begin(begin_),end(end_),arr(arr_){
    }
    void run(){
        int l=begin,r=end;
        int i=l,j=r,x=arr[(l+r)/2];
        do{
            for (;arr[i]<x;++i);
            for (;arr[j]>x;--j);
            if (i<=j) std::swap(arr[i++],arr[j--]);
        } while (i<=j);
        if (i<end){
            if (end-i>recorder::maxlen && (j-begin>recorder::maxlen)){
                QThreadPool::globalInstance()->start(new myQsort(i,end,arr));
            } else {
                begin=i;
                run();
                begin=l;
            }
        }
        if (j>begin){
            //if (j-begin>recorder::maxlen){
            //    QThreadPool::globalInstance()->start(new myQsort(begin,j,arr));
            //} else {
                end=j;
                run();
                end=r;
            //}
        }
    }
};


#endif // MYQSORT_H
