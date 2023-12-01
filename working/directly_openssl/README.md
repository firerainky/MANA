 搞个项目直接 link openssl 的二进制包
 
 可惜的是目前还是不行，会报类似下面的错：
 ```shell
 In file included from /usr/include/c++/11/bits/localefwd.h:42,
                 from /usr/include/c++/11/ios:41,
                 from /usr/include/c++/11/ostream:38,
                 from /usr/include/c++/11/iostream:39,
                 from /home/zky/cpp/MANA/working/directly_openssl/main.cpp:2:
/usr/include/c++/11/cctype:64:11: error: ‘isalnum’ has not been declared in ‘::’
   64 |   using ::isalnum;
      |           ^~~~~~~
 ```

 尚不清楚是什么原因，可能是对 openssl 编译链接的方式不太对

 可以去搜一下或者是查一下 openssl install 的步骤里都干了什么？