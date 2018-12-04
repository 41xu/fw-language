/*
 * @Author: fuujiro 
 * @Date: 2018-12-04 21:35:51 
 * @Last Modified by:   fuujiro 
 * @Last Modified time: 2018-12-04 21:35:51 
 */

#include <iostream>
#include "lvm_assembler.h"
#include "lvm_lmachine.h"
using namespace std;

int main(int argc, char** argv) {
    Lmachine lvm;
    lvm.init(argc, argv);         //init lmachine
    lvm.readline();     //get code
    Assembler assembler;
    assembler.assemblerrun();
    lvm.lvmrun(assembler);
    cout<<"lvm is over ..."<<endl;
    return 0;
}
