/*
 * VirtualNode.h
 *
 *  Created on: 12 oct. 2014
 *      Author: dosimont
 */

#ifndef VIRTUALNODE_H_
#define VIRTUALNODE_H_

#include<vector>

namespace std {

class VirtualNode {
	private:
		int id;
		int value;
		VirtualNode* father;
		vector<VirtualNode*> children;

	public:
		VirtualNode();
		VirtualNode(int, VirtualNode* father);
		virtual ~VirtualNode();
		const vector<VirtualNode*>& getChildren() const;
		void setChildren(const vector<VirtualNode*>& children);
		VirtualNode* getFather() ;
		void setFather(VirtualNode* father);
		int getId() const;
		void setId(int id);
		int getValue() const;
		void setValue(int value);
		void addChild(VirtualNode* child);
		bool hasChild();
};

} /* namespace std */

#endif /* VIRTUALNODE_H_ */
