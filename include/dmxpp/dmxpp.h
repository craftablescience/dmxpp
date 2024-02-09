#pragma once

#include <vector>

namespace dmxpp {

class DMX {
public:
	[[nodiscard]] bool open(const std::byte* dmxData, std::size_t dmxSize);

	[[nodiscard]] bool open(const unsigned char* dmxData, std::size_t dmxSize);

	[[nodiscard]] bool open(const std::vector<std::byte>& dmxData);

	[[nodiscard]] bool open(const std::vector<unsigned char>& dmxData);

	[[nodiscard]] explicit operator bool() const;

protected:
	DMX() = default;

	[[nodiscard]] bool openInternal(const std::byte* dmxData, std::size_t dmxSize);

private:
	bool opened = false;
};

} // namespace dmxpp
