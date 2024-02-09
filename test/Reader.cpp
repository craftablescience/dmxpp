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

/*TEST(Reader, v1) {
	DMX dmx;
	bool opened = dmx.open(::readFileToBuffer(TEST_FILE_ROOT_PATH "v1.dmx"));
	ASSERT_TRUE(opened);
}*/

TEST(Reader, v2) {
	DMX dmx;
	bool opened = dmx.open(::readFileToBuffer(TEST_FILE_ROOT_PATH "v2.dmx"));
	ASSERT_TRUE(opened);
}

/*TEST(Reader, v3) {
	DMX dmx;
	bool opened = dmx.open(::readFileToBuffer(TEST_FILE_ROOT_PATH "v3.dmx"));
	ASSERT_TRUE(opened);
}

TEST(Reader, v4) {
	DMX dmx;
	bool opened = dmx.open(::readFileToBuffer(TEST_FILE_ROOT_PATH "v4.dmx"));
	ASSERT_TRUE(opened);
}

TEST(Reader, v5) {
	DMX dmx;
	bool opened = dmx.open(::readFileToBuffer(TEST_FILE_ROOT_PATH "v5.dmx"));
	ASSERT_TRUE(opened);
}*/
