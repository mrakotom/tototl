/*
 * DLPBench.cpp
 *
 *  Created on: 10 oct. 2014
 *      Author: dosimont
 */

#include "DLPBench.h"

namespace std {

DLPBench::DLPBench(): OLPBench(OLPBench()), structure(new vector<int>()), dlp(DLPAggregWrapper(2)){
	// TODO Auto-generated constructor stub
}

DLPBench::~DLPBench() {
	// TODO Auto-generated destructor stub
}

void DLPBench::addStructure(vector<string> tab) {
}

void DLPBench::generateMatrix(int i, int j, int k, double density,
		int structure) {
}

void DLPBench::launchTest(ostream* output, double p) {
	timeval t1,t2;
	int dicho;
	double param=p;
	olp->computeQualities(false);
	gettimeofday(&t1, NULL);
	olp->computeDichotomy(threshold);
	gettimeofday(&t2, NULL);
	dicho=((t2.tv_sec - t1.tv_sec) * 1000)
			+ ((t2.tv_usec - t1.tv_usec) / 1000);
	if (param==-1){
		param=rand()/RAND_MAX;
	}
	olp->computeParts(param);
	*output << ", " << olp->getAggreg()->getQualityCount() << ", " << olp->getAggreg()->getBestCutCount() << ", " << olp->getAggreg()->getBestPartitionCount() << ", " << olp->getAggreg()->getQualityDuration() << ", " << dicho << ", " << olp->getAggreg()->getBestCutDuration() << ", " << olp->getAggreg()->getBestPartitionDuration() << ", " << olp->getParameterNumber()<<endl;
	delete olp;
}

void DLPBench::launchBench(ostream *output) {
	int num=0;
	int cdimension1=1;
	int cdimension2=1;
	int cdimension3=1;
	int cstructure=1;
	double cdensity=1;
	double cp=1;
	printHeader(output);
	for (unsigned int i=0; i<dimension1->size();i++){
		cdimension1=(*dimension1)[i];
		for (unsigned int j=0; j<dimension2->size();j++){
			cdimension2=(*dimension2)[j];
			for (unsigned int k=0; k<dimension3->size();k++){
				cdimension3=(*dimension3)[k];
				for (unsigned int o=0; o<structure->size(); o++){
					cstructure=o;
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
								generateMatrix(cdimension1,cdimension2,cdimension3,cdensity,cstructure);
								launchTest(output,cp);
								}
							}
						}
					}
				}
			}
		}
	}

} /* namespace std */
