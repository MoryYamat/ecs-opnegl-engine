#pragma once
#include <string>

// �摜�p�f�[�^�\����
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