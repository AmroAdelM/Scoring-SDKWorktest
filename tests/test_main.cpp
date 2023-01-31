#include <gtest/gtest.h>
#include "library.h"
#include "test_sdk.hpp"

namespace fs = std::filesystem;

int main() {

	::testing::InitGoogleTest();
	RUN_ALL_TESTS();

	return 0;
}