
#include "texture.h"
	
	Texture::Texture(){};

	Texture::Texture(std::string texture_name) {
		std::string path = "../textures/" + texture_name;
		const char* str = path.c_str();
		std::string s = str;
		unsigned int t, tw, th;
		unsigned char* texData;
		unsigned int texID;

		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

		ilGenImages(1, &t);
		ilBindImage(t);
		ilLoadImage((ILstring)s.c_str());

		tw = ilGetInteger(IL_IMAGE_WIDTH);
		th = ilGetInteger(IL_IMAGE_HEIGHT);

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		texData = ilGetData();

		// create a texture slot
		glGenTextures(1, &texID);
		// bind the slot
		glBindTexture(GL_TEXTURE_2D, texID);

		// define texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

		// send texture data to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		this->texID = texID;
	};