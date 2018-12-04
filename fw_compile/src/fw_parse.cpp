/*
 * @Author: fuujiro 
 * @Date: 2018-12-02 23:48:17 
 * @Last Modified by: fuujiro
 * @Last Modified time: 2018-12-04 09:38:02
 */

#include <iostream>
#include <string>
#include <stack>
#include "fw_parse.h"
#include "fw_ast.h"
#include "fw_global.h"
using namespace std;

//static
int parse::index = 0;

int parse::string2int(string str)
{
    return atoi(str.c_str());
}

//type check
void parse::parse_typecheck(string type)
{
    if(type == "int")
        return;
    if(type == "string")
        return;
    else
        error("No such variable type");
}

//id name check
void parse::parse_idcheck(string id)
{
    for(int keyindex = 0; keyindex < keynum; keyindex++)
    {
        if(keyword[keyindex] == id)
        {
            error(id + " is a key word");
            break;
        } else
            continue;
    }
}

//token check
void parse::parse_tokenjudge(string token)
{
    if(codestream[index] != token)
    {
        error("Expected token " + token);
        return;
    }
    else
        return;
}

//check number or not
bool parse::parse_judgenumber(string num)
{
    bool flag = true;
    for(int numindex=0;numindex<num.size();numindex++)
    {
        char c=num[numindex];
        if(!isdigit(c)) {
            flag = false;
        }
    }
    return flag;
}

//check array size type is int or not
void parse::parse_numbercheck(string num)
{
    if(!parse_judgenumber(num))
        error("Must be number value");
}

//check operator
void parse::parse_operatorcheck(string op)
{
    if (op == "+" || op == "-" || op == "*" || op == "/")
        return;
    else
        error("This is a illegal operator");
}

//judge operator
bool parse::judge_op(string token)
{
    if (token == "+" || token == "-" || token == "*" || token == "/")
        return true;
    else
        return false;
}

//judge variable
bool parse::judge_variable(string token) {
    if(symbol_search(token))
        return true;
    else   
        return false;
}

//judge system function
bool parse::judge_system_func(string name)
{
    if(name=="print")
        return true;
    else
        return false;
}

//operator level
bool parse::lowlevel(string token,string top)
{
    if ((token == "*" || token == "/")&&(top == "+" || top == "-"))
        return false;
    else
        return true;
}

//arithmetic operation
int parse::operation(int num1, int num2,string op)
{
    int out;
    if (op == "+")
        out = num1 + num2;
    else if (op == "-")
        out = num1 - num2;
    else if (op == "*")
        out = num1 * num2;
    else if (op == "/")
        out = num1 / num2;
    return out;
}

//get array information
string parse::parse_getarrayinfo(string variable_name)
{
    index++;
    parse_tokenjudge("[");
    index++;
    string array_index=getsign("next");
    parse_binary(array_index);
    int array_size=string2int(array_index);
    symbol inistsymbol=symbol_getsymbol(variable_name);
    if(array_size>inistsymbol.array_size)
        error("Array out of bouds");
    parse_tokenjudge("]");
    index++;
    string array_name=variable_name+"["+array_index+"]";
    return array_name;
}

//get variable real information
string parse::parse_get_variable_real(string variable_name)
{
    if(symbol_gettype(variable_name)==int_array)
        return parse_getarrayinfo(variable_name);
    else if(symbol_gettype(variable_name)==int_variable)
    {
        index++;
        return variable_name;
    }
    else if(parse_judgenumber(variable_name))
    {
        index++;
        return variable_name;
    }
    else
        return variable_name;
}

/* arithmetic operation immediate number
 int parse::binary_immediate()
 {
 stack<int> num;
 stack<string> op;
 int exp_index=index;
 while (codestream[exp_index] != "\n")
 {
 string token = codestream[index];
 if (judge_op(token))
 {
 if (op.size() == 0)
 op.push(token);
 else if (lowlevel(token, op.top()))
 {
 int number2 = num.top();
 num.pop();
 int number1 = num.top();
 num.pop();
 string operand = op.top();
 int out = operation(number1, number2, operand);
 num.push(out);
 }
 else
 {
 op.push(token);
 }
 }
 else if (judge_variable(token))
 {
 int variable_value = symbol_getvalue(token);
 num.push(variable_value);
 }
 else //number
 {
 int number = string2int(token);
 num.push(number);
 }
 exp_index++;
 }
 while (op.size() != 0)
 {
 int number2 = num.top();
 num.pop();
 int number1 = num.top();
 num.pop();
 string operand = op.top();
 op.pop();
 int out = operation(number1, number2, operand);
 num.push(out);
 }
 return num.top();
 }
 
 int parse::getvalue(string name)
 {
 int value;
 if (judge_variable(name))
 value = symbol_getvalue(name);
 else
 value = string2int(name);
 return value;
 }
 */


