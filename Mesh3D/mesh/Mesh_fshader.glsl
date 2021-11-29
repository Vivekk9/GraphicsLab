#version 330 core
uniform float time;
uniform sampler2D water;
uniform sampler2D sand;
uniform sampler2D grass;


out vec4 color;
in vec3 fpoint;
in vec3 fnormal_cam;


vec3 O = vec3(0.82,0.68,0.21); //gold color


void main() { 
   //Height levels of bunny
   float neck_level = 0.0;
   float hip_level =  -0.25;
   
   //TODO1: Spherical mapping: find out _phi and _theta
   
   //float u = ______________;
   //float v = ______________;  
   
   
   //TODO2: Heightwise texturing and blending of textures
   /*if (fpoint.y > neck_level){   
        color = _____________________;   
   } else if((fpoint.y > hip_level) && (fpoint.y < neck_level)){
        float halfDistance = ___________________;
		if (fpoint.y < (hip_level + halfDistance)) {

                // Blend with water
                float pos = __________________________;
                float posScaled = _____________________;
                color = (texture(sand, vec2(u,v)) * (posScaled))+(texture(water, vec2(u,v)) * (1 - posScaled));
            } else {

                // Blend with grass
                float pos = ______________________;
                float posScaled = ________________;
                color = ________________________________________;
            }
            
   } else if(fpoint.y < hip_level){
        color = ____________________;  
   }*/

    color = vec4(O,1);
    
    /// Lambertian shading
    vec3 N = normalize(fnormal_cam);
    vec3 L = vec3(0,0,-1); ///< fixed light pos    
    float lamb = dot(N,L);
    color = color * max(lamb, 0);


    /// Specular shading
    if(lamb>0){
        vec3 V = vec3(0,0,-1); 
        vec3 R = reflect(V,N);
        float glossy = pow( max(dot(-R,L),0), 100 );
        color += vec4(vec3(.5)*glossy,0);
    }

    
    
}
