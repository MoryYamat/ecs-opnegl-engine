#pragma once
#include <cstdint>

// ID
struct Entity {
	uint32_t id;

	// 演算子オーバーロード
	bool operator== (const Entity& other) const {
		return id == other.id;
	}

};