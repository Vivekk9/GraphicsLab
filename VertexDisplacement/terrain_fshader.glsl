R"(
#version 330 core
out vec4 color;

uniform sampler2D noiseTex;

in vec2 uv;
in vec3 fragPos;

void main() {
    //light position
    vec3 lightPos = vec3(0.5f,0.5f,0.3f);
    vec3 viewPos=vec3(0.5f,0.0f,1.0f);

    // TODO: Texture size in pixels
    //ivec2 size = ________;

    // TODO: Calculate surface normal N
    vec3 A = vec3(uv.x + 1.0f / size.x, uv.y, textureOffset(noiseTex, uv, ivec2(1, 0)));
    //vec3 B = _______;
    //vec3 C = _______;
    //vec3 D = _______;
    //vec3 normal = normalize( __________ );
	
	// Calculate ambient lighting factor
    float ambient = 0.05f;
    float diffuse_coefficient = 0.2f;
    float specular_coefficient = 0.2f;
    float specularPower = 16.0;

    // Calculate diffuse lighting factor
    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuse = diffuse_coefficient * max(0.0f, -dot(normal, lightDir));

    // Calculate specular lighting factor
    vec3 view_direction = normalize(viewPos - fragPos);
    vec3 halfway = normalize(lightDir + view_direction);
    float specular = specular_coefficient * max(0.0f, pow(dot(normal, halfway), specularPower));
	
    vec4 col = vec4(0,0.5,0.1,1);    
    col += (ambient + diffuse + specular);  

    color = vec4(col);
    
}
)"
