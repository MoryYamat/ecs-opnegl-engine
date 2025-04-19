#pragma once
#include "Entity.h"
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <type_traits>
#include <vector>
#include <memory>


// A system for managing the relationship between entities and components
// (Entity��Component�̊֌W���Ǘ�����V�X�e��)
class ECS{
private:

	uint32_t nextEntityID = 1;


	// ����Efficiency issues����	
	// ����Efficiency issues����
	// ����Efficiency issues����
	// Entity���ƂɃR���|�[�l���g��R�Â���
	std::unordered_map<std::type_index, std::unordered_map<uint32_t, std::shared_ptr<void>>> componentPools;



public:
	// 
	Entity createEntity() {
		return Entity{ nextEntityID++ };
	}
	
	// Add any component to an Entity(�C�ӂ̃R���|�[�l���g�ǉ�)�i�f�[�^�C���X�^���X�̃R�s�[�j
	template<typename T>
	void addComponent(Entity e, T component) {
		const std::type_index type = std::type_index(typeid(T));

		// ini
		if (componentPools.find(type) == componentPools.end())
		{
			componentPools[type] = std::unordered_map<uint32_t, std::shared_ptr<void>>();
		}


		// Register the entity to shared_ptr`pack`
		componentPools[type][e.id] = std::make_shared<T>(component);
	}

	// Get component(�R���|�[�l���g���擾)
	template<typename T>
	T& get(Entity e) {
		std::type_index type = std::type_index(typeid(T));
		return *std::static_pointer_cast<T>(componentPools[type][e.id]);
	}

	// 
	template<typename... Components>
	std::vector<Entity> view() {
		// ��̌���
		std::vector<Entity> result;

		// �x�[�X�ƂȂ�R���|�[�l���g�i�ŏ��̌^�j���g��
		using FirstComponent = typename std::tuple_element<0, std::tuple<Components...>>::type;
		const std::type_index firstType = std::type_index(typeid(FirstComponent));

		// �x�[�X�ɂ���map�����݂��Ȃ��ꍇ�͋�ŕԂ�
		if (componentPools.find(firstType) == componentPools.end()) {
			return result;
		}

		// ���O�T��
		const auto& base = componentPools[firstType];

		// �T��(�����������i��)
		for (const auto& [entityID, _] : base) {
			// �S�Ă�Component������entity�Ɋ܂܂�Ă��邩�m�F(��ݍ��ݎ�)
			bool hasAll = (... && (
				componentPools.count(std::type_index(typeid(Components))) &&//���̌^�����݂��邩
				componentPools[std::type_index(typeid(Components))].count(entityID)// ���̌^������Entity�������Ă��邩
				));

			if (hasAll) {
				result.push_back(Entity{ entityID });
			}
		}

		return result;

	}



};