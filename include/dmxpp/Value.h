#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace dmxpp {

namespace Value {

struct Element {
	std::uint32_t index;
	std::string stubGUID;
};

using ByteArray = std::vector<std::byte>;

using Time = float;

struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct Vector2 {
	float x;
	float y;
};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;
};

using EulerAngle = Vector3;

using Quaternion = Vector4;

struct Matrix4x4 {
	Vector4 r0;
	Vector4 r1;
	Vector4 r2;
	Vector4 r3;
};

using Generic = std::variant<
	Element,
	int,
	float,
	bool,
	std::string,
	std::vector<std::byte>,
	//Time, // Same as float
	Color,
	Vector2,
	Vector3,
	Vector4,
	//EulerAngle, // Same as Vector3
	//Quaternion, // Same as Vector4
	Matrix4x4,
	std::vector<Element>,
	std::vector<int>,
	std::vector<float>,
	std::vector<bool>,
	std::vector<std::string>,
	std::vector<std::vector<std::byte>>,
	//std::vector<Time>,
	std::vector<Color>,
	std::vector<Vector2>,
	std::vector<Vector3>,
	std::vector<Vector4>,
	//std::vector<EulerAngle>,
	//std::vector<Quaternion>,
	std::vector<Matrix4x4>
>;

enum class ID : unsigned char {
	INVALID = 0,

	VALUE_START = 1,
	ELEMENT = 1,
	INT = 2,
	FLOAT = 3,
	BOOL = 4,
	STRING = 5,
	BYTEARRAY = 6,
	TIME = 7, // OBJECT_ID in v1 & v2
	COLOR = 8,
	VECTOR2 = 9,
	VECTOR3 = 10,
	VECTOR4 = 11,
	EULER_ANGLE = 12,
	QUATERNION = 13,
	MATRIX_4X4 = 14,
	VALUE_END = 14,

	ARRAY_START = 15,
	ARRAY_ELEMENT = 15,
	ARRAY_INT = 16,
	ARRAY_FLOAT = 17,
	ARRAY_BOOL = 18,
	ARRAY_STRING = 19,
	ARRAY_BYTEARRAY = 20,
	ARRAY_TIME = 21, // ARRAY_OBJECT_ID in v1 & v2
	ARRAY_COLOR = 22,
	ARRAY_VECTOR2 = 23,
	ARRAY_VECTOR3 = 24,
	ARRAY_VECTOR4 = 25,
	ARRAY_EULER_ANGLE = 26,
	ARRAY_QUATERNION = 27,
	ARRAY_MATRIX_4X4 = 28,
	ARRAY_END = 28,
};

inline std::byte IDToByte(ID type) {
	return static_cast<std::byte>(type);
}

inline ID byteToID(std::byte id) {
	return static_cast<ID>(id);
}

inline ID arrayIDToInnerID(ID id) {
	if (id >= ID::ARRAY_START) {
		return static_cast<ID>(static_cast<unsigned char>(id) - static_cast<unsigned char>(ID::VALUE_END));
	}
	return id;
}

} // namespace Value

struct Attribute {
	std::string name;
	Value::ID type;
	Value::Generic value;

	template<typename T>
	std::optional<T> getValueAs() {
		if constexpr (std::holds_alternative<T>(this->value)) {
			try {
				return std::get<T>(this->value);
			} catch (const std::bad_variant_access&) {
				return std::nullopt;
			}
		}
		return std::nullopt;
	}
};

struct Element {
	std::string type;
	std::string name;
	std::array<std::byte, 16> guid;
	std::vector<Attribute> attributes;
};

} // namespace dmxpp