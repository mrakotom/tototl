/*
 * DLPBench.cpp
 *
 *  Created on: 10 oct. 2014
 *      Author: dosimont
 */

#include "DLPBench.h"

namespace std {

DLPBench::DLPBench(): OLPBench(OLPBench()), structure(new vector<int>()), dlp(0){
	// TODO Auto-generated constructor stub
}

DLPBench::~DLPBench() {
	delete structure;
}

void DLPBench::addStructure(vector<string> tab) {
	addLineInteger(tab, structure);
}

void DLPBench::generateMatrix(int time, int nodes, int types, double density,
		int structure, ostream *output) {
	dlp= new DLPAggregWrapper(2);
    vector<VirtualNode*>elements=vector<VirtualNode*>();
    vector<VirtualNode*>leaves=vector<VirtualNode*>();
    vector<VirtualNode*>pendings=vector<VirtualNode*>();

    dlp->newRoot(0);
    elements.push_back(new VirtualNode());

    for (int i=1, j=0; i<nodes+1; i++) {
       elements.push_back(new VirtualNode(i,elements[j]));
       if (i%structure==0)
                j++;
        }

    for (unsigned int i=1; i< elements.size(); i++) {
        if (!elements[i]->hasChild()){
            leaves.push_back(elements[i]);
        }else{
        	pendings.push_back(elements[i]);
        }
    }
    *output<<", " << nodes+1 << ", " << leaves.size() << ", " << structure;
    for (unsigned int i=0; i< pendings.size(); i++) {
    	dlp->newNode(pendings[i]->getId(), pendings[i]->getFather()->getId());
    }
    for (unsigned int i=0; i< leaves.size(); i++) {
    	dlp->newLeaf(leaves[i]->getId(), leaves[i]->getFather()->getId());
    	for (int t=0; t<time; t++){
    		dlp->addVector(leaves[i]->getId());
    		for (int e=0; e<types; e++){
    			dlp->push_back(leaves[i]->getId(),generateValue(density));
    		}
    	}
    }

    dlp->validate();

    delete elements[0];
}

void DLPBench::launchTest(ostream* output, double p) {
	timeval t1,t2;
	int dicho;
	double param=p;
	dlp->computeQualities(false);
	gettimeofday(&t1, NULL);
	dlp->computeDichotomy(threshold);
	gettimeofday(&t2, NULL);
	dicho=((t2.tv_sec - t1.tv_sec) * 1000)
			+ ((t2.tv_usec - t1.tv_usec) / 1000);
	if (param==-1){
		param=rand()/RAND_MAX;
	}
	dlp->computeParts(param);
	*output << ", " << dlp->getRoot()->getQualityCount() << ", " << dlp->getRoot()->getBestCutCount() << ", " << dlp->getRoot()->getBestPartitionCount() << ", " << dlp->getRoot()->getQualityDuration() << ", " << dicho << ", " << dlp->getRoot()->getBestCutDuration() << ", " << dlp->getRoot()->getBestPartitionDuration() << ", " << dlp->getParameterNumber()<<endl;
	delete dlp;
}

void DLPBench::launchBench(ostream *output) {
	int total=dimension1->size()*dimension2->size()*dimension3->size()*density->size()*p->size()*structure->size()*iteration;
	cout<<total<< " tests to run"<<endl;
	int num=0;
	int cdimension1=1;
	int cdimension2=1;
	int cdimension3=1;
	int cstructure=2;
	double cdensity=1;
	double cp=1;
	printSpaceHeader(output);
	for (unsigned int i=0; i<dimension1->size();i++){
		cdimension1=(*dimension1)[i];
		for (unsigned int j=0; j<dimension2->size();j++){
			cdimension2=(*dimension2)[j];
			for (unsigned int k=0; k<dimension3->size();k++){
				cdimension3=(*dimension3)[k];
				for (unsigned int o=0; o<structure->size(); o++){
					cstructure=(*structure)[o];
					for (unsigned int l=0; l<density->size(); l++){
						cdensity=(*density)[l];
						for (unsigned int m=0; m<p->size(); m++){
							cp=(*p)[m];
							for (int n=0; n<iteration; n++){
								*output<< (++num) <<", "<< cdimension1 <<", "<< cdimension2 <<", "<< cdimension3 <<", "<< threshold;
								if (cp==-1){
									*output<<", "<< "rand";
								}else{
									*output<<", " << cp;
								}
								*output<<", " << cdensity;
								generateMatrix(cdimension1,cdimension2,cdimension3,cdensity,cstructure, output);
								launchTest(output,cp);
								double pc=(double)num/(double)total;
								cout<<'\r'<<pc<< " %                    ";
								}
							}
						}
					}
				}
			}
		}
	}

void printSpaceHeader(ostream *output){
	*output << "N, DIM1, DIM2, DIM3, DICHO, P, DENSITY, NODES, LEAVES, TREE, COUNTER Q, COUNTER BC, COUNTER BP, TIME Q, TIME DICHO, TIME BC, TIME BP, P RETRIEVED" <<endl;
}

} /* namespace std */
