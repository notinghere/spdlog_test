//
// Created by evan on 10/17/22.
//

#include "lib_log.hpp"

// so库实现文件 lib_testLog.c
void (*__LIB_WRITE_LOG)(std::string buff) = NULL;

int add(int a, int b) {

    __LIB_WRITE_LOG("log_test2");

    return a + b;
}