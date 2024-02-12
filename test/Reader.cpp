#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include <dmxpp/dmxpp.h>

#include "Config.h"

using namespace dmxpp;

static std::vector<std::byte> readFileToBuffer(const std::string& path) {
	std::ifstream file(path, std::ios::binary);
	file >> std::skipws;
	auto size = std::filesystem::file_size(path);
	std::vector<std::byte> out(size);
	file.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(size));
	return out;
}

// v1 and v2 are identical afaik...
TEST(Reader, v2) {
	DMX dmx{::readFileToBuffer(TEST_FILE_ROOT_PATH "binary/v2.dmx")};
	ASSERT_TRUE(dmx);
}

TEST(Reader, v3) {
	DMX dmx{::readFileToBuffer(TEST_FILE_ROOT_PATH "binary/v3.dmx")};
	ASSERT_TRUE(dmx);
}

TEST(Reader, v4) {
	DMX dmx{::readFileToBuffer(TEST_FILE_ROOT_PATH "binary/v4.dmx")};
	ASSERT_TRUE(dmx);
}

TEST(Reader, v5) {
	DMX dmx{::readFileToBuffer(TEST_FILE_ROOT_PATH "binary/v5.dmx")};
	ASSERT_TRUE(dmx);
}
