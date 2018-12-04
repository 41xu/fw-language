/*
 * @Author: fuujiro 
 * @Date: 2018-12-02 22:21:08 
 * @Last Modified by: fuujiro
 * @Last Modified time: 2018-12-03 14:31:30
 */

#ifndef FW_AST_H_
#define FW_AST_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

char* string2char(string str);
string getsign(string choice);

//id
class id_ast {
public:
    string idname;
    id_ast(string name):idname(name){}
    void codegen();
};

//immediate number
class immediate_ast {
public:
    int number;
    immediate_ast(int num):number(num){}
    void codegen();
};

//number
class number_ast
{
public:
    int number;
    number_ast(int num) :number(num){}
    void codegen();
};

//string 
class string_ast { 
public:
    string str;
    string_ast(string str_value):str(str_value){}
    void codegen();
};

//int array
class intarray_ast {
public:
    string name;
    vector<int> values;
    int size;
    string end;
    intarray_ast(string array_name, vector<int> array_values, int array_size):
    name(array_name), values(array_values), size(array_size), end("$"){}
    void codegen();
};

//string array
class strarray_ast
{
public:
    string name;
    vector<string> values;
    int size;
    string end;
    strarray_ast(string array_name,vector<string> array_values,int array_size):
    name(array_name),values(array_values),size(array_size),end("$"){}
    void codegen();
};

//define int variable
class defvariable_ast
{
private:
    string int_name;
    number_ast * int_value;
public:
    defvariable_ast(string name,number_ast * number) :
    int_name(name),int_value(number){}
    void codegen();
};

//define string variable
class defstrvariable_ast
{
private:
    string str_name;
    string_ast * str_value;
public:
    defstrvariable_ast(string name,string_ast *value):
    str_name(name),str_value(value){}
    void codegen();
};

//assign varialbe
class assign_ast
{
private:
    string variable_name;
    string value_name;
public:
    assign_ast(string name,string value):
    variable_name(name),value_name(value){}
    void codegen();
};

//binary
class binary_ast
{
private:
    string op,left, right,save;
public:
    binary_ast(string Operator, string l, string r,string savelabel) :
    op(Operator), left(l), right(r),save(savelabel){}
    void codegen();
};

//judge
class judge_ast
{
private:
    string sign;
    string op;
    id_ast *left, *right;
public:
    judge_ast(string Operator, id_ast *l, id_ast *r,string sign_address) :
    op(Operator), left(l), right(r),sign(sign_address){}
    void codegen();
};

//if
class if_ast
{
private:
    string op;
    immediate_ast *left, *right;
public:
    if_ast(string Operator, immediate_ast *l, immediate_ast * r) :
    op(Operator), left(l), right(r){}
    void codegen();
};

//while
class while_ast
{
private:
    string op;
    immediate_ast *left, *right;
public:
    while_ast(string Operator, immediate_ast *l, immediate_ast *r) :
    op(Operator), left(l), right(r){}
    void codegen();
};

//call funciton
class callfunc_ast
{
private:
    string func_name;
public:
    callfunc_ast(string name) :
    func_name(name){}
    void codegen();
};

class function_ast
{
private:
    string func_name;
public:
    function_ast(string name) :
    func_name(name){}
    void codegen();
};

//label address
class sign_ast
{
private:
    string choice;
public:
    string sign;
    sign_ast(string str):choice(str){}
    void get_sign();
    void codegen();
};

//end label
class end_ast
{
private:
    string end;
    string sign;
public:
    end_ast(string strend,string sign_address) :
    end(strend),sign(sign_address){}
    void codegen();
};

//system function print()
class print_ast
{
private:
    string content;
public:
    print_ast(string str_content):
    content(str_content){};
    void codegen();
};

//program end
class program_end
{
public:
    void codegen();
};
#endif /* defined(FW_AST_H_) */