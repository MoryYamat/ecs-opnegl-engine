#pragma once
#include <cstdint>

// ID
struct Entity {
	uint32_t id;

	// ���Z�q�I�[�o�[���[�h
	bool operator== (const Entity& other) const {
		return id == other.id;
	}

};