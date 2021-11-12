R"(
#version 330 core
uniform sampler2D noiseTex;

in vec3 vposition;
in vec2 vtexcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 uv;
out vec3 fragPos;


void main() {
    uv = vtexcoord;
    float h=0.0f; 
	
    // Task 2: Calculate vertical displacement h given uv      
    //h = _________;
    
    h*=0.5; //scale the height
   
    //Task 3: displace the vertex position by translating it h units along z
    //fragPos = ____________;

    // Set gl_Position
    gl_Position = P*V*M*vec4(fragPos, 1.0f);

}
)"
