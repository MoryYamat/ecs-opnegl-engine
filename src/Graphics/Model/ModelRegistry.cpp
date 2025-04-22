#include "ModelRegistry.h"
#include "ModelData.h"

#include <iostream>

#include "Core/ECS/Component/TransformComponent.h"
#include "Core/ECS/Component/MeshComponent.h"
#include "Core/ECS/Component/MaterialComponent.h"

#include "Utils/GPUBufferUtils.h"
#include "Utils/TextureUtils.h"

void ModelRegistry::RegisterModelToECS(ECS& ecs, const ModelData& model)
{
	for (const MeshData& mesh : model.meshes)
	{
		Entity e = ecs.createEntity();

		//[�v�C��]:::�����ňʒu��X�P�[�������߂�͖̂��炩�ɂ�������:::[�v�C��]
		//[�v�C��]:::�����ňʒu��X�P�[�������߂�͖̂��炩�ɂ�������:::[�v�C��]
		//[�v�C��]:::�����ňʒu��X�P�[�������߂�͖̂��炩�ɂ�������:::[�v�C��]
		//[�v�C��]:::�����ňʒu��X�P�[�������߂�͖̂��炩�ɂ�������:::[�v�C��]
		TransformComponent transform;
		transform.position = glm::vec3(0.0f);
		transform.rotation = glm::vec3(0.0f);
		transform.scale = glm::vec3(0.01f);
		
		ecs.addComponent<TransformComponent>(e, transform);

		// MeshComponent�o�^
		MeshComponent meshComp = GPUBufferUtils::createMeshComponentFromMeshData(mesh);
		ecs.addComponent<MeshComponent>(e, meshComp);

		// MaterialComponent�̓o�^
		const MaterialData& matData = model.materials[mesh.materialIndex];

		MaterialComponent matComp;
		matComp.baseColor = matData.baseColor;
		matComp.shininess = matData.shininess;

		for (const auto& tex : matData.textures)
		{
			TextureSlot slot;
			slot.type = tex.type;

			slot.id = TextureUtils::uploadTextureToGPU(tex.image);

			matComp.textures.push_back(slot);

			//std::cout << "add textures to matComp" << std::endl;
		}


		ecs.addComponent<MaterialComponent>(e, matComp);
		//std::cout << "add MaterialComponent to ecs" << std::endl;
	}

}