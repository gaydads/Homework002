#include "Node.h"

/**
*Node constructor
*/


Node::Node() {
	next_ = this;
	prev_ = this;
	shape_ = new Shape();
	isSentinal = true;
}

Node::Node(Shape* shape) {
	this->shape_ = shape;
	next_ = this;
	prev_ = this;
	isSentinal = false;
}

bool Node::isEmpty() {
	if (this->next_ == this)
		return true;
	
	return false;
}

void Node::insertAfter(Node* where_at) {
	Node* our_node_pointer = new Node;
	our_node_pointer->shape_ = this->shape_;
	our_node_pointer->next_ = where_at->next_;
	our_node_pointer->prev_ = where_at;
	where_at->next_ = our_node_pointer;
}


void Node::remove(Node*){
	prev_->next_ = next_;
	next_->prev_ = prev_;
	next_ = this;
	prev_ = this;
}

void Node::deleteNode(Node* node) {
	delete(node);
}
		
Node* Node::getEnd() {
	cur = new Node();
	cur = next_;

	while(cur != this) {
		cur = cur->next_;
	}
	return cur->prev_;
}
void Node::popOn(Node* node){ 
	node->prev_=this->getEnd();
	node->next_=this->getEnd()->next_;
	this->getEnd()->next_ = node;

	/*next_= node;
	node->prev_=this;
	node->next_=next_;*/

}



///FIX THIS!!!
void Node::popOff(Node* end) {
	//set list end's previous's next to end's next
	this->getEnd()->prev_->next_=this->getEnd()->next_;
	//set list end's next's previous to end's previous
	this->getEnd()->prev_->next_=this->getEnd()->prev_;
	//delete end/// BUT IT DELETES EVERYTHING???
	//delete(end);
}

void Node::draw() {
	shape_->circle();
}

void Node::drawList() {
	cur = new Node();
	cur = next_;

	while(cur != this) {
		cur->draw();
		cur = cur->next_;
	}
}