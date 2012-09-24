#include "LinkedList.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"
#include "Resources.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Surface.h"
#include "cinder/Cinder.h"
#include "cinder/Font.h"
#include <vector>
#include <math.h>

/*Another difficult assignment that took many hours of doing, and re-doing; researching and failing!

  All in all I gained a lot more knowledge of how pointers work and how I can use them to make a fluent
  linked list. I think if I were to redo this assignment I would try to figure out if I could store different 
  objects in each of the list's variable members. I feel like it would be easier to pass in an object rather than
  call a different draw method for each time you are looping through the linked list.
*/

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPicturePart2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings (Settings* settings);
	void keyDown(KeyEvent event);
	void text();

  private:

	Surface* mySurface_;
	Surface baby_picture;
	gl::Texture help_display;
	Font font;
	LinkedList List;
	bool show_help;

	float red, green, blue;
	///These signs will change the direction of the color change (+/-)
	int redSign, greenSign, blueSign;

	//Going to use this to change my circle colors
	struct circle_colors{
		int r;
		int g;
		int b;
	};

	//Made for smoother color changes
	struct circle_signs{
		int redSign;
		int greenSign;
		int blueSign;
	};


	//Screen dimensions
	static const int kAppWidth= 800;
	static const int kAppHeight= 600;
	static const int kTextureSize= 1024;
	//Filling a rectangle that will change colors
	void drawRectangles(uint8_t* pixels, int x1, int y1, int x2, int y2, int red, int green, int blue);
	void drawBackground(uint8_t* pixels);
	void drawCircles(uint8_t* pixels, int center_x, int center_y, int radius, int red, int green, int blue);
};

void CatPicturePart2App::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(true);
}

void CatPicturePart2App::setup()
{
	help_display = loadImage( "Instructions.png" );

	//Set the initial values of the colors and color sign values
	red = 250;
	green = 50;
	blue = 175;
	redSign = 1;
	greenSign = 1;
	blueSign = 1;

	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	//My Textbox won't work :( I keep getting WHITE SCREENED!!
	//font = Font("Times New Roman", 24);
	for (int i = 0; i < 5; i++){
		List.addNode(i);
	}
	show_help = true;
}

void CatPicturePart2App::text()
{

	/*SOO I tried implementing the Textbox, but had to suffer through the white screen problem and not have my .cpp file render anything besides
	a purely white page..so I had to make a picture with the instructions on them instead and relearn how to bring in a picture..
	*/


	//Textbox help credited to AJDUBERSTEIN
	/*string txt = "Welcome!\n\n Keybindings: \n 'n'      Moves shapes up \n 'r'     Reverses shape order \n	'?'		Toggles help on/off";
	TextBox tbox = TextBox().alignment( TextBox::CENTER ).font(font).size( Vec2i( 512, 512) ).text( txt );
	tbox.setColor( Color( 1.0f, 0.65f, 0.35f ) );
	tbox.setBackgroundColor( ColorA( 0.5, 0, 0, 1 ) );
	help_display = gl::Texture( tbox.render() );
	*/

}


void CatPicturePart2App::drawBackground(uint8_t* pixels)
{

	///Green Background
	for (int i = 0; i < 3*kTextureSize*kTextureSize; i+= 3){
			pixels[i] = red;
			pixels[i+1] = green;
			pixels[i+2] = blue;
	}
}

void CatPicturePart2App::drawRectangles(uint8_t* pixels, int x1, int y1, int x2, int y2, int red, int green, int blue)
{

	circle_colors t;
	t.r = red;
	t.g = green;
	t.b = blue;


	//--------------------------------------------------
	//Copied from Homework01
	//If x1 is less than x2, take x1, else take x2
	int startx = (x1 < x2) ? x1 : x2;
	int endx = (x1 < x2) ? x2 : x1;
	//Same thing for the y values
	int starty = (y1 < y2) ? y1 : y2;
	int endy = (y1 < y2) ? y2 : y1;
	//--------------------------------------------------

	
	//checking the boundaries
	if(endx < 0) return; 
	if(endy < 0) return; 
	if(startx >= kAppWidth) return;
	if(starty >= kAppHeight) return;
	//Making sure the rectangle drawn isn't outside the viewing box
	if(endx >= kAppWidth) endx = kAppWidth-1;
	if(endy >= kAppHeight) endy = kAppHeight-1;
	
	//making the rectangle
	for ( int y=starty; y <= endy; y++){
		for ( int x = startx; x <= endx; x++) {
			//Set the Red, Green, Blue values for each pixel
				pixels [3* (x+y*kTextureSize)]= t.r;			
				pixels [3* (x+y*kTextureSize)+1]= t.g;			
				pixels [3* (x+y*kTextureSize)+2]= t.b;			
		}		
	}
}

