# FW Programming Language

### English: 

> FW(Functional Watse) Programming Language, is designed by C++. We create this toy programming language, compiler & virtual machine environment for Course Design of The Principle Compile.

### 中文: 

> 废物（功能性浪费）编程语言，由C++编写，实现了部分C子集功能。因为编译原理课设的原因，我们创造这个玩具编程语言，和相应的编译器以及虚拟机环境。

### Installation

Follow these steps below.

1. Download & make

    ```
    git clone https://github.com/fuujiro/fw-language.git

    cd fw-language/

    cd fw_compiler/

    make

    cd fw_lvm/

    make

    ```

2. Run

    ```
    cd fw-lanuage/

    cd fw-compiler/

    ./fw inputPath_File OutputPath_File # This step will create intermediate code file.

    cd ..

    cd fw-lvm/

    ./lvm inputPath_File OutputPath_File/null # lvm will interpret the intermediate file, and you can see the result in terminal.
    ```

3. Environmental configuration (Optional, but recommended)

    ```
    # MacOS
    cd ~
    vim ~/.bash_profile
    # Then you should add Path like below (need change your path to mine path!!!):
    export PATH="/Users/fzy/fuujiro/fuujiroCode/fw/fw_compile":"$PATH"
    export PATH="/Users/fzy/fuujiro/fuujiroCode/fw/fw_lvm":"$PATH"
    ```

    Test

    ```
    cd ~
    fw # if terminal can recognize the command, you make it!
    lvm # if terminal can recognize the command, you make it!
    ```
