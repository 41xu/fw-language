/*
 * @Author: fuujiro 
 * @Date: 2018-12-02 21:40:21 
 * @Last Modified by: fuujiro
 * @Last Modified time: 2018-12-03 18:17:06
 */

#ifndef FW_GLOBAL_H_
#define FW_GLOBAL_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define keynum 7
extern string keyword[];
extern string node;
extern int nodenum;

//variable type
enum var_type
{
    int_variable,
    int_array,
    string_varaible,
    string_array
};

//expression type
enum exp_type
{
    if_exp,
    while_exp,
};

class symbol {
public:
    string symbolname;
    int array_size = 0; //if variable is array , array_size is array length
    var_type type;
};

extern vector<string> codestream;
extern vector<symbol> symboltable;

void symbol_insert(string name, var_type type);
bool symbol_search(string name);
var_type symbol_gettype(string name);
symbol symbol_getsymbol(string name);
void error(string error);
string getsign(string choice);
char* string2char(string str);

#endif /* defined(FW_GLOBAL_H_) */