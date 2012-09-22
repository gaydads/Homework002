#include "Shape.h"
#include "Circle.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Shape::Shape() {
	x_=0;
	y_=0;

}

void Shape::circle() {
	gl::drawSolidCircle( Vec2f(x_,y_), 50.0f, 3);
}