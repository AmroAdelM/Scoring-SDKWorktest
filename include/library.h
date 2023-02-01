#ifndef LIBRARY_H
#define LIBRARY_H

#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

namespace storage {

	struct Score {
		int userId;
		int levelId;
		int score;
		bool operator>(Score const& tmp) const { return score > tmp.score; }
		Score(int userId, int levelId, int score);
	};

	class IFileHandler
	{
	public:
		IFileHandler(const std::string& fileName) : m_fileName(fileName) {}
		virtual void save_scores(const std::multiset<Score, std::greater<Score>>& scores) = 0;
		virtual std::multiset<Score, std::greater<Score>> read_scores() = 0;

	protected:
		std::string m_fileName;
	};

	class FileSystemHandler : public IFileHandler
	{
	public:
		FileSystemHandler(const std::string& fileName);
		virtual ~FileSystemHandler() = default;
		void save_scores(const std::multiset<Score, std::greater<Score>>& scores) override;
		std::multiset<Score, std::greater<Score>> read_scores() override;
	};

	class ScoringSDK
	{
	public:
		ScoringSDK(IFileHandler&);
		void storeScore(int userId, int levelId, int score);
		int retrieveScore(int userId, int levelId);
		std::vector<std::tuple<int, int, int>> retrieveToplist(int levelId);
		std::pair<int, int> retrieveHighestScore(int userId);

	private:
		std::multiset<Score, std::greater<Score>> m_scores;
		IFileHandler& m_fileHandler;
	};
}

#endif //LIBRARY_H
