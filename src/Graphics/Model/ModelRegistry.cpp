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

		//[要修正]:::ここで位置やスケールを決めるのは明らかにおかしい:::[要修正]
		//[要修正]:::ここで位置やスケールを決めるのは明らかにおかしい:::[要修正]
		//[要修正]:::ここで位置やスケールを決めるのは明らかにおかしい:::[要修正]
		//[要修正]:::ここで位置やスケールを決めるのは明らかにおかしい:::[要修正]
		TransformComponent transform;
		transform.position = glm::vec3(0.0f);
		transform.rotation = glm::vec3(0.0f);
		transform.scale = glm::vec3(0.01f);
		
		ecs.addComponent<TransformComponent>(e, transform);

		// MeshComponent登録
		MeshComponent meshComp = GPUBufferUtils::createMeshComponentFromMeshData(mesh);
		ecs.addComponent<MeshComponent>(e, meshComp);

		// MaterialComponentの登録
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