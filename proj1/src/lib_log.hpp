//
// Created by evan on 10/17/22.
//

#ifndef COMPONENTS_LIB_LOG_HPP
#define COMPONENTS_LIB_LOG_HPP

#include <iostream>


// so库头文件 lib_testLog.h
extern void (*__LIB_WRITE_LOG)(std::string buff);

int add(int a,int b);

#endif //COMPONENTS_LIB_LOG_HPP
