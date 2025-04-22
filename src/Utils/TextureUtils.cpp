#include "TextureUtils.h"

#include <iostream>

namespace TextureUtils {

	GLuint uploadTextureToGPU(const RawImage& image)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		GLenum format = GL_RGB;
		if (image.channels == 1)
			format = GL_RED;
		else if (image.channels == 3)
			format = GL_RGB;
		else if (image.channels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format,
			image.width, image.height, 0,
			format, GL_UNSIGNED_BYTE, image.data);

		glGenerateMipmap(GL_TEXTURE_2D);

		//テクスチャパラメータ設定
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		//std::cout << "Uploaded texture to GPU: " << image.path << "(id = " << textureID << ")" << std::endl;


		return textureID;
	}

}