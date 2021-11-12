#include <OpenGP/GL/Application.h>
#include "OpenGP/GL/Eigen.h"
#include "loadTexture.h"

using namespace OpenGP;
const int width=1280, height=720;

const char* terrain_vshader =
#include "terrain_vshader.glsl"
;
const char* terrain_fshader =
#include "terrain_fshader.glsl"
;

void init();
void genTerrainMesh();
void drawTerrain();

std::unique_ptr<Shader> terrainShader;
std::unique_ptr<GPUMesh> terrainMesh;
std::unique_ptr<RGBA8Texture> heightTexture;

int main(int, char**){

    Application app;

    init();
    genTerrainMesh();

    // Display callback
    Window& window = app.create_window([&](Window&){
        glViewport(0,0,width,height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawTerrain();
    });
    window.set_title("Terrain Demo");
    window.set_size(width, height);

    return app.run();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, /*solid*/1.0 );

    loadTexture(heightTexture, "perlin.png");

    ///--- Compile shaders
    terrainShader = std::unique_ptr<Shader>(new Shader());
    terrainShader->verbose = true;
    terrainShader->add_vshader_from_source(terrain_vshader);
    terrainShader->add_fshader_from_source(terrain_fshader);
    terrainShader->link();
}

//Task1: Grid Mesh Generation

void genTerrainMesh() {
    /// NOTE: For assignment 2 you cannot use this method to generate the mesh, you'll have to use GL_TRIANGLE_STRIPS
    /// Create a flat (z=0) mesh for the terrain with given dimensions
    terrainMesh = std::unique_ptr<GPUMesh>(new GPUMesh());
    int n_width = 32; // Grid resolution
    int n_height = 32;

    std::vector<Vec3> points;
    std::vector<unsigned int> indices;
    std::vector<Vec2> texCoords;

    ///TODO--- Vertex positions
    

    ///TODO--- Element indices using GL_TRIANGLE
    

    terrainMesh->set_vbo<Vec3>("vposition", points);
    terrainMesh->set_vbo<Vec2>("vtexcoord", texCoords);
    terrainMesh->set_triangles(indices);
}

void drawTerrain() {
    terrainShader->bind();

    /// Create transformation matrices, use lookAt and perspective
    Mat4x4 M = Mat4x4::Identity(); // Identity should be fine
    terrainShader->set_uniform("M", M);

    Mat4x4 V = lookAt(Vec3(0.5,0,1.0), Vec3(0.5,0.5,0), Vec3(0,1,0));
    terrainShader->set_uniform("V", V);

    Mat4x4 P = perspective(70.0f, width / (float)height, 0.01f, 10.0f);
    terrainShader->set_uniform("P", P);

    glActiveTexture(GL_TEXTURE0);
    heightTexture->bind();
    terrainShader->set_uniform("noiseTex", 0);

    // Draw terrain using triangle strips
    glEnable(GL_DEPTH_TEST);
    terrainMesh->set_attributes(*terrainShader);
    //terrainMesh->set_mode(GL_TRIANGLE_STRIP); //Use this option for Task 4 
 
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE); //Comment for Task 4
	
    terrainMesh->set_attributes(*terrainShader);
    terrainMesh->draw();

    terrainShader->unbind();
}
