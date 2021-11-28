#pragma once
#include "icg_common.h"
#include <OpenGP/GL/Application.h>
#include "OpenGP/external/LodePNG/lodepng.cpp"

using namespace OpenGP;

class Mesh {
protected:
	GLuint _vao; ///< vertex array object
	GLuint _pid; ///< GLSL shader program ID
	

	std::unique_ptr<RGBA8Texture> water_tex;
	std::unique_ptr<RGBA8Texture> sand_tex;
	std::unique_ptr<RGBA8Texture> grass_tex;

	OpenGP::SurfaceMesh mesh;
	GLuint _vpoint;    ///< memory buffer
	GLuint _vnormal;   ///< memory buffer

public:
	void init() {
		
		const std::string& filename = "mesh/bunny.obj";
		//const std::string& filename = "mesh/armadillo.obj"; ///You may try the experiment with armadillo; increase the FOV in vshader.

		
		bool success = mesh.read(filename.c_str());
		assert(success);
		mesh.triangulate();
		mesh.update_vertex_normals();
		printf("Loaded mesh '%s' (#V=%d, #F=%d)\n", filename.c_str(), mesh.n_vertices(), mesh.n_faces());

		///--- Vertex one vertex Array
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		

		///--- Vertex Buffer
		SurfaceMesh::Vertex_property<Point> vpoints = mesh.get_vertex_property<Point>("v:point");
		glGenBuffers(1, &_vpoint);
		glBindBuffer(GL_ARRAY_BUFFER, _vpoint);
		glBufferData(GL_ARRAY_BUFFER, mesh.n_vertices() * sizeof(vec3), vpoints.data(), GL_STATIC_DRAW);
		

		///--- Normal Buffer
		SurfaceMesh::Vertex_property<Normal> vnormals = mesh.get_vertex_property<Normal>("v:normal");
		glGenBuffers(1, &_vnormal);
		glBindBuffer(GL_ARRAY_BUFFER, _vnormal);
		glBufferData(GL_ARRAY_BUFFER, mesh.n_vertices() * sizeof(vec3), vnormals.data(), GL_STATIC_DRAW);
		

		///--- Index Buffer
		std::vector<unsigned int> indices;
		for (SurfaceMesh::Face_iterator fit = mesh.faces_begin(); fit != mesh.faces_end(); ++fit) {
			unsigned int n = mesh.valence(*fit);
			SurfaceMesh::Vertex_around_face_circulator vit = mesh.vertices(*fit);
			for (unsigned int v = 0; v < n; ++v) {
				indices.push_back((*vit).idx());
				++vit;
			}
		}

		GLuint _vbo_indices;
		glGenBuffers(1, &_vbo_indices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		

		///--- Compile the shaders
		_pid = OpenGP::load_shaders("mesh/Mesh_vshader.glsl", "mesh/Mesh_fshader.glsl");
		if (!_pid) exit(EXIT_FAILURE);
		glUseProgram(_pid);



		///--- Load textures
		this->loadTexture(water_tex, "mesh/water.png");
		water_tex->bind();
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		this->loadTexture(sand_tex, "mesh/sand.png");
		sand_tex->bind();
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		this->loadTexture(grass_tex, "mesh/grass.png");
		grass_tex->bind();
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void loadTexture(std::unique_ptr<RGBA8Texture>& texture, const char* filename) {
		// Used snippet from https://raw.githubusercontent.com/lvandeve/lodepng/master/examples/example_decode.cpp
		std::vector<unsigned char> image; //the raw pixels
		unsigned width, height;
		//decode
		unsigned error = lodepng::decode(image, width, height, filename);
		//if there's an error, display it
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...

		// unfortunately they are upside down...lets fix that
		unsigned char* row = new unsigned char[4 * width];
		for (int i = 0; i < int(height) / 2; ++i) {
			memcpy(row, &image[4 * i * width], 4 * width * sizeof(unsigned char));
			memcpy(&image[4 * i * width], &image[image.size() - 4 * (i + 1) * width], 4 * width * sizeof(unsigned char));
			memcpy(&image[image.size() - 4 * (i + 1) * width], row, 4 * width * sizeof(unsigned char));
		}
		delete row;

		texture = std::unique_ptr<RGBA8Texture>(new RGBA8Texture());
		texture->upload_raw(width, height, &image[0]);
	}


	void cleanup() {
		glBindVertexArray(0);
		glUseProgram(0);
		glDeleteBuffers(1, &_vpoint);
		glDeleteBuffers(1, &_vnormal);
		glDeleteProgram(_pid);
		glDeleteVertexArrays(1, &_vao);
		
	}

	void draw() {
		bindShader();
		///--- Setup the texture units

		glActiveTexture(GL_TEXTURE0);
		water_tex->bind();
		glUniform1i(glGetUniformLocation(_pid, "water"), 0 /*GL_TEXTURE0*/);
		glActiveTexture(GL_TEXTURE1);
		sand_tex->bind();
		glUniform1i(glGetUniformLocation(_pid, "sand"), 1 /*GL_TEXTURE1*/);
		glActiveTexture(GL_TEXTURE2);
		grass_tex->bind();
		glUniform1i(glGetUniformLocation(_pid, "grass"), 2 /*GL_TEXTURE2*/);

		glUniform1f(glGetUniformLocation(_pid, "time"), glfwGetTime());
		glDrawElements(GL_TRIANGLES, /*#vertices*/ 3 * mesh.n_faces(), GL_UNSIGNED_INT, 0);		
		unbindShader();
	}

	GLuint getProgramID() { return _pid; }

private:
	void bindShader() {
		glUseProgram(_pid);
		glBindVertexArray(_vao);
		

		///--- Vertex Attribute ID for Positions
		GLint vpoint_id = glGetAttribLocation(_pid, "vpoint");
		if (vpoint_id >= 0) {
			glEnableVertexAttribArray(vpoint_id);
			
			glBindBuffer(GL_ARRAY_BUFFER, _vpoint);
			glVertexAttribPointer(vpoint_id, 3 /*vec3*/, GL_FLOAT, GL_FALSE, 0, 0);
			
		}

		///--- Vertex Attribute ID for Normals
		GLint vnormal_id = glGetAttribLocation(_pid, "vnormal");
		if (vnormal_id >= 0) {
			glEnableVertexAttribArray(vnormal_id);
			glBindBuffer(GL_ARRAY_BUFFER, _vnormal);
			glVertexAttribPointer(vnormal_id, 3 /*vec3*/, GL_FLOAT, GL_FALSE, 0, 0);
			
		}
	}

	void unbindShader() {
		GLint vpoint_id = glGetAttribLocation(_pid, "vpoint");
		if (vpoint_id >= 0)
			glDisableVertexAttribArray(vpoint_id);
		GLint vnormal_id = glGetAttribLocation(_pid, "vnormal");
		if (vnormal_id >= 0)
			glDisableVertexAttribArray(vnormal_id);
		glUseProgram(0);
		glBindVertexArray(0);
	}
};
