/*
 * DLPBench.h
 *
 *  Created on: 10 oct. 2014
 *      Author: dosimont
 */

#ifndef SRC_DLPBENCH_H_
#define SRC_DLPBENCH_H_

#include "OLPBench.h"
#ifdef OPENMP
#include <openmplpaggreg/DLPAggregWrapper.h>
#else
#include <benchlpaggreg/DLPAggregWrapper.h>
#endif
#include "VirtualNode.h"

namespace std {

class DLPBench: public OLPBench {
		vector<int> * structure;
		DLPAggregWrapper * dlp;
	public:
		DLPBench();
		virtual ~DLPBench();
		void addStructure(vector<string> tab);
		void generateMatrix(int i, int j, int k, double density, int structure, ostream *output);
		void launchTest(ostream *output, double p);
		void launchBench(ostream *output);
};

void printSpaceHeader(ostream *output);

} /* namespace std */

#endif /* SRC_DLPBENCH_H_ */
