fw:fw_main.o fw_ast.o fw_global.o fw_parse.o fw_token.o
	g++ -g fw_main.o fw_ast.o fw_global.o fw_parse.o fw_token.o -o fw
fw_main.o:src/fw_main.cpp src/fw_token.h src/fw_parse.h
	g++ -std=c++11 -g -c src/fw_main.cpp
fw_ast.o:src/fw_ast.cpp src/fw_ast.h src/fw_token.h
	g++ -std=c++11 -g -c src/fw_ast.cpp
fw_global.o:src/fw_global.cpp src/fw_global.h
	g++ -std=c++11 -g -c src/fw_global.cpp
fw_parse.o:src/fw_parse.cpp src/fw_parse.h src/fw_ast.h src/fw_global.h
	g++ -std=c++11 -g -c src/fw_parse.cpp
fw_token.o:src/fw_token.cpp src/fw_token.h src/fw_global.h
	g++ -std=c++11 -g -c src/fw_token.cpp

clean:
	rm -f *.o fw
