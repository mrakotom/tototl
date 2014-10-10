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
#include "DLPBench.h"

#define READ vector<string> tab; \
			for (unsigned int i=0; i<(*loop).size(); i++){ \
				tab.push_back((*loop)[i].c_str());}

#define SBENCH DLPBench* bencht=static_cast<DLPBench*>(bench);\
				bencht

#define TBENCH bench

#define TEST type!=Void



using namespace std;

enum State { Idle, Test, D1, D2, D3, Dicho, P, Density, Iteration, Tree};

enum Type { Void, Temporal, Spatiotemporal };

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
    Type type = Void;
    OLPBench * bench = new OLPBench();
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
    			if ((*loop)[0].compare("TEMPORAL")==0){ type=Temporal;}
    			else if ((*loop)[0].compare("SPATIOTEMPORAL")==0){ type=Spatiotemporal; delete bench; bench = new DLPBench();}
    		}
    		else if (TEST && state==D1){ READ TBENCH->addDimension1(tab);}
    		else if (TEST && state==D2){ READ TBENCH->addDimension2(tab);}
    		else if (TEST && state==D3){ READ TBENCH->addDimension3(tab);}
    		else if (TEST && state==Dicho){ READ TBENCH->addThreshold(tab);}
    		else if (TEST && state==P){ READ TBENCH->addP(tab);}
    		else if (TEST && state==Density){ READ TBENCH->addDensity(tab);}
    		else if (TEST && state==Iteration){ READ TBENCH->addIteration(tab);}
    		else if (TEST && state==Tree&&type==Spatiotemporal){ READ SBENCH->addStructure(tab);}
    	}
    }
    if (type==Temporal){
    	TBENCH->launchBench(output);
    }else if (type==Spatiotemporal){
    	SBENCH->launchBench(output);
    }
    return 0;
}
