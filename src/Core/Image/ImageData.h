#pragma once
#include <string>

// 画像用データ構造体
struct RawImage {
	unsigned char* data = nullptr;
	int width = 0;
	int height = 0;
	int channels = 0;
	std::string path;

	~RawImage() {
		//if (data) stbi_image_free(data);
	}
};