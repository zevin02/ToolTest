# 编译
## bazel的使用
### WORKSPACE
首先先创建一个WORKSPACE
~~~cpp
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

http_archive(
    name = "com_github_google_glog",
    sha256 = "122fb6b712808ef43fbf80f75c52a21c9760683dae470154f02bddfc61135022",
    strip_prefix = "glog-0.6.0",
    urls = ["https://github.com/google/glog/archive/v0.6.0.zip"],
)
~~~

### BUILD
再创建一个BUILD
~~~cpp
cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = ["@com_github_google_glog//:glog"],
)
~~~


使用bazel编译,构建项目
~~~cpp
bazel bulid //:main
~~~

编译出来的文件再就可以运行了
~~~c
./bazel-bin/main
~~~

或者也可以这样运行,但是不推荐
~~~cpp
bazel run //:main
~~~



# 使用
## 日志等级
glog有四种错误级别

~~~cpp
enum SeverityLevel
{
　　google::INFO = 0,
　　google::WARNING = 1,
　　google::ERROR = 2,
　　google::FATAL = 3,//使用FATAL程序就会立刻终止
};
~~~


4个错误级别的使用
严重程度分级
~~~cpp
LOG(INFO) << "info test";  //输出一个Info日志
LOG(WARNING) << "warning test";  //输出一个Warning日志
LOG(ERROR) << "error test";  //输出一个Error日志
LOG(FATAL) << "fatal test";  //输出一个Fatal日志，这是最严重的日志并且输出之后会中止程序
~~~
使用完不需要endl,glog 会自动换行

使用结果
![](https://img-blog.csdnimg.cn/8323dd9303e14ca1a60446fd20fdde67.png)

>ERROR和FATAL除了会写到日志里面，还会打印到标准错误里面
>也就是说，WARNING和INFO不会打印到标准错误里面去


## 日志信息
>E20220715 10:10:21.065380 25803 main.cc:8] HELLO WORLD

>* E:错误级别 
>* 20220715 10:10:21.065380 ：年月日时分秒.微秒
>* 065380:线程号 
>* main.cc :源文件名
>* 8:行数
>* HELLO WORLD:就是打印出来的信息


## 头文件

>#include<glog/logging.h>

## 使用的必须
首先要先初始化
~~~cpp
google::InitGoogleLogging(argv[0]);
~~~

最后用完就要关闭
~~~cpp
google::ShutdownGoogleLogging();
~~~


## 设置标志
*  **log_dir**:可以将生成的日志文件放到指定的目录下面，而不是默认的日志记录目录

我们也可以在全局里面设置

~~~cpp
FLAGS_log_dir="./log";
~~~
这个要放在init之前

* FLAGS_logtostderr=0/1;//这个默认是false（不打印到标准错误里面）（设置true，就可以把信息打印到标准错误里面）
* FLAGS_stderrthreshold；
>默认是=2，就是可以把>=它的严重等级信息也同时打印到标准错误当中
~~~cpp
FLAGS_logtostderr=0;//这样的话INFO就能打印出来了,默认是false

FLAGS_alsologtostderr=true;//既打印到文件里面，又打印到标准输出里面
FLAGS_stderrthreshold=0/1/2/3；
~~~
这个需要的话，还需要我们自己去设置



## 条件判断
错误等级设置为INFO，当num_cookies>10的时候才会触发
~~~cpp
LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
~~~

google::COUNTER就是可以记录第几个1,2,3这样
~~~cpp
for(int i=0;i<30;i++){
    LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";//每10次打印一下,
}
~~~

## DEBUG
DLOG仅有在debug模式下才会有效
~~~cpp
DLOG(INFO) << "Found cookies";
DLOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
DLOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
~~~


# CHECK
这个如果调用失败的话程序就会终止，

~~~cpp
CHECK_EQ(1,2)<< ": The world must be ending!";//判断等于，如果不等于就打印信息
CHECK_NE(1,2)<< ": The world must be ending!";//判断不等于，如果等于就会打印信息
CHECK(1==2)<<"not";//CHCEK判断，如果条件失败的话就会报错



## 