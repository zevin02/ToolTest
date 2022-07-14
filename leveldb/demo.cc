#include<cassert>
#include"leveldb/db.h"
#include"leveldb/write_batch.h"
#include<string>
using namespace std;
#include<iostream>
int main()
{
    //打开一个数据库
    leveldb::DB* db;
    leveldb::Options opts;
    opts.create_if_missing=true;
    leveldb::Status status=leveldb::DB::Open(opts,"testdb",&db);
    assert(status.ok());//每次对status进行操作的时候都需要检测是否成功
    cout<<status.ToString()<<endl;//输出OK
    /*
    Open要三个参数，
    * Options：：控制DB的一些行为，这里的true是存在就打开，不存在就创建
    * ./testdb：leveldb数据库的根目录，一个leveldb数据库存放在一个目录下
    * &db用来返回一个实例
    * status就是返回的详细信息
    
    */

   //写入一个数据
   leveldb::Slice key("ehello");//这里面对应的是key值
   
    status=db->Put(leveldb::WriteOptions(),"name","zhelin");//这里我们直接用
    assert(status.ok());

    //读一个数据
    string val;
    status=db->Get(leveldb::ReadOptions(),"name",&val);
    assert(status.ok());//当操作成功的时候，函数返回status.ok()的值为true，如果错误的话，就是返回false
    cout<<val<<endl;//val里面就是我们读取到的数据

    //批量的写入一些数据

    leveldb::WriteBatch batch;
    batch.Delete("name");//把name对应的东西删除
    /*
        这里的Delete并不会直接删除数据，而是在对应的位置插入一个key的删除标志，然后再后续的压实过程中才会最终去删除这条key -value记录

    */




    batch.Put("name0","zelin0");
    batch.Put("name1","zelin1");
    batch.Put("name2","zelin2");
    batch.Put("name3","zelin3");
    batch.Put("name4","zelin4");
    batch.Put("name5","zelin5");
    batch.Put("name6","zelin6");
    batch.Put("name7","zelin7");
    
    status=db->Write(leveldb::WriteOptions(),&batch);//write方法是可以依次写好几个的

    //读取数据库
    leveldb::Iterator *it =db->NewIterator(leveldb::ReadOptions());//用一个迭代器来使用
    
    //zh
    for(it->SeekToFirst();it->Valid();it->Next())
    {
        cout<<it->key().ToString()<<": "<<it->value().ToString()<<endl;
    }
    assert(it->status().ok());


    //范围扫描["name3",name8)
    for(it->Seek("name3");it->Valid()&&it->key().ToString()<"name8";it->Next())
    {
        cout<<it->key().ToString()<<": "<<it->value().ToString()<<endl;
    }

    delete db;//使用完之后要把数据库关掉
    return 0;
}
