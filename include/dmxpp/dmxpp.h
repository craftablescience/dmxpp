#pragma once

#include "Format.h"
#include "Value.h"

class BufferStream;

namespace dmxpp {

class DMX {
public:
	DMX(const std::byte* dmxData, std::size_t dmxSize);

	DMX(const unsigned char* dmxData, std::size_t dmxSize);

	explicit DMX(const std::vector<std::byte>& dmxData);

	explicit DMX(const std::vector<unsigned char>& dmxData);

	[[nodiscard]] explicit operator bool() const;

	[[nodiscard]] std::string_view getFormatType() const;

	[[nodiscard]] int getFormatVersion() const;

	[[nodiscard]] const std::vector<Element>& getElements() const;

protected:
	[[nodiscard]] bool openText(const std::byte* dmxData, std::size_t dmxSize);

	[[nodiscard]] bool openBinary(BufferStream& stream);

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
