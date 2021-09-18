#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "Image.h"

//Data types
typedef float Scalar;
typedef Eigen::Matrix<Scalar, 3, 1> Vec3;
typedef Eigen::Matrix<Scalar, 2, 1> Vec2;
typedef	unsigned char uchar;

//Color functions
using Colour = cv::Vec3b; // RGB Value
Colour red() { return Colour(255, 0, 0); }
Colour green() { return Colour(0, 255,0); }
Colour blue() { return Colour(0, 0, 255); }
Colour white() { return Colour(255, 255, 255); }
Colour black() { return Colour(0, 0, 0); }


//bounding the channel wise pixel color between 0 to 255
uchar Clamp(int color)
{
    if (color < 0) return 0;
    if (color >= 255) return 255;
    return color;
}



int main(int, char**){
	
	//Create an image object with 500 x 500 resolution.
    Image image = Image(500, 500);
	
	//Coordinates of image rectangle
	Vec3 llc = Vec3(-1, -1, -1);
	Vec3 urc = Vec3(1, 1, -1);
    int width = urc(0) - llc(0);
    int height = urc(1) - llc(1);
    Vec2 pixelUV = Vec2((float)width / image.cols, (float)height / image.rows);
	
	/// TODO: define camera position (view point), sphere center, sphere radius (Weightage: 5%)
    // example: Vec3 SpherePos = Vec3(0, 0, -5);

  
  
	
	///TODO: define lighting source, ambient and diffuse colors (Weightage: 5%)
	//example: Vec3 LightSource = (2.0, 3.0, 0.0);
   
   

    Vec3 Origin = CameraPoint;
    //end

    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
			///TODO: Build primary rays (Weightage: 10%). 
			//Find the pixel position (PixelPos) for each row and col and then construct the vector PixelPos-Origin
           

            ///TODO: Ray-sphere intersection...(refer to the lecture slides and Section 4.4.1 of the textbook) (Weightage: 30%)
           
			
			//compute the discriminant
            
			
			
			//if the discriminant is greater than zero
			if(discriminant > 0){
            
			
				//find roots t1 and t2
                
				
                //determine which one is the real intersection point
                

                if (t > 0){
                    ///TODO: Basic shading (Weightage: 20%)
					//Shade the pixel, normal is Intersection - SphereCenter, LightVector is LightSource- Intersection, make sure to normalize the vectors
                    
                    float diffuseTerm = LightVector.dot(Normal);
                    if (diffuseTerm < 0) diffuseTerm = 0;

                    Colour colour(0, 0, 0); //The ambient base
                    colour[0] = Clamp( ambient[0] + diffuse[0] * diffuseTerm );
                    colour[1] = Clamp( ambient[1] + diffuse[1] * diffuseTerm );
                    colour[2] = Clamp( ambient[2] + diffuse[2] * diffuseTerm );
                    image(row, col) = colour;
                } else {
                    image(row, col) = black();
                }
			
            } else {
                //No intersection, discriminant < 0
                image(row, col) = white();
            }

       }
    }
    ///Program compiles, runs and outputs the correct results (Weightage: 30%) 
    ///	Required outputs: (1) Ray traced image of a sphere (2) Ray traced image when the camera is placed inside the sphere (complete black)
    image.save("./result.png");
    image.display();

    return EXIT_SUCCESS;
}

