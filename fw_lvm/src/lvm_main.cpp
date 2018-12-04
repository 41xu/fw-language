//
//  main.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

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
