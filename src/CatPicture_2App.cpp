#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPicture_2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings *settings);   //set size of window
	void drawHorizonalLine(uint8_t* pixels, int start, int end, int row);      //draw horizonal line
	void drawVerticalLine(uint8_t* pixels, int start, int end, int col);      //draw vertical line
	void drawRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color);      //draw rectangle
	void drawTriangle(uint8_t* pixels, int x1, int y1, int x2, int y2, int x3, int y3, Color8u color);       //draw triangle
	void drawCircle(uint8_t* pixels, float radius, float center_x, float center_y);    //draw circle
	void paintChimney(uint8_t* pixels, Color8u color);   //paint chimney
	void blur(uint8_t* pixels);   //do blur
	void tint(uint8_t* pixels, int row, int col);

  private:
	Surface* mySurface;  //The Surface object I modify array on
	Color8u colorRoof;
	Color8u colorWall;
	Color8u colorWindow;
	Color8u colorDoor;
	Color8u colorChimney;
	Color8u colorSky;
	float circle_x;
	float circle_y;
	int mouse_x;
	int mouse_y;
};

/*
* Possible thoughts:
*
* The row major order formula is used quite alot, maybe there
* could be a function with x and y inputs that performs this 
* operation, so you don't have to type it in every time.
*
* You switch slightly between variables x, y vs. row and col (as used in line drawing methods)
* Might be beneficial to make sure these stay constant.
*
* The blur effect adds alot to the picture. I like how it initially thickens the lines of the house.
* Also, it totally works for the chimney smoke! That looks awesome!!! Congrats!!!
* 
* I really enjoyed the animation and your picture.
* Good job on everything overall!
*
*------------------------------------------ David Gayda
*/



/* While using this tint method and the mousedown method, I was able to break your
* program by drawing a tint circle out of the upper bounds of your app screen.
* You can add error handling, or a statement in this method to handle it.
*/
//tint
void CatPicture_2App::tint(uint8_t* pixels, int row, int col) {

	//This while loop fixes the problem, and keeps the circles in bounds
	//Not sure why 30 works but no lower...
	while(col-30<0) {
		col++;
	}
		for (int x=row-50; x<row+50; x++) {
			for (int y=col-50; y<col+50; y++) {
				if(((row-x)*(row-x)+(col-y)*(col-y))<=(30*30)){
					pixels[(int)(3*(x+(y*1024)))] = 255;
					pixels[(int)(3*(x+(y*1024)))+1] = 255;
					pixels[(int)(3*(x+(y*1024)))+2] = 255;
				}
			}
		}

	}

/*This blur works, but the code looks slightly long and redundant. 
* There is probably a more compact way of doing this, if this had bugs,
* it'd probably be very tedious trying to change each pixel calculation.
*
* Also, your picture becomes darker and overtime, because the blur method is acting upon
* the unfilled surface. This can be avoided by filling your picture with a background.
* Though this would ruin how your smoke effect is performed, unless it is implemented differently.
*/

//do blur
void CatPicture_2App::blur(uint8_t* pixels){
	for(int x=0; x<=1024; x++){
		for(int y=0; y<=1024; y++){
			if(x > 0 && x < 1024 && y > 0 && y < 1023){
				pixels[3*(x+y*1024)] = (pixels[3*(x+y*1024)] + pixels[3*((x+1)+y*1024)] + pixels[3*((x-1)+y*1024)] + pixels[3*((x-1)+(y-1)*1024)] + pixels[3*(x+(y-1)*1024)] + pixels[3*((x+1)+(y-1)*1024)] + pixels[3*((x-1)+(y+1)*1024)] + pixels[3*(x+(y+1)*1024)] + pixels[3*((x+1)+(y+1)*1024)])/9;
				pixels[3*(x+y*1024)+1] = (pixels[3*(x+y*1024)+1] + pixels[3*((x+1)+y*1024)+2] + pixels[3*((x-1)+y*1024)+1] + pixels[3*((x-1)+(y-1)*1024)+1] + pixels[3*(x+(y-1)*1024)+1] + pixels[3*((x+1)+(y-1)*1024)+1] + pixels[3*((x-1)+(y+1)*1024)+1] + pixels[3*(x+(y+1)*1024)+1] + pixels[3*((x+1)+(y+1)*1024)]+1)/9;
				pixels[3*(x+y*1024)+2] = (pixels[3*(x+y*1024)+1] + pixels[3*((x+1)+y*1024)+2] + pixels[3*((x-1)+y*1024)+2] + pixels[3*((x-1)+(y-1)*1024)+2] + pixels[3*(x+(y-1)*1024)+2] + pixels[3*((x+1)+(y-1)*1024)+2] + pixels[3*((x-1)+(y+1)*1024)+2] + pixels[3*(x+(y+1)*1024)+2] + pixels[3*((x+1)+(y+1)*1024)]+2)/9;
			}

		}
	}
}