//build syntax tree
void parse::build_ast()
{
    for (index = 0; index < codestream.size(); index++)
    {
        string token = codestream[index];
        //statement or define variable
        if (token == "var")
        {
            index++;
            parse_defvar();
        }
        //binary expreesion
        else if (judge_variable(token))
        {
            string variable_name = codestream[index];
            index++;
            if (codestream[index] == "=")
            {
                index++;
                parse_binary(variable_name);
            }
        }
        else if (token == "def")
        {
            index++;
            parse_func();
        }
        //system function
        else if(judge_system_func(codestream[index]))
        {
            parse_system_func();
        }
        else if (codestream[index] == "\n")
            continue;
    }
    program_end * end=new program_end;
    end->codegen();
    cout<<"fw_Complier is running successfully."<<endl;
}

//statement or define variable
void parse::parse_defvar()
{
    string type = codestream[index];
    parse_typecheck(type);
    index++;
    string name = codestream[index];
    parse_idcheck(name);
    index++;
    //string
    if(type=="string")
    {
        //string array : still doing now...
        if(codestream[index]=="[")
        {
            index++;
            parse_numbercheck(codestream[index]);
            int size=string2int(codestream[index]);
            index++;
            parse_tokenjudge("]");
            index++;
            //string array define
            if(codestream[index]=="=")
            {
                index++;
                parse_tokenjudge("{");
                index++;
                vector<string> str_array;
                while (codestream[index]!="}") {
                    parse_tokenjudge("\"");
                    index++;
                    string value;
                    while (codestream[index]!="\"") {
                        value=codestream[index];
                        index++;
                    }
                    index++; //read "
                    str_array.push_back(value);
                    if(codestream[index]=="}")
                        break;
                    parse_tokenjudge(",");
                    index++;
                }
                symbol_insert(name,string_varaible);
                strarray_ast * array=new strarray_ast(name,str_array,size);
                array->codegen();
            }
            //string variable statement
            else
            {
                vector<string> str_array;
                symbol_insert(name, string_varaible);
                strarray_ast * array=new strarray_ast(name,str_array,0);
                array->codegen();
            }
        }
        //string normal variable
        else
        {
            bool continuous=true; //continuous declaration variable
            while(continuous)
            {
                //string variable define
                if(codestream[index]=="=")
                {
                    index++;
                    string value="";
                    parse_tokenjudge("\"");
                    index++;
                    while(codestream[index]!="\"")
                    {
                        value+=codestream[index];
                        index++;
                    }
                    index++; // read "
                    symbol_insert(name, string_varaible);
                    string_ast * string_value=new string_ast(value);
                    defstrvariable_ast * str_variable=new defstrvariable_ast(name,string_value);
                    str_variable->codegen();
                }
                //string variable statement
                else
                {
                    symbol_insert(name, string_varaible);
                    string_ast * string_value=new string_ast(" ");
                    defstrvariable_ast * str_variable=new defstrvariable_ast(name,string_value);
                    str_variable->codegen();
                }
                if(codestream[index]==",")
                {
                    index++;
                    continuous=true;
                    name=codestream[index];
                    index++;
                }
                else
                    continuous=false;
            }
        }
    }
    //int
    else if (type=="int")
    {
        //int array
        if(codestream[index]=="[")
        {
            index++;
            parse_numbercheck(codestream[index]);
            int size = string2int(codestream[index]);
            index++;
            parse_tokenjudge("]");
            index++;
            //int array define
            if (codestream[index] == "=")
            {
                index++;
                parse_tokenjudge("{");
                index++;
                vector<int> num;
                while (codestream[index] != "}")
                {
                    if (codestream[index] == ",")
                    {
                        index++;
                        continue;
                    }
                    else
                        num.push_back(string2int(codestream[index]));
                    index++;
                }
                index++;// " { "
                symbol_insert(name, int_array);
                intarray_ast * array = new intarray_ast(name,num,size);
                array->codegen();
            }
            //int array statement
            else
            {
                vector<int> num;
                symbol_insert(name, int_array);
                intarray_ast * array=new intarray_ast(name,num,0);
                array->codegen();
            }
        }
        //int normal variable
        else
        {
            bool continuous=true; //continuous declaration variable
            while (continuous) {
                //int variable define
                if (codestream[index] == "=")
                {
                    index++;
                    number_ast *value = new number_ast(0);
                    defvariable_ast *variable = new defvariable_ast(name, value);
                    variable->codegen();
                    parse_binary(name);
                    symbol_insert(name, int_variable);
                }
                //int variable statement
                else
                {
                    symbol_insert(name, int_variable);
                    number_ast *value = new number_ast(0);
                    defvariable_ast *variable = new defvariable_ast(name, value);
                    variable->codegen();
                }
                if(codestream[index]==",")
                {
                    index++;
                    continuous=true;
                    name=codestream[index];
                    index++;
                }
                else
                    continuous=false;
            }
        }
    }
}

//binary expression
void parse::parse_binary(string variable_name)
{
    string value=parse_binary_exp();
    assign_ast * assign=new assign_ast(variable_name,value);
    assign->codegen();
}

//BNF expression
string parse::parse_binary_exp()
{
    string op1,op2,operation;
    op1=parse_binary_term();
    operation=codestream[index];
    if (operation!="+"&&operation!="-"&&operation!="*"&&operation!="/")
        return op1;
    parse_operatorcheck(operation);
    while(operation=="+"||operation=="-")
    {
        string newlabel=getsign("next");
        index++;
        op2=parse_binary_term();
        binary_ast * binary=new binary_ast(operation,op1,op2,newlabel);
        binary->codegen();
        op1=newlabel;
        operation=codestream[index];
    }
    return op1;
}

