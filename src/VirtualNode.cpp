/*
 * VirtualNode.cpp
 *
 *  Created on: 12 oct. 2014
 *      Author: dosimont
 */

#include "VirtualNode.h"

namespace std {

VirtualNode::VirtualNode(): id(0), value(0), father(0), children(vector<VirtualNode*>()){
}

const vector<VirtualNode*>& VirtualNode::getChildren() const {
	return children;
}

void VirtualNode::setChildren(const vector<VirtualNode*>& children) {
	this->children = children;
}

VirtualNode* VirtualNode::getFather() {
	return father;
}

void VirtualNode::setFather(VirtualNode* father) {
	this->father = father;
}

int VirtualNode::getId() const {
	return id;
}

void VirtualNode::setId(int id) {
	this->id = id;
}

VirtualNode::VirtualNode(int id, VirtualNode* father): id(id), value(0), children(vector<VirtualNode*>()) {
	if (father!=0){
		father->addChild(this);
	}else{
		this->father=0;
	}
}

VirtualNode::~VirtualNode() {
	for (unsigned int i=0; i<children.size(); i++){
		delete children[i];
	}
	children.clear();
}

void VirtualNode::addChild(VirtualNode* child) {
	children.push_back(child);
	child->setFather(this);
}

bool VirtualNode::hasChild() {
	return (children.size()!=0);
}

} /* namespace std */
