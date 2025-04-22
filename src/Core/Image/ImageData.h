#pragma once
#include <stb_image.h>

#include <iostream>
#include <string>

// 画像用データ構造体
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
		std::cout << "[警告] RawImageのコピーが呼ばれました！" << std::endl;
	}

	// 将来的に安全に。
	//コピー禁止(ポインタ重複による2回解放を防ぐ)
	//RawImage(const RawImage&) = delete;
	//RawImage& operator=(const RawImage&) = delete;

 //   RawImage(RawImage&& other) noexcept {
 //       data = other.data;
 //       width = other.width;
 //       height = other.height;
 //       channels = other.channels;
 //       path = std::move(other.path);

 //       other.data = nullptr; // 他方のdataを無効化！
 //   }

 //   // ムーブ代入演算子
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