void CatPicturePart2App::drawCircles(uint8_t* pixels, int centerX, int centerY, int radius, int red, int green, int blue)
{
	circle_colors t;
	t.r = red;
	t.g = green;
	t.b = blue;

	//Taken from Dr. Brinkmans Circle Funtion, except for the modulus portion of it

	for ( int y=centerY-radius; y <= centerY+radius; y++){		
		for ( int x = centerX-radius; x <= centerX+radius; x++) {	
			int dist = (int)sqrt((double)((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY)));
			if (dist <= radius) {
				//I'm using the values I have stored above to be able to change the circle's color
				pixels[3*(x + y*kTextureSize)] = t.r;
				pixels[(3*(x + y*kTextureSize))+1] = t.g;
				pixels[(3*(x + y*kTextureSize))+2] = t.b;
			}
		}
	}
}

void CatPicturePart2App::mouseDown( MouseEvent event )
{

	//Click to change the colors!

	//Beware not to click to quickly or the screen will turn black and white!
	if (red < 100) red = red *2;
	else red = red / 2;
	if (green < 100) green = green *2;
	else green = green / 2;
	if (blue < 100) blue = blue *2;
	else blue = blue / 2;
}

void CatPicturePart2App::keyDown(KeyEvent event)
{
	if (event.getChar() == '?'){
		show_help = !(show_help);
	}
	else if (event.getChar() == 'n'){
		List.next_in_list();
	}
	else if (event.getChar() == 'r'){
		List.reverse_list();
	}
	else{
	}
}

void CatPicturePart2App::update()
{
	
	///So I made the colors bounce between the values of 0 - 255
	if (red >= 255 || red <= 0) {
		redSign = redSign*-1;
	}
	if (green >= 255 || green <= 0) {
		greenSign = greenSign*-1;
	}
	if (blue >= 255 || blue <= 0) {
		blueSign = blueSign*-1;
	}

	///Regardless of whether *_Sign is (+/-) we will add it to the current values
	red = red + (redSign);
	green = green + (greenSign);
	blue = blue + (blueSign);
}

void CatPicturePart2App::draw()
{
	//Clear the surface
	gl::clear(Color(0, 0, 0));

	gl::draw(*mySurface_); 

	//Gather the info we need in an array
	uint8_t* dataArray = (*mySurface_).getData();
	drawBackground(dataArray);
	int node;

	//Same idea as with AJDUBERSTEIN's TheRoyalSociety
	for (int i = 0; i < 5; i++) {
		node = List.at(i) ->data;
		if (node == 0) {
			drawCircles(dataArray, 415, 300, 200, blue, blue*2, green);
			//I think it looks cool when the "character" has eyes, he looks dizzy!
			//...probably from all of the color changes!!
			//__________________eyes_____________________________
			drawCircles(dataArray, 380, 200, 35, 0, 0, 0);
			drawCircles(dataArray, 480, 200, 35, 0, 0, 0);
			drawCircles(dataArray, 370, 190, 15, 255, 255, 255);
			drawCircles(dataArray, 490, 210, 15, 255, 255, 255);
			//____________________^pupils^_____________________________
		}
		else if(node == 1){
			drawCircles(dataArray, 350, 350, 70, blue/2, green, red);
		}
		else if(node == 2){
			drawRectangles(dataArray, 350, 350, 400, 400, red, green, red);
		}
		else if(node == 3) {
			drawRectangles(dataArray, 420, 350, 470, 400, green/2, blue, red);
		}
		else if(node == 4) {
			drawCircles(dataArray, 410, 375, 25, green, red*2, red); 
		}
		else{
			break;
		}
	}
	if (show_help == true){
		gl::draw(help_display);
	}
}

CINDER_APP_BASIC( CatPicturePart2App, RendererGl )
