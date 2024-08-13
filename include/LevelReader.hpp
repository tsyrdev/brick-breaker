#ifndef LEVELREADER_HPP
#define LEVELREADER_HPP

#include "PowerBall.hpp"

#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>

const int SHAPE_WIDTH = 10;
const int SHAPE_HEIGHT = 10;
const char POWER_BALL_SLOW_DOWN = '<';
const char POWER_BALL_SPEED_UP = '>';
const char POWER_PLAYER_SLOW_DOWN = 'v';
const char POWER_PLAYER_SPEED_UP = '^';
const char POWER_PLUS_LIFE = '+';
const char POWER_MINUS_LIFE = '-';

struct Level {
    std::string name;
    int bestScore;
    int shape[SHAPE_HEIGHT][SHAPE_WIDTH];
    Power powers[SHAPE_HEIGHT][SHAPE_WIDTH];
};

class LevelReader {
    public: 
        static LevelReader& GetInstance();
        Level LoadLevel(std::string filepath);
        void SaveScore(int newScore, std::string levelName);
        void  LoadScores(std::string filepath);
   private: 
        LevelReader();
        LevelReader(LevelReader const&);
        LevelReader operator=(LevelReader const&);
        ~LevelReader();
        Level ReadLevel(std::string filepath);
        Power ConvertPower(const char power);
        std::unordered_map<std::string, Level> m_levels;
        std::unordered_map<std::string, int> m_bestScores; 
};

#endif
