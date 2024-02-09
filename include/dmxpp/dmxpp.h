#pragma once

#include "Format.h"
#include "Value.h"

class BufferStream;

namespace dmxpp {

class DMX {
public:
	DMX() = default;

	[[nodiscard]] bool open(const std::byte* dmxData, std::size_t dmxSize);

	[[nodiscard]] bool open(const unsigned char* dmxData, std::size_t dmxSize);

	[[nodiscard]] bool open(const std::vector<std::byte>& dmxData);

	[[nodiscard]] bool open(const std::vector<unsigned char>& dmxData);

	[[nodiscard]] explicit operator bool() const;

	[[nodiscard]] std::string_view getFormatType() const;

	[[nodiscard]] int getFormatVersion() const;

protected:
	[[nodiscard]] bool openInternalText(const std::byte* dmxData, std::size_t dmxSize);

	[[nodiscard]] bool openInternalBinary(BufferStream& stream);

private:
	bool opened = false;

	// Header
	std::string formatType;
	int formatVersion = -1;
	std::string encodingType;
	int encodingVersion = -1;

	// Elements
	std::vector<Element> elements;
};

} // namespace dmxpp
