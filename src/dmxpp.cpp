#include <dmxpp/dmxpp.h>

#include <BufferStream.h>

using namespace dmxpp;

bool DMX::open(const std::byte* dmxData, std::size_t dmxSize) {
	if (this->opened || !dmxData || !dmxSize) {
		return false;
	}
	if (!this->openInternal(dmxData, dmxSize)) {
		return false;
	}
	this->opened = true;
	return true;
}

bool DMX::open(const unsigned char* dmxData, std::size_t dmxSize) {
	return this->open(reinterpret_cast<const std::byte*>(dmxData), dmxSize);
}

bool DMX::open(const std::vector<std::byte>& dmxData) {
	return this->open(dmxData.data(), dmxData.size());
}

bool DMX::open(const std::vector<unsigned char>& dmxData) {
	return this->open(dmxData.data(), dmxData.size());
}

DMX::operator bool() const {
	return this->opened;
}

bool DMX::openInternal(const std::byte* dmxData, std::size_t dmxSize) {
	BufferStream stream{dmxData, dmxSize};

	int id = stream.read<int>();
	if (id != MDL_ID) {
		return false;
	}

	return true;
}
