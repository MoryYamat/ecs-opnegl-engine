#pragma once
#include <string>


struct RawImage {
	unsigned char* data = nullptr;
	int width = 0;
	int height = 0;
	int channels = 0;
	std::string path;

	~RawImage() {

	}
};