//BNF term
string parse::parse_binary_term()
{
    string op1,op2,operation;
    op1=parse_binary_factor();
    operation=codestream[index];//operator
    if (operation!="+"&&operation!="-"&&operation!="*"&&operation!="/")
        return op1;
    parse_operatorcheck(operation);
    while (operation=="*"||operation=="/")
    {
        string newlabel=getsign("next");
        index++;
        op2=parse_binary_factor();
        binary_ast * binary=new binary_ast(operation,op1,op2,newlabel);
        binary->codegen();
        op1=newlabel;
        operation=codestream[index];
    }
    return op1;
}

//BNF factor
string parse::parse_binary_factor()
{
    string id=codestream[index];
    if(parse_judgenumber(id))
    {
        index++;
        return id;
    }
    else if (symbol_search(id))
    {
        if(symbol_gettype(id)==int_array) //array
            return parse_getarrayinfo(id);
        else
        {
            index++;
            return id;
        }
    }
    else
        return "";
}

//function
void parse::parse_func()
{
    string func_name = codestream[index];
    parse_idcheck(func_name);
    index++;
    function_ast * function = new function_ast(func_name);
    function->codegen();
    parse_tokenjudge("(");
    index++;
    parse_tokenjudge(")");
    index++;
    while (codestream[index]!="{")
        index++;
    if (codestream[index] == "{")
    {
        index++;
        parse_expression();
    }
}

//system function
void parse::parse_system_func()
{
    if(codestream[index]=="print")
    {
        index++;
        parse_system_print();
    }
}

//system function print()
void parse::parse_system_print()
{
    parse_tokenjudge("(");
    index++;
    string content;
    while (codestream[index]!=")") {
        content+=codestream[index];
        index++;
    }
    index++;
    print_ast * print=new print_ast(content);
    print->codegen();
}

//native expression
void parse::parse_expression()
{
    while (codestream[index] != "}")
    {
        if (codestream[index] == "if")
        {
            index++;
            parse_if();
        }
        else if (codestream[index] == "while")
        {
            index++;
            parse_while();
        }
        else if (judge_variable(codestream[index]))
        {
            string variable_name = codestream[index];
            string real_variable_name=parse_get_variable_real(variable_name);
            parse_tokenjudge("=");
            index++;
            parse_binary(real_variable_name);
        }
        //statement or define variable
        else if (codestream[index] == "var")
        {
            index++;
            parse_defvar();
        }
        else if(judge_system_func(codestream[index]))
            parse_system_func();
        else if (codestream[index] == "\n")
            index++;
    }
    index++;
}

//judge expression .like while if ...
void parse::parse_judge(exp_type type,string choice)
{
    vector<string> codes;
    parse_tokenjudge("(");
    index++;
    string left_cmp=getsign("next");
    parse_binary(left_cmp);
    codes.push_back(left_cmp);
    string op=codestream[index];
    index++;
    codes.push_back(op);
    string right_cmp=getsign("next");
    parse_binary(right_cmp);
    codes.push_back(right_cmp);
    if (type == if_exp)
    {
        parse_bool(codes,choice);
    }
    else if (type == while_exp)
    {
        parse_bool(codes,choice);
    }
    parse_tokenjudge(")");
    index++;
}

//parse bool expression
void parse::parse_bool(vector<string> codes,string choice)
{
    string sign;
    string left = codes[0];
    id_ast * left_ast=new id_ast(left);
    string op = codes[1];
    string right = codes[2];
    id_ast * right_ast=new id_ast(right);
    if(choice=="now"||choice=="next")
        sign=getsign(choice);
    else
        sign=choice;
    judge_ast *judge = new judge_ast(op, left_ast, right_ast,sign);
    judge->codegen();
}

//if expression
void parse::parse_if()
{
    string strsign;
    parse_judge(if_exp,"next");
    while (codestream[index] != "{")
        index++;
    index++;
    //write label address
    sign_ast * addr_sign = new sign_ast("now");
    addr_sign->get_sign();
    addr_sign->codegen();
    strsign=addr_sign->sign;
    //block expreesion
    parse_expression();
    //end label
    end_ast * end = new end_ast("OPEND",strsign);
    end->codegen();
}

//while expression
void parse::parse_while()
{
    string strsign;
    vector<string> codes;
    int judge_startindex=index;
    parse_judge(while_exp,"next");
    while (codestream[index] != "{")
        index++;
    index++;
    //write label address
    sign_ast * addr_sign = new sign_ast("now");
    addr_sign->get_sign();
    addr_sign->codegen();
    strsign=addr_sign->sign;
    //block expreesion
    parse_expression();
    //end label
    end_ast * end = new end_ast("OPEND",strsign);
    end->codegen();
    int block_endindex=index;
    index=judge_startindex;
    parse_judge(while_exp,strsign);
    index=block_endindex;
}

