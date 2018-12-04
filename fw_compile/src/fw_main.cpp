/*
 * @Author: fuujiro 
 * @Date: 2018-12-02 21:36:54 
 * @Last Modified by: fuujiro
 * @Last Modified time: 2018-12-04 11:26:46
 */

#include <iostream>
#include "fw_token.h"
#include "fw_parse.h"
using namespace std;

int main(int argc, char** argv) {
    token tokenmachine; // start tokenizer
    // Check for existence of the path & Input file
    if(tokenmachine.tokeninit(argc, argv)) { // exist
        tokenmachine.readline(); // Tokenizer analysising..。
        parse parsemachine; // start parser
        parsemachine.build_ast(); // building Abstract Syntax Tree
        cout << "fw_Compiler's font_end is over..." << endl;
    } else { // nope 
        cout << "Sorry...We have a littile wrong, maybe you should modify bug, try next!" << endl;
    }
    return 0;
}