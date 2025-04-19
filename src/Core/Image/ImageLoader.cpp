#include "ImageLoader.h"
#include <stb_image.h>
#include <iostream>

RawImage loadImageFromFile(const std::string& path)
{
	RawImage img;
	img.path = path;
	img.data = stbi_load(path.c_str(), &img.width, &img.height, &img.channels, 0);

	if (!img.data)
	{
		std::cout << "Failed to load image: " << path << std::endl;
	}

	return img;
}