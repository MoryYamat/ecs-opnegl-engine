#pragma once
#include <stb_image.h>

#include <iostream>
#include <string>

// �摜�p�f�[�^�\����
struct RawImage {
	unsigned char* data = nullptr;
	int width = 0;
	int height = 0;
	int channels = 0;
	std::string path;

    RawImage() = default;

	~RawImage() 
	{
		//if (data) stbi_image_free(data);
		std::cout << "[�x��] RawImage�̃R�s�[���Ă΂�܂����I" << std::endl;
	}

	// �����I�Ɉ��S�ɁB
	//�R�s�[�֎~(�|�C���^�d���ɂ��2������h��)
	//RawImage(const RawImage&) = delete;
	//RawImage& operator=(const RawImage&) = delete;

 //   RawImage(RawImage&& other) noexcept {
 //       data = other.data;
 //       width = other.width;
 //       height = other.height;
 //       channels = other.channels;
 //       path = std::move(other.path);

 //       other.data = nullptr; // ������data�𖳌����I
 //   }

 //   // ���[�u������Z�q
 //   RawImage& operator=(RawImage&& other) noexcept {
 //       if (this != &other) {
 //           if (data) stbi_image_free(data);

 //           data = other.data;
 //           width = other.width;
 //           height = other.height;
 //           channels = other.channels;
 //           path = std::move(other.path);

 //           other.data = nullptr;
 //       }
 //       return *this;
 //   }
};