//Meet one of main goals: draw horizonal line
void CatPicture_2App::drawHorizonalLine(uint8_t* pixels, int start, int end, int row){
	int draw;
	for(draw = start; draw <= end; draw++){
		pixels[3*(draw + row*1024)] = 0;
		pixels[3*(draw + row*1024)+1] = 0;
		pixels[3*(draw + row*1024)+2] = 0;
	}
}

//The draw variable name may be slightly confusing.
//Possible suggestion would be to avoid verbs to name variables

//Meet one of main goals: draw vertical line
void CatPicture_2App::drawVerticalLine(uint8_t* pixels, int start, int end, int col){
	int draw;
	for(draw = start; draw <=end; draw++){
		pixels[3*(col + draw * 1024)] = 0;
		pixels[3*(col + draw * 1024)+1] = 0;
		pixels[3*(col + draw * 1024)+2] = 0;
	}
}

//Meet one of main goals: draw rectangle
void CatPicture_2App::drawRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color){
	
	int draw;

	//Very nice edge lines.
	//Though this could be incorporated within the other loop
	//that fills in the rectangle by using an if statement
	//
	//Other idea, would be to call your horizontal and vertical line
	//methods here to avoid redundant lines of code

	//draw horizonal edges
	for(draw = x1; draw <= x2; draw++){
		pixels[3*(draw + y1*1024)] = 0;
		pixels[3*(draw + y1*1024)+1] = 0;
		pixels[3*(draw + y1*1024)+2] = 0;

		pixels[3*(draw + y2*1024)] = 0;
		pixels[3*(draw + y2*1024)+1] = 0;
		pixels[3*(draw + y2*1024)+2] = 0;
	}

	//draw vertical edges
	for(draw = y1; draw <= y2; draw++){
		pixels[3*(x1 + draw * 1024)] = 0;
		pixels[3*(x1 + draw * 1024)+1] = 0;
		pixels[3*(x1 + draw * 1024)+2] = 0;

		pixels[3*(x2 + draw * 1024)] = 0;
		pixels[3*(x2 + draw * 1024)+1] = 0;
		pixels[3*(x2 + draw * 1024)+2] = 0;
	}

	for(int x=0; x<=1024; x++){
		for(int y=0; y<=1024; y++){
			if(x>x1 && x<x2 && y>y1 && y<y2){
				if(pixels[3*(x + y * 1024)] != 0 && pixels[3*(x + y * 1024)+1] != 0 && pixels[3*(x + y * 1024)+2] != 0){
					pixels[3*(x + y * 1024)] = color.r;
					pixels[3*(x + y * 1024)+1] = color.g;
					pixels[3*(x + y * 1024)+2] = color.b;
				}
			}
		}
	}
}

// Looks like you may want to implement a rectangle method, instead
// of creating a whole new way to draw a chimney.

//paint chimney
void CatPicture_2App::paintChimney(uint8_t* pixels, Color8u color){
	for(int x=0; x<=1024; x++){
		for(int y=0; y<=1024; y++){
			if(x > 101 && x < 149 && y > 220 && y < 300){
				pixels[3*(x + y * 1024)] = color.r;
				pixels[3*(x + y * 1024)+1] = color.g;
				pixels[3*(x + y * 1024)+2] = color.b;
			}
		}
	}
}

//I like how simple your strategy was to draw yourtriangle.
// You do have an unused parameter (color) that can be deleted.

//Meet one of main goals: draw triangle
void CatPicture_2App::drawTriangle(uint8_t* pixels, int x1, int y1, int x2, int y2, int x3, int y3, Color8u color){
	
	//This is a very easy way to draw 45 degree angle lines.
	//Good thinking!
	
	//draw the first edge
	int draw_x2 = x2;
	int draw_y2 = y2;
	while(draw_x2 <= x1 && draw_y2 >= y1){
		pixels[3*(draw_x2 + draw_y2 * 1024)] = 0;
		pixels[3*(draw_x2 + draw_y2 * 1024)+1] = 0;
		pixels[3*(draw_x2 + draw_y2 * 1024)+2] = 0;

		draw_x2++;
		draw_y2--;
	}

	//draw the second edge
	int draw_x3 = x3;
	int draw_y3 = y3;
	while(draw_x3 >= x1 && draw_y3 >= y1){
		pixels[3*(draw_x3 + draw_y3 * 1024)] = 0;
		pixels[3*(draw_x3 + draw_y3 * 1024)+1] = 0;
		pixels[3*(draw_x3 + draw_y3 * 1024)+2] = 0;

		draw_x3--;
		draw_y3--;
	}

	//draw the third edge
	int draw_x = x2;
	for(draw_x; draw_x <= x3; draw_x++){
		pixels[3*(draw_x + 350 * 1024)] = 0;
		pixels[3*(draw_x + 350 * 1024)+1] = 0;
		pixels[3*(draw_x + 350 * 1024)+2] = 0;
	}
	
	//I'm not sure why this section uses new ints, paint
	// looks like you can just keep using x1 and y1.
	int paint_x = x1;
	int paint_y = y1;
	for(paint_x; paint_x > x2; paint_x--){
		for(paint_y; paint_y < y2; paint_y++){
			pixels[3*(paint_x + paint_y * 1024)] = 0;
			pixels[3*(paint_x + paint_y * 1024)+1] = 0;
			pixels[3*(paint_x + paint_y * 1024)+2] = 0;
		}
	}

}

//Meet one of main goals: Draw circle
void CatPicture_2App::drawCircle(uint8_t* pixels, float radius, float center_x, float center_y){
	
	for(int y=0; y<=1024; y++){
		for(int x=0;x<=1024; x++){
			if ((pow(x-center_x,2) + (pow(y-center_y,2))) <= (pow(radius,2))){
				pixels[3*(x + y*1024)] = 255;
				pixels[3*(x + y*1024)+1] = 255;
				pixels[3*(x + y*1024)+2] = 255;
			}
		}
	}

}

void CatPicture_2App::setup()
{
	mySurface = new Surface(1024,1024,false);

	colorWall.r = 237;
	colorWall.g = 28;
	colorWall.b = 36;

	colorWindow.r = 153;
	colorWindow.g = 217;
	colorWindow.b = 234;

	colorDoor.r = 255;
	colorDoor.g = 242;
	colorDoor.b = 0;

	colorChimney.r = 163;
	colorChimney.g = 73;
	colorChimney.b = 164;

	colorRoof.r = 255;
	colorRoof.g = 127;
	colorRoof.b = 39;

	colorSky.r = 0;
	colorSky.g = 162;
	colorSky.b = 232;

	circle_x = 120;
	circle_y = 145;


}

/*This mouse interaction works well, but only on the non drawn surface area.
* This happens because your circle tint isn't being drawn through the draw update loop.
* A possible way to fix this, is to add some sort of link list that is updated when the mouse is clicked.
* That way you can check and update the list within the update draw loop. Allowing the circle to be displayed
* everywhere.
*/
//Meet one of stretch goals: mouse interaction
void CatPicture_2App::mouseDown( MouseEvent event )
{
	tint((*mySurface).getData(), event.getX(), event.getY());
}

void CatPicture_2App::update()
{
	//Surface 1
	uint8_t* dataArray = (*mySurface).getData();

	//draw lines of chimney
	drawVerticalLine(dataArray, 220, 300, 99);
	drawVerticalLine(dataArray, 220, 300, 100);
	drawVerticalLine(dataArray, 220, 300, 101);

	drawVerticalLine(dataArray, 220, 250, 149);
	drawVerticalLine(dataArray, 220, 250, 150);
	drawVerticalLine(dataArray, 220, 250, 151);

	//paint chimney
	paintChimney(dataArray, colorChimney);

	//draw rectangle of chimney
	drawRectangle(dataArray, 74, 179, 174, 219, colorChimney);
	drawRectangle(dataArray, 75, 180, 175, 220, colorChimney);
	drawRectangle(dataArray, 73, 178, 173, 218, colorChimney);

	//draw rectangle of house
	drawRectangle(dataArray, 110, 350, 400, 530, colorWall);
	drawRectangle(dataArray, 111, 351, 399, 529, colorWall);
	drawRectangle(dataArray, 112, 352, 398, 528, colorWall);

	//draw rectangle of window
	drawRectangle(dataArray, 150, 380, 230, 430, colorWindow);
	drawRectangle(dataArray, 151, 381, 229, 429, colorWindow);
	drawRectangle(dataArray, 152, 382, 231, 431, colorWindow);

	//draw lines of window
	drawHorizonalLine(dataArray, 150, 230, 404);
	drawHorizonalLine(dataArray, 150, 230, 405);
	drawHorizonalLine(dataArray, 150, 230, 406);

	drawVerticalLine(dataArray, 380, 430, 189);
	drawVerticalLine(dataArray, 380, 430, 190);
	drawVerticalLine(dataArray, 380, 430, 191);

	//draw rectangle of door
	drawRectangle(dataArray, 290, 417, 360, 530, colorDoor);
	drawRectangle(dataArray, 291, 418, 359, 530, colorDoor);
	drawRectangle(dataArray, 292, 419, 358, 530, colorDoor);

	//draw triangle of roof
	drawTriangle(dataArray, 255, 145, 50, 350, 460, 350, colorRoof);
	drawTriangle(dataArray, 255, 144, 50, 349, 460, 349, colorRoof);
	drawTriangle(dataArray, 255, 143, 50, 348, 460, 348, colorRoof);

	//draw circle of smoke
	drawCircle(dataArray, 20, circle_x, circle_y);

	//Meet one of stretch goals: Animation
	circle_y = 30*cos(circle_x/20)+130;
	circle_x += 2;
	if(circle_x > 1024)
		circle_x = 120;

	blur(dataArray);


}

void CatPicture_2App::draw()
{
	gl::draw(*mySurface);
}

// Set size of window.
void CatPicture_2App::prepareSettings(Settings *settings){
	settings -> setWindowSize(1024,1024);
}

CINDER_APP_BASIC( CatPicture_2App, RendererGl )
