#include<iostream>
#include <glog/logging.h>
int main(int argc,char* argv[])
{
    FLAGS_log_dir="./log";//把内容输出到一个文件里面
    // FLAGS_logtostderr=true;
    //这个false就是不把他输出到标准输出当中
    //如果是true的话就不会输出到文件里面了
    //第一步初始化

    FLAGS_alsologtostderr=true;//既打印到文件里面，又打印到标准输出里面

    google::InitGoogleLogging(argv[0]);
    LOG(INFO)<<"HELLO WORLD";
    LOG(ERROR)<<"HELLO WORLD";
    // LOG(FATAL)<<"HELLO WORLD";
    LOG(WARNING)<<"HELLO WORLD";
    //最后关闭
    int num_cookies=9;
    LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";//进行依次判断

    for(int i=0;i<30;i++){
    LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";//每10次打印一下,
    }

    DLOG(INFO) << "Found cookies";
    // CHECK_EQ(1,2)<< ": The world must be ending!";
    CHECK_NE(1,2)<< ": The world must be ending!";
    // CHECK(1==2)<<"not";//CHCEK判断，如果条件失败的话就会报错
    google::ShutdownGoogleLogging();
    return 0;
}
