/*
 * @Author: fuujiro 
 * @Date: 2018-12-03 14:06:49 
 * @Last Modified by: fuujiro
 * @Last Modified time: 2018-12-03 14:46:22
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "fw_ast.h"
#include "fw_token.h"
using namespace std;

void immediate_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout << " " << number << endl;
    fout.close();
}

void number_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout << "OPLOADVB AL " << number << endl;
    fout.close();
}

void string_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout<<"OPLOADVB DL "<<"\""<<str<<"\""<<endl;
    fout.close();
}


void strarray_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout<<"OPINITLIST "<<name<<" ";
    for (int size=0; size<values.size(); size++)
        fout<<"\""<<values[size]<<"\""<<" ";
    fout<<end<<endl;
    fout.close();
}

void intarray_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout << "OPINITLIST " << name<<" ";
    for (int size = 0; size < values.size(); size++)
        fout << values[size] << " ";
    fout << end << endl;
    fout.close();
}

void defvariable_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    int_value->codegen();
    fout << "OPINIT " << int_name << " AL" << endl;
    fout.close();
}

void defstrvariable_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    str_value->codegen();
    fout<<"OPINIT "<<str_name<<" DL"<<endl;
    fout.close();
}

void assign_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout<<"OPASSIGN "<<variable_name<<" "<<value_name<<endl;
    fout.close();
}
void binary_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    if (op=="+")
        fout<<"OPBINADD "+save+" "+left+" "+right<<endl;
    else if(op=="-")
        fout<<"OPBINSUB "+save+" "+left+" "+right<<endl;
    else if(op=="*")
        fout<<"OPBINMUL "+save+" "+left+" "+right<<endl;
    else if(op=="/")
        fout<<"OPBINDIV "+save+" "+left+" "+right<<endl;
    fout.close();
}
void judge_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    if (op == "<")
        fout << "OPJNG " << left->idname << " " << right->idname << " " << sign << endl;
    else if(op==">")
        fout<<"OPJG "<<left->idname<<" "<<right->idname<<" "<<sign<<endl;
    fout.close();
}

void callfunc_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout << "JMP " <<func_name<< endl;
    fout.close();
}

void function_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout << func_name << " :" << endl;
    fout.close();
}

void sign_ast::get_sign()
{
    this->sign = getsign(this->choice);
}

void sign_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout <<this->sign<< " :" << endl;
    fout.close();
}

void end_ast::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout << end <<" "<<sign<<endl;
    fout.close();
}

void print_ast::codegen()
{
    if (symbol_gettype(content)==int_array) {
        ofstream fout;
        fout.open(string2char(token::outfile),ios::app);
        fout<<"OPPRINTRLIST "<<content<<endl;
        fout.close();
    }
    else
    {
        ofstream fout;
        fout.open(string2char(token::outfile),ios::app);
        fout<<"OPLOADVB DL "<<content<<endl;
        fout<<"OPPRINTR DL"<<endl;
        fout.close();
    }
}

void program_end::codegen()
{
    ofstream fout;
    fout.open(string2char(token::outfile),ios::app);
    fout<<"OPHALT"<<endl;
    fout.close();
}

