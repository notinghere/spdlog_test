//
// Created by evan on 10/14/22.
//

#include <iostream>
#include "logger.hpp"

int main(int argc, char *argv[])
{
    XLogger::getInstance()->Init("debug","debug","test.log");
//    XLogger::getInstance()->Init("debug","debug");

    XLOG_INFO("hello");

    return 0;
}