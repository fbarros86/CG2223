//#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
//#include "../libs/tiny_obj_loader.h"
#include "texture.cpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "model.h"


class Model {
public:
	unsigned int indexesCount;
	bool isObj, hadTex;
	GLuint vertices, indices, normals, texCoords;
	std::string file_name;
	Texture textura;
	
	int isOBJFile(const std::string& file_name) {
		// Find the last occurrence of '.' in the file name
		std::size_t dot_index = file_name.find_last_of(".");

		// Check if a dot was found and it is not the first or last character
		if (dot_index != std::string::npos && dot_index != 0 && dot_index != file_name.length() - 1) {
			// Get the file extension by extracting the substring after the dot
			std::string file_extension = file_name.substr(dot_index + 1);

			// Compare the file extension with "obj" (case-insensitive)
			for (char& c : file_extension) {
				c = std::tolower(c);
			}
			return file_extension == "obj";
		}
		return false;
	};

	Model(std::string file_name, bool hadTex, std::string tex_name) {
		this->file_name = file_name;
		this->isObj = isOBJFile(file_name);
		this->hadTex = hadTex;
		if (hadTex) {
			this->textura = Texture(tex_name);
		}
		
			std::vector<unsigned int> indexes;
			std::vector<float> points;
			std::vector<float> normals;
			std::vector<float> textures;
			this->isObj = isOBJFile(this->file_name);
			std::string full_path = "../models/" + this->file_name;

			std::ifstream model_file("../models/" + this->file_name);
			if (!model_file.is_open()) {
				std::cerr << "Error: Failed to open model file " << this->file_name << std::endl;
			}
			if (!this->isObj){
				

				float value1, value2, value3, normal1, normal2, normal3, texture1, texture2;
				std::string line;

				std::getline(model_file, line);
				std::istringstream iss(line);

				while (iss >> value1 >> value2 >> value3 >> normal1 >> normal2 >> normal3 >> texture1 >> texture2) {
					points.push_back(value1);
					points.push_back(value2);
					points.push_back(value3);

					normals.push_back(normal1);
					normals.push_back(normal2);
					normals.push_back(normal3);

					textures.push_back(texture1);
					textures.push_back(texture2);
				}

				std::getline(model_file, line);
				std::istringstream iss2(line);

				while (iss2 >> value1) {
					indexes.push_back(value1);
				}

			}
			/*
			else {
				tinyobj::attrib_t attrib;
				std::vector<tinyobj::shape_t> shapes;
				std::vector<tinyobj::material_t> materials;

				std::string warn;
				std::string err;

				bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, full_path.c_str());

				if (!warn.empty()) {
					std::cout << warn << std::endl;
				}

				if (!err.empty()) {
					std::cerr << err << std::endl;
				}

				if (!ret) {
					exit(1);
				}

				// Loop over shapes
				for (size_t s = 0; s < shapes.size(); s++) {
					// Loop over faces(polygon)
					size_t index_offset = 0;
					for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
						size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

						// Loop over vertices in the face.
						for (size_t v = 0; v < fv; v++) {
							// access to vertex
							tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

							tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
							tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
							tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
							points.push_back(vx);
							points.push_back(vy);
							points.push_back(vz);
							// Check if `normal_index` is zero or positive. negative = no normal data
							if (idx.normal_index >= 0) {
								tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
								tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
								tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
								normals.push_back(nx);
								normals.push_back(ny);
								normals.push_back(nz);
							}

							// Check if `texcoord_index` is zero or positive. negative = no texcoord data
							if (idx.texcoord_index >= 0) {
								tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
								tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
								textures.push_back(tx);
								textures.push_back(ty);
							}
							// Optional: vertex colors
							// tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
							// tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
							// tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
						}
						index_offset += fv;


						// per-face material
						shapes[s].mesh.material_ids[f];
					}
				}
			}
			*/
			glGenBuffers(1, &(this->vertices));
			glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* points.size(), points.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &(this->normals));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->normals);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)* normals.size(), normals.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &(this->texCoords));
			glBindBuffer(GL_ARRAY_BUFFER, this->texCoords);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* textures.size(), textures.data(), GL_STATIC_DRAW);

			this->indexesCount = indexes.size();
			glGenBuffers(1, &(this->indices));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* (this->indexesCount), indexes.data(), GL_STATIC_DRAW);
		};

	void draw(bool hadtex) {
			if (hadtex) {
				glBindTexture(GL_TEXTURE_2D, (this->textura).texID);
				glBindBuffer(GL_ARRAY_BUFFER, texCoords);
				glTexCoordPointer(2, GL_FLOAT, 0, 0);
			}
			glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
			glVertexPointer(3, GL_FLOAT, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, this->normals);
			glNormalPointer(GL_FLOAT, 0, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
			glDrawElements(GL_TRIANGLES, this->indexesCount, GL_UNSIGNED_INT, 0);
		};
};