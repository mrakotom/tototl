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
				tab.push_back((*loop)[i]);} \


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
    for(; loop != CSVIterator(); ++loop) {
    	string c=(*loop)[0];
    	if (c[0]=='#'){
    	if (c.compare("#TEST")) state=Test;
    	else if (c.compare("#D1")) state=D1;
    	else if (c.compare("#D2")) state=D2;
    	else if (c.compare("#D3")) state=D3;
    	else if (c.compare("#DICHO")) state=Dicho;
    	else if (c.compare("#P")) state=P;
    	else if (c.compare("#P")) state=Density;
    	else if (c.compare("#ITERATION")) state=Iteration;
    	}else{
    		if (state==Test){
    			if (c.compare("TEMPORAL")){
    				//test=Temporal;
    			}
    		}
    		else if (state==D1){ READ;bench.addDimension1(tab);}
    		else if (state==D2){ READ;bench.addDimension2(tab);}
    		else if (state==D3){ READ;bench.addDimension2(tab);}
    		else if (state==Dicho){ READ;bench.addThreshold(tab);}
    		else if (state==P){ READ;bench.addP(tab);}
    		else if (state==Density){ READ;bench.addDensity(tab);}
    		else if (state==Iteration){ READ;bench.addIteration(tab);}
    	}
    }
    bench.launchBench(output);
    return 0;
}
