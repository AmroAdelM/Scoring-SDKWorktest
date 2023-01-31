# Introduction
This document provides an overview of the implementation of the tiny game client SDK in C++. The purpose of this SDK is to provide essential functionality to multiple games that each have their own tech stack and requirements. 

# Functionality
1. Store and retrieve a user’s score for each level of a game. Users are represented by a numeric ID.
2. Retrieve a top-list of all known scores for a given level.
3. Retrieve the highest score of all levels for a single user.

# Implementation Details
- The ScoringSDK class provides the main interface for interacting with the SDK. The class holds a vector of Score structs that represent the scores for each user and level.
- The ScoringSDK class also provides an interface for file handling through the IFileHandler class.
- The file handling functionality can be replaced at runtime or build-time, allowing for the testing of the SDK without accessing the file system.
- The FileSystemHandler class is provided as an implementation of the FileHandler interface.
- This class reads and writes score data to a text file, where each line represents a score and is separated by commas.

- Unit tests were written to verify the functionality of the ScoringSDK and FileSystemHandler classes. The tests cover all functionality provided by the SDK and verify that the correct data is stored, retrieved, and written to separate files for each test.

# Assumptions
The text file storing the scores will be in the format of one score per line, with each line containing the user ID, level, and score separated by commas.
The file handling implementation provided by the IFileHandler interface and the FileSystemHandler class is sufficient for the needs of the games using the SDK. If additional file handling functionality is needed, a new implementation of the FileHandler interface will need to be created.

# Future Work
- Adding support for saving/reading scores from a database instead of a text file.
- Adding encryption for score data to ensure the data is secure and private
- Implementing a UI for viewing the scores, such as a web page or a graphical interface

