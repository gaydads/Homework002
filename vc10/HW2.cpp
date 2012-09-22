#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Shape.h"
#include "Circle.h"
#include "Resources.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Node.h"



using namespace ci;
using namespace ci::app;
using namespace std;

class HW2 : public AppBasic {
public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings*);

private:
	  Shape* circles;
	  Shape* circle;
	  Node* linked_list;
	  Node* node;

	  int mouse_click;
	  static const int surfaceSize_ = 1028;
	  static const int appHeight_ = 600;
	  static const int appWidth_ = 800;
};

void HW2::prepareSettings(Settings* settings) {
	settings->setWindowSize(appWidth_,appHeight_);
	settings->setResizable(false);
}

void  HW2::setup()
{
	linked_list = new Node();
	node = new Node();
	node->shape_->x_=50;
	node->shape_->y_=50;
	node->insertAfter(linked_list);
	//linked_list->next_=node;

	///////////linked_list = new Node();
	/////////////circle = new Shape();
	//Circle* cir = new Circle(50, 50);

	//Shape* tri = cir;

	//Node* triangle = new Node();
	//Shape* shapes = new Shape();
	//Shape* circle = tri;
	
	//triangle->shape_ = shapes;

	//circles = new Shape();
	//sentinal = new Node();

	//circles->circle(50,50);
	//Node* cir = new Node(circles);
	//cir->insertAfter(sentinal);
}

void  HW2::mouseDown( MouseEvent event ) {

	Node* shape = new Node();

	if (event.isLeftDown()) {
		shape->shape_= new Shape();
		shape->shape_->x_=event.getX();
		shape->shape_->y_=event.getY();
		linked_list->popOn(shape);
	}
	if (event.isRightDown()) {
		linked_list->popOff(linked_list->getEnd());
	}

	//node->shape_->x_=50;
	//node->shape_->y_=50;
	//node->insertAfter(linked_list);


	/*if(event.isLeftDown()) {
		circle->x_ = event.getX();
		circle->y_ = event.getY();
	}*/

	//linked_list->insertAfter(new Node(circle));

	/*mouse_click = 1;

	circle->circle(event.getX(),event.getY());
	node = new Node(circle);

	if(event.isLeftDown()) {
		linked_list->insertAfter(node);
		linked_list->drawList(event.getX(),event.getY());
	}*/

	/*Shape* shape_ = new Shape();

	if(event.isLeftDown()) {
		shape_->circle(event.getX(),event.getY());
	}

	linked_list->popOn(new Node(shape_));
	*/



}

void  HW2::update()
{
	//circle->x_=50;
	//circle->y_=50;
	//linked_list->insertAfter(new Node(circle));
}

void  HW2::draw()
{
	
	//node->shape_->circle();
	

	//gl::drawSolidCircle( Vec2f( 15.0f, 25.0f ), 50.0f );
	// clear out the window with red
	gl::clear( Color( 1.0, 0, 0 ) );
	//node->draw();
	//linked_list->next_->draw();
	linked_list->drawList();
	//linked_list->drawList();

	/*if (mouse_click == 1) {
		circle->circle(40,40);
	//node = new Node(circle);
	}*/



	//linked_list->drawList();
	//circles->circle(50,50);
	//Circle(300,300);
}

CINDER_APP_BASIC(  HW2, RendererGl )
