#include "Perlin.h"


Perlin::Perlin(int w, int h) {
	width = w;
	height = h;
		
}

/// TODO1: Implement the linear interpolation (weightage-5%)

float Perlin::lerp(float x, float y, float t) {
	/// TODO: Implement linear interpolation between x and y
	 
	return 0; //to be changed
}


/// TODO2: Implement the fade function (try both cubic as well as quintic polynomials and generatee the corresponding noise textures) (weightage-5%)

float Perlin::fade(float t) {
	/// TODO: Implement the quintic function (optimized)      
	return 0;//to be changed	
}

//function returns one of the eight gradients
Vec2 Gradient(int index) {
	//index is the value from the permutation table
	int h = index & 7;
	if (h == 0)
		return  Vec2(1.0, 1.0);
	else if (h == 1)
		return  Vec2(-1.0, 1.0);
	else if (h == 2)
		return  Vec2(1.0, -1.0);
	else if (h == 3)
		return  Vec2(-1.0, -1.0);
	else if (h == 4)
		return Vec2(0.707, 0.707);
	else if (h == 5)
		return Vec2(-0.707, 0.707);
	else if (h == 6)
		return Vec2(0.707, -0.707);
	else
		return Vec2(-0.707, -0.707);
}

//TODO3: Complete the following noise generation function. THe function takes three coordinates of the sample point and retirns the noise vlaue at that point. 
//Since this is 2D Noise, we keep z=0 for all the points and use x and y coordinates to generate the noise value.

float Perlin::noise(float xCoord, float yCoord, float zCoord) {	

	// TODO: Unit cube vertex coordinates surrounding the sample point. In this example find the unit square vertex coordinates in X and Y coords. (Weightage-10%)
	

	// Determine sample point position within unit cube (unit square in our case) (Weightage-10%)
	

	//Construct distance vectors from each corner to the sample point (Weightage-10%)	

	
	//Fetch the gradients at corners (Weightage-10%)

	//TODO: Get scalars at corners HINT: take the dot product of gradient and the distance vectors. (Weightage-10%)
	float dotX0Y0Z0, dotX0Y0Z1, dotX0Y1Z0, dotX0Y1Z1, dotX1Y0Z0, dotX1Y0Z1, dotX1Y1Z0, dotX1Y1Z1;
	

	//TODO: Interpolate along X (Weightage-5%)
	

	//TODO: Interpolate along Y (Weightage-5%)
	


	// Return the result
	return result;	
	
}
