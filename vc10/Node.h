#pragma once
#include "Shape.h"

class Node{
	public:
		Node();
		Node(Shape*);
		bool isEmpty();
		void insertAfter(Node*);
		void remove(Node*);
		void deleteNode(Node*);
		void draw();
		void drawList();

		Node* getEnd();
		void popOn(Node*);
		void popOff(Node*);
		void drawList(int,int);

		Node* cur;
		Shape* shape_;
		Node* next_;
		Node* prev_;
		bool isSentinal;
};