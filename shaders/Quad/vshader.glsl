#version 330 core
in vec3 vpoint;
in vec2 vtexcoord;

out vec2 uv;

//TODO 3: Define Scaling and Rotate functions




uniform float time;

void main() {
	//TODO4: Use the transformation functions to move the quad geometry. Modify the following statement.
	gl_Position = vec4(vpoint, 1.0);	
	uv = vtexcoord;  

}
