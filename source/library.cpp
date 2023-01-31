#include <library.h>
namespace storage {

	Score::Score(int userId, int levelId, int score)
	{
		this->userId = userId;
		this->levelId = levelId;
		this->score = score;
	}
	FileSystemHandler::FileSystemHandler(const std::string& file_name) : IFileHandler(file_name)
	{}
	void FileSystemHandler::save_scores(const std::multiset<Score, std::greater<Score>>& scores)
	{
		std::ofstream file(file_name);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file for writing." << std::endl;
			return;
		}

		for (const auto& itr : scores)
		{
			file << itr.userId << "," << itr.levelId << "," << itr.score << '\n';
		}

		file.close();
	}
	std::multiset<Score, std::greater<Score>> FileSystemHandler::read_scores()
	{
		std::multiset<Score, std::greater<Score>> scores;

		std::ifstream file(file_name);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file for reading." << std::endl;
			return scores;
		}

		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream linestream(line);
			std::string user_id_str, level_str, score_str;

			std::getline(linestream, user_id_str, ',');
			std::getline(linestream, level_str, ',');
			std::getline(linestream, score_str, ',');

			int user_id = std::stoi(user_id_str);
			int level = std::stoi(level_str);
			int score = std::stoi(score_str);
			scores.insert(Score(user_id, level, score));
		}
		file.close();
		return scores;
	}

	ScoringSDK::ScoringSDK(IFileHandler& tmp) : fileHandler(tmp)
	{
		scores = fileHandler.read_scores();
	}

	void ScoringSDK::storeScore(int userId, int levelId, int score)
	{
		scores.insert(Score(userId, levelId, score));
		fileHandler.save_scores(scores);
	}

	int ScoringSDK::retrieveScore(int userId, int levelId)
	{
		scores = fileHandler.read_scores();
		for (const auto& itr : scores)
		{
			if (itr.userId == userId && itr.levelId == levelId)
			{
				return itr.score;
			}
		}

		return 0;
	}

	std::vector<std::tuple<int, int, int>> ScoringSDK::retrieveToplist(int levelId)
	{
		std::vector<std::tuple<int, int, int>> levelList;
		for (auto itr = scores.begin(); itr != scores.end(); itr++)
		{
			if (itr->levelId == levelId)
			{
				levelList.push_back(std::make_tuple(itr->userId, itr->levelId, itr->score));
			}
		}
		return levelList;
	}

	std::pair<int, int> ScoringSDK::retrieveHighestScore(int userId)
	{
		for (auto& itr : scores)
		{
			if (itr.userId == userId)
			{
				return std::make_pair(itr.levelId, itr.score);
			}
		}

		return { 0, 0 };
	}
}