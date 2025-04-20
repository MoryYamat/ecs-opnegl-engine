#pragma once


#include <vector>

#include "Core/ECS/Component/MeshComponent.h"
#include "Graphics/Model/ModelData.h"

namespace GPUBufferUtils {
	MeshComponent createMeshComponentFromMeshData(const MeshData& mesh);

	//void deleteMeshComponent(MeshComponent& mesh);
}

