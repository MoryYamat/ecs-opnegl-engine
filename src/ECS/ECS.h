#pragma once
#include "Entity.h"
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <type_traits>
#include <vector>
#include <memory>


// A system for managing the relationship between entities and components
// (EntityとComponentの関係を管理するシステム)
class ECS{
private:

	uint32_t nextEntityID = 1;


	// ※※Efficiency issues※※	
	// ※※Efficiency issues※※
	// ※※Efficiency issues※※
	// Entityごとにコンポーネントを紐づける
	std::unordered_map<std::type_index, std::unordered_map<uint32_t, std::shared_ptr<void>>> componentPools;



public:
	// 
	Entity createEntity() {
		return Entity{ nextEntityID++ };
	}
	
	// Add any component to an Entity(任意のコンポーネント追加)（データインスタンスのコピー）
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

	// Get component(コンポーネントを取得)
	template<typename T>
	T& get(Entity e) {
		std::type_index type = std::type_index(typeid(T));
		return *std::static_pointer_cast<T>(componentPools[type][e.id]);
	}

	// 
	template<typename... Components>
	std::vector<Entity> view() {
		// 空の結果
		std::vector<Entity> result;

		// ベースとなるコンポーネント（最初の型）を使う
		using FirstComponent = typename std::tuple_element<0, std::tuple<Components...>>::type;
		const std::type_index firstType = std::type_index(typeid(FirstComponent));

		// ベースにするmapが存在しない場合は空で返す
		if (componentPools.find(firstType) == componentPools.end()) {
			return result;
		}

		// 事前探索
		const auto& base = componentPools[firstType];

		// 探索(候補を少しずつ絞る)
		for (const auto& [entityID, _] : base) {
			// 全てのComponentがそのentityに含まれているか確認(畳み込み式)
			bool hasAll = (... && (
				componentPools.count(std::type_index(typeid(Components))) &&//その型が存在するか
				componentPools[std::type_index(typeid(Components))].count(entityID)// その型をそのEntityが持っているか
				));

			if (hasAll) {
				result.push_back(Entity{ entityID });
			}
		}

		return result;

	}



};