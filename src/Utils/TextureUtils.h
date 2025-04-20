#pragma once

#include <glad/glad.h>

#include "Core/Image/ImageData.h"

namespace TextureUtils {
	GLuint uploadTextureToGPU(const RawImage& image);
}