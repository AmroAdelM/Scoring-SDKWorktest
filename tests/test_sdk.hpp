#include <gtest/gtest.h>
#include <library.h>
#include <string>

class ScoringSDKTest : public ::testing::Test {
protected:
	//storage::FileSystemHandler fileHandler;
	//storage::ScoringSDK testSDK;

	//ScoringSDKTest() :fileHandler("scores.txt"), testSDK(fileHandler) {}
};

TEST_F(ScoringSDKTest, TestStoreAndRetrieveScore) {
	storage::FileSystemHandler fileHandler(std::string("test1.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	testSDK.storeScore(1, 2, 100);
	testSDK.storeScore(2, 2, 200);
	testSDK.storeScore(3, 1, 300);

	EXPECT_EQ(100, testSDK.retrieveScore(1, 2));
	EXPECT_EQ(200, testSDK.retrieveScore(2, 2));
	EXPECT_EQ(300, testSDK.retrieveScore(3, 1));
}

TEST_F(ScoringSDKTest, TestRetrieveToplist) {
	storage::FileSystemHandler fileHandler(std::string("test2.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	testSDK.storeScore(1, 1, 100);
	testSDK.storeScore(2, 1, 200);
	testSDK.storeScore(3, 1, 300);

	std::vector<std::tuple<int, int, int>> expected_top_list = { {3, 1, 300} , {2, 1, 200}, {1, 1, 100} };
	EXPECT_EQ(expected_top_list, testSDK.retrieveToplist(1));
}

TEST_F(ScoringSDKTest, TestretrieveHighestScore) {
	storage::FileSystemHandler fileHandler(std::string("test3.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	testSDK.storeScore(1, 1, 100);
	testSDK.storeScore(1, 2, 200);
	testSDK.storeScore(1, 3, 300);

	EXPECT_EQ(3, testSDK.retrieveHighestScore(1).first);
	EXPECT_EQ(300, testSDK.retrieveHighestScore(1).second);
}


TEST_F(ScoringSDKTest, ProvidedTest1) {
	storage::FileSystemHandler fileHandler(std::string("test4.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	testSDK.storeScore(1, 100, 10'000);
	int score = testSDK.retrieveScore(1, 100);
	ASSERT_EQ(score, 10'000);
}

TEST_F(ScoringSDKTest, ProvidedTest2) {
	storage::FileSystemHandler fileHandler(std::string("test5.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	testSDK.storeScore(1, 100, 10'000);
	std::tuple<int, int> scoreTuple = testSDK.retrieveHighestScore(1);
	ASSERT_EQ(std::get<0>(scoreTuple), 100);
	ASSERT_EQ(std::get<1>(scoreTuple), 10'000);
}

TEST_F(ScoringSDKTest, MultipleLevels) {
	storage::FileSystemHandler fileHandler(std::string("test6.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	testSDK.storeScore(1, 1, 100);
	testSDK.storeScore(1, 2, 200);
	testSDK.storeScore(1, 3, 300);
	testSDK.storeScore(2, 1, 400);
	testSDK.storeScore(2, 2, 500);
	testSDK.storeScore(2, 3, 600);

	std::vector<std::tuple<int, int, int>> expected_top_list_level_1 = { {2, 1, 400 }, {1, 1, 100 } };
	EXPECT_EQ(expected_top_list_level_1, testSDK.retrieveToplist(1));

	std::vector<std::tuple<int, int, int>> expected_top_list_level_2 = { {2, 2, 500 }, {1, 2, 200} };
	EXPECT_EQ(expected_top_list_level_2, testSDK.retrieveToplist(2));

	std::vector<std::tuple<int, int, int>> expected_top_list_level_3 = { { 2, 3, 600 }, { 1, 3, 300} };
	EXPECT_EQ(expected_top_list_level_3, testSDK.retrieveToplist(3));

	EXPECT_EQ(300, testSDK.retrieveHighestScore(1).second);
	EXPECT_EQ(600, testSDK.retrieveHighestScore(2).second);
}

TEST_F(ScoringSDKTest, EmptyTopList) {
	storage::FileSystemHandler fileHandler(std::string("test7.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	std::vector<std::tuple<int, int, int>> expected_empty_top_list;
	EXPECT_EQ(expected_empty_top_list, testSDK.retrieveToplist(1));
}

TEST_F(ScoringSDKTest, NoScoreForUser) {
	storage::FileSystemHandler fileHandler(std::string("test8.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	EXPECT_EQ(0, testSDK.retrieveScore(1, 1));
	EXPECT_EQ(0, testSDK.retrieveHighestScore(1).second);
}

TEST_F(ScoringSDKTest, NoScoreForLevel) {
	storage::FileSystemHandler fileHandler(std::string("test9.txt"));
	storage::ScoringSDK testSDK(fileHandler);

	testSDK.storeScore(1, 1, 100);

	std::vector<std::tuple<int, int, int>> expected_empty_top_list;
	EXPECT_EQ(expected_empty_top_list, testSDK.retrieveToplist(2));
}

//
//TEST_F(ScoringSDKTest, TestretrieveHighestScore2) {
//	testSDK.storeScore(1, 100, 11'000);
//	testSDK.storeScore(1, 101, 15'000);
//	std::tuple<int, int> scoreTuple = testSDK.retrieveHighestScore(1);
//
//	ASSERT_EQ(std::get<0>(scoreTuple), 101);
//	ASSERT_EQ(std::get<1>(scoreTuple), 15'000);
//}
//
//TEST_F(ScoringSDKTest, TestRetrieveHighestScore2) {
//	testSDK.storeScore(1, 100, 12'000);
//	testSDK.storeScore(2, 101, 16'000);
//	std::tuple<int, int> scoreTuple = testSDK.retrieveHighestScore(2);
//
//	ASSERT_EQ(std::get<0>(scoreTuple), 101);
//	ASSERT_EQ(std::get<1>(scoreTuple), 16'000);
//}
//
//TEST_F(ScoringSDKTest, TestRetrieveHighestScore3) {
//	testSDK.storeScore(1, 103, 16'000);
//	testSDK.storeScore(2, 101, 15'000);
//	std::tuple<int, int> scoreTuple = testSDK.retrieveHighestScore(1);
//
//	ASSERT_EQ(std::get<0>(scoreTuple), 103);
//	ASSERT_EQ(std::get<1>(scoreTuple), 16'000);
//}
//
//TEST_F(ScoringSDKTest, TestStoreAndRetrieveScore2) {
//	testSDK.storeScore(1, 100, 10'000);
//	testSDK.storeScore(2, 100, 15'000);
//	std::vector<std::tuple< int, int, int>> scoreTuple = testSDK.retrieveToplist(100);
//
//	ASSERT_EQ(std::get<0>(*scoreTuple.begin()), 2);
//	ASSERT_EQ(std::get<1>(*scoreTuple.begin()), 100);
//	ASSERT_EQ(std::get<2>(*scoreTuple.begin()), 15'000);
//}
