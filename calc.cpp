/************************************* 
Fabrice Lacout
ID: 5652857
project1 calculator/  main function
***************************************/


#include "calculator.h"

bool verbose=false;
int main (int argc, char* argv[]){
    if (argc==1) tokenizeLine();
    else {
        if (argv[1][1]=='h') showDocumentation();
		else if (argv[1][1]=='v') {
	    	verbose=true;
	    	tokenizeLine();
		}
		else std::cout <<"Usage: ˜/bin/calc [-h] [-v]";
    }
    return 0;    
}
