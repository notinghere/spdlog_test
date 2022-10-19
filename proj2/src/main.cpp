//
// Created by evan on 10/14/22.
//

#include <iostream>
#include "logger.hpp"
#include "lib_log.hpp"

static void mainApp_writeLogFunc(std::string buff)
{
    // 此接口是对zlog日志库进一步封装得到的主程序写日志函数
    XLOG_INFO(buff);
}

int main(int argc, char *argv[])
{
    XLogger::getInstance()->Init("debug","debug","test.log");
//    XLogger::getInstance()->Init("debug","debug");

    __LIB_WRITE_LOG = mainApp_writeLogFunc;

    XLOG_INFO("hello");

    int a = add(2,3);
    XLOG_INFO("2+3={}",a);

    return 0;
}