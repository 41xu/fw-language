/*
 * @Author: fuujiro 
 * @Date: 2018-12-02 21:53:17 
 * @Last Modified by: fuujiro
 * @Last Modified time: 2018-12-04 11:08:13
 */

#ifndef FW_TOKEN_H_
#define FW_TOKEN_H_

#include <iostream>
#include <string>
#include <cstring>
#include "fw_global.h"
using namespace std;

class token {
public:
    char* string2char(string str);
    static string infile;
    static string outfile;
    bool tokeninit(int argc, char** argv);
    void readline();
};
#endif /* defined(FW_TOKEN_H_) */