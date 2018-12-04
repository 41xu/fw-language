/*
 * @Author: fuujiro 
 * @Date: 2018-12-02 22:52:42 
 * @Last Modified by: fuujiro
 * @Last Modified time: 2018-12-04 11:30:02
 */

#include <iostream>
#include <fstream>
#include <string>
#include "fw_global.h"
#include "fw_token.h"
using namespace std;

//static variable
string token::infile = "";
string token::outfile = "";

char fileIn[100];
char fileOut[100];
FILE* fileAp = NULL;
FILE* fileBp = NULL;

char* token::string2char(string str) {
    return const_cast<char *>(str.c_str());
}

// need change 1
/* bool token::tokeninit()
{
    cout << "please enter source file path and name :";
    cin >> infile;
    ifstream search;
    char *starfile = string2char(infile);
    search.open(starfile);
    if (!search)
        cout << "source file " << infile << " not find " << endl;
    while (!search) {
        cout << "please input correct file  path and name :" << endl;
        cin >> infile;
        search.open(string2char(infile));
    }
    cout << "please enter output file path and name :";
    cin >> outfile;
    ofstream newoutfile;
    newoutfile.open(string2char(outfile));
    if (newoutfile)
        cout << "file " << outfile << " is create success " << endl;
    return true;
} */

bool token::tokeninit( int argc, char** argv)
{
    strcpy(fileIn, argv[1]);
    strcpy(fileOut, argv[2]);
    if(fopen(fileIn, "r") == NULL)
    {
        printf("can not find file named %s.\n", fileIn);
        return false;
    }
    infile = fileIn;
    outfile = fileOut;
    cout << infile << " is read success." << endl;
    cout << outfile << " is create success." << endl;
    return true;
}

void token::readline()
{
    int index, length;
    ifstream code;
    code.open(infile);
    string line;
    while (getline(code, line)) {
        length = int(line.length());
        index = 0;
        while (index<length) {
            //number
            if (line[index] >= '0'&&line[index] <= '9')
            {
                string token = "";
                token += line[index];
                index++;
                while (line[index] >= '0'&&line[index]<'9') {
                    token += line[index];
                    index++;
                }
                codestream.push_back(token);
            }
            //id
            else if ((line[index] >= 'a'&&line[index]<'z') || (line[index] >= 'A'&&line[index] <= 'Z'))
            {
                string token = "";
                token += line[index];
                index++;
                while ((line[index] >= 'a'&&line[index]<'z') || (line[index] >= 'A'&&line[index] <= 'Z') || (line[index] >= '0'&&line[index]<'9')) {
                    token += line[index];
                    index++;
                }
                codestream.push_back(token);
            }
            //symbol
            else if (line[index] == ';'||line[index]==','||line[index]=='"'||line[index]=='\\')
            {
                string token = "";
                token += line[index];
                index++;
                codestream.push_back(token);
            }
            //operator
            else if (line[index] == '+' || line[index] == '-' || line[index] == '*' || line[index] == '/')
            {
                string token = "";
                token += line[index];
                index++;
                codestream.push_back(token);
            }
            //comparison operator
            else if (line[index] == '=' || line[index] == '<' || line[index] == '>')
            {
                string token = "";
                token += line[index];
                index++;
                codestream.push_back(token);
            }
            //brcket
            else if (line[index] == '{' || line[index] == '}' || line[index] == '(' || line[index] == ')'||line[index]=='['||line[index]==']')
            {
                string token = "";
                token += line[index];
                index++;
                codestream.push_back(token);
            }
            //comments
            else if (line[index] == '#')
            {
                index++;
                while (index<length) {
                    index++;
                }
            }
            //space
            else if(line[index]=='\t'||line[index]=='\n'||line[index]==' ')
                index++;
        }
        string end = "\n";
        codestream.push_back(end);
    }
}

