#include<vector>
#include "Helpers/Quad.h"


const int SUN_ROT_PERIOD = 30;        
const int EARTH_ROT_PERIOD = 4;       
const int MOON_ROT_PERIOD = 8;       
const int EARTH_ORBITAL_PERIOD = 10; 
const int MOON_ORBITAL_PERIOD = 5;   
const int SPEED_FACTOR = 1;
    
Quad sun;
Quad earth;
Quad moon;

void init();

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    float time_s = glfwGetTime();

    //TODO: Set up the transform hierarchies for the three objects!
    float freq = M_PI*time_s*SPEED_FACTOR;

    // **** Sun transform
    

    // **** Earth transform
    

    // **** Moon transform
    

    // draw the sun, the earth and the moon
    
}

int main(int, char**){
    GLFWwindow* window;
    glewExperimental = true; // for core profile

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context

    window = glfwCreateWindow(1200, 1200, "Planets", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    init();

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    do {
        // Clear the screen. 
        glClear(GL_COLOR_BUFFER_BIT);
        
        display();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0); // Check if the ESC key was pressed or the window was closed

   
    return EXIT_SUCCESS;
}

void init(){
    glClearColor(1.0f,1.0f,1.0f, 1.0 );

    // Enable alpha blending so texture backgroudns remain transparent
    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sun.init();
    earth.init();
    moon.init();

    std::vector<Vec3> quadVert;
    quadVert.push_back(Vec3(-1.0f, -1.0f, 0.0f));
    quadVert.push_back(Vec3(1.0f, -1.0f, 0.0f));
    quadVert.push_back(Vec3(1.0f, 1.0f, 0.0f));
    quadVert.push_back(Vec3(-1.0f, 1.0f, 0.0f));
    std::vector<unsigned> quadInd;
    quadInd.push_back(0);
    quadInd.push_back(1);
    quadInd.push_back(2);
    quadInd.push_back(0);
    quadInd.push_back(2);
    quadInd.push_back(3);
    sun.loadVertices(quadVert, quadInd);
    earth.loadVertices(quadVert, quadInd);
    moon.loadVertices(quadVert, quadInd);

    std::vector<Vec2> quadTCoord;
    quadTCoord.push_back(Vec2(0.0f, 0.0f));
    quadTCoord.push_back(Vec2(1.0f, 0.0f));
    quadTCoord.push_back(Vec2(1.0f, 1.0f));
    quadTCoord.push_back(Vec2(0.0f, 1.0f));
    sun.loadTexCoords(quadTCoord);
    earth.loadTexCoords(quadTCoord);
    moon.loadTexCoords(quadTCoord);

    sun.loadTextures("sun.png");
    moon.loadTextures("moon.png");
    earth.loadTextures("earth.png");
}
