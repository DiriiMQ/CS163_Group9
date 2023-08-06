//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_API_H
#define CS163_GROUP9_API_H

#include <string>
#include <vector>

#include "Dict.h"
#include "Quiz.h"
#include "stuff/Constants.h"

class Dicts {
public:
    Dict dicts[3]; // use Constants::TypeDict to index
    Dicts(); // load Dicts
};

class BaseApi {
protected:
    Dicts& dicts;

public:
    explicit BaseApi(Dicts& dicts) : dicts(dicts) {};
};

class ApiFavorite : public BaseApi {
public:
    explicit ApiFavorite(Dicts& dicts) : BaseApi(dicts) {};

    void addFavorite(Constants::TypeDict typeDict, std::string word);
    bool removeFavorite(Constants::TypeDict typeDict, std::string word); // return true if success, false if not found
    std::vector<Dict> getFavorite(Constants::TypeDict typeDict);
    void resetFavorite(Constants::TypeDict typeDict);
};

class ApiWord : public BaseApi {
public:
    explicit ApiWord(Dicts& dicts) : BaseApi(dicts) {};

    Word getWord(Constants::TypeDict typeDict, std::string word);
    void addWord(Constants::TypeDict typeDict, Word word);
    bool removeWord(Constants::TypeDict typeDict, std::string word); // return true if success, false if not found
    void editWord(Constants::TypeDict typeDict, std::string word, std::string newDefinition);
    Word getRandomWord(Constants::TypeDict typeDict);
};

class ApiSearch : public BaseApi {
public:
    explicit ApiSearch(Dicts& dicts) : BaseApi(dicts) {};

    std::vector<Word> getAutoCompleteListForWord(Constants::TypeDict typeDict, std::string word);
    std::vector<Word> getAutoCompleteListForDefinition(Constants::TypeDict typeDict, std::string definition);

    std::vector<Word> getHistory(Constants::TypeDict typeDict);
};

class ApiQuiz :  public BaseApi {
private:
    Quiz quiz;
public:
    explicit ApiQuiz(Dicts& dicts) : BaseApi(dicts) {};

    Quiz getQuiz(Constants::TypeDict typeDict); // random word, then recreate quiz from that word and return it
    bool submitQuiz(Constants::TypeDict typeDict, QuizResponse response); // return true if correct, false if not
};

class Api : public BaseApi {
public:
    ApiFavorite apiFavorite;
    ApiWord apiWord;
    ApiSearch apiSearch;
    ApiQuiz apiQuiz;

    explicit Api(Dicts& dicts) : BaseApi(dicts), apiFavorite(dicts), apiWord(dicts), apiSearch(dicts), apiQuiz(dicts) {};

    void resetDict(Constants::TypeDict typeDict);
};


#endif //CS163_GROUP9_API_H