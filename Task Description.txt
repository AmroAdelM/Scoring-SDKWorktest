The task
========
Your task is to implement a tiny game client SDK. The purpose of a game client
SDK is to provide essential functionality to multiple games that each have their
own tech stack and requirements.

We think that this task should take one working day or less to complete. If you
run out of time, please include a note of what you intended to implement.

Functionality
-------------
* Store and retrieve a user’s score for each level of a game.
    * Users are represented by a numeric ID.
* Retrieve a top-list of all known scores for a given level.
* Retrieve the highest score of all levels for a single user.

Other requirements
------------------
* It must be possible to replace the file handling code at either runtime or
    build-time. This will make it possible to, for example, test the SDK
    without needing to access the file system.
* No external dependencies other than the STL.
* Any version of C++ is allowed, but try to only use functionality that has
    wide support across these compilers: GCC, Clang and MSVC.

As you can tell, this is a quite high level description. We encourage you to
think about reasonable assumptions based on the domain, and draw from your
knowledge and experience. There are no rights or wrongs, but be prepared to
explain your thought process.

We have provided a skeleton project structure for you to get started. You may
use it, modify it or discard it altogether if you prefer.

What we expect you to deliver
-----------------------------
* A zip archive containing your source code project, including automated tests
    if you wrote any.
* Instructions for building and running your code.
* Your implementation notes, e.g. assumptions made and if there was anything
    you intended to do but didn't have time for.

What we look for in your code
-----------------------------
The purpose of this test is for you to show off your skills, and to give us
plenty of things to discuss in a technical interview.

We're not particularly bothered by inefficient code, small bugs, or not 
following the specification to the letter. What does matter is how the big
picture fits together, that the API makes sense, that you've used the C++ 
language and its standard library well, and that you've thought out pragmatic
and reasonable solutions.

-------------------------------------------------------------------------------
(C) King.com Ltd 2022                                                Version 3J