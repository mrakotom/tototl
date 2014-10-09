//============================================================================
// Name        : ozomatli.cpp
// Author      : Damien Dosimont
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <csvreader/CSVIterator.h>
#include <lpaggreg/OLPAggregWrapper.h>
#include "OLPBench.h"

#define READ vector<string> tab; \
			for (unsigned int i=0; i<(*loop).size(); i++){ \
				tab.push_back((*loop)[i].c_str());}\


using namespace std;

enum State { Idle, Test, D1, D2, D3, Dicho, P, Density, Iteration };

enum Test { Temporal, Spatiotemporal };

int main(int argc, const char* argv[]) {
	if (argc<2){
		cerr<<"Error: no input file provided"<<endl;
		return 1;
	}
	if (argc<3){
		cerr<<"Error: no output file found"<<endl;
		return 1;
	}
    ifstream input(argv[1]);
    ofstream *output=new ofstream(argv[2]);
    State state = Idle;
    //Test test = Temporal;
    OLPBench bench;
    //Iterator for parsing csv file. ',' is used as separator between each field.
    CSVIterator loop(input, ',');
    for(; loop != CSVIterator(); loop++) {
    	if ((*loop)[0].compare("#TEST")==0){ state=Test;}
    	else if ((*loop)[0].compare("#D1")==0) {state=D1;}
    	else if ((*loop)[0].compare("#D2")==0) {state=D2;}
    	else if ((*loop)[0].compare("#D3")==0) {state=D3;}
    	else if ((*loop)[0].compare("#DICHO")==0) {state=Dicho;}
    	else if ((*loop)[0].compare("#P")==0) {state=P;}
    	else if ((*loop)[0].compare("#DENSITY")==0) {state=Density;}
    	else if ((*loop)[0].compare("#ITERATION")==0) {state=Iteration;}
    	else if ((*loop)[0].compare("#END")==0) {break;}
    	else{
    		if (state==Test){
    			if ((*loop)[0].compare("TEMPORAL")==0){
    			}
    		}
    		else if (state==D1){ READ bench.addDimension1(tab);}
    		else if (state==D2){ READ bench.addDimension2(tab);}
    		else if (state==D3){ READ bench.addDimension3(tab);}
    		else if (state==Dicho){ READ bench.addThreshold(tab);}
    		else if (state==P){ READ bench.addP(tab);}
    		else if (state==Density){ READ bench.addDensity(tab);}
    		else if (state==Iteration){ READ bench.addIteration(tab);}
    	}
    }
    bench.launchBench(output);
    return 0;
}
