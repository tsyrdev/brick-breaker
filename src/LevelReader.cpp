#include "LevelReader.hpp"

LevelReader& LevelReader::GetInstance() {
    static LevelReader* s_instance = new LevelReader();
    return *s_instance;
}
Level LevelReader::LoadLevel(std::string filepath) {
   auto it = m_levels.find(filepath);
    if (it == m_levels.end()) {
        Level newLevel = ReadLevel(filepath); 
        m_levels.insert(std::make_pair(filepath, newLevel)); 
        return newLevel; 
    } else {
        return it->second; 
    }
}
void LevelReader::SaveScore(int newScore, std::string levelName) {
    auto it = m_bestScores.find(levelName);
    if (it == m_bestScores.end()) {
        it->second = newScore;
    }
}
void LevelReader::LoadScores(std::string filepath) {
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        std::cout << "File open error" << std::endl;
    }
    std::string line;
    std::string levelName;
    int x = 0; 
    while (std::getline(inputFile, line)) {
        if (x % 2 == 0) {
            levelName = line;  
        } else {
            m_bestScores.insert(std::make_pair(levelName, std::stoi(line)));
        }
    } 
}
LevelReader::LevelReader() {

}
LevelReader::LevelReader(LevelReader const&) {

}
LevelReader LevelReader::operator=(LevelReader const&) {
    return *this;
}
LevelReader::~LevelReader() {

}
Level LevelReader::ReadLevel(std::string filepath) {
    static int counter = 0;
    Level newLevel;
    memset(&newLevel.shape, 0, sizeof(newLevel.shape));

    int nameSec = 0;
    int mapSec = 0;
    int powerSec = 0;

    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        std::cout << "File open error" << std::endl;
        return newLevel; 
    }

    std::string line;
    int x = 0;
    while (std::getline(inputFile, line)) {
        counter++; 
        if (nameSec == 0 && line == "#")
            nameSec = 1;
        else if (nameSec == 1){
            newLevel.name = line;  
            nameSec = -1; 
        }
        if (mapSec == 0 && line == "-") {
            mapSec = 1;
        } else if (mapSec == 1){
            if (line == "-") {
                mapSec = -1;  
                x = 0; 
            }
            else {
                for (int y = 0; y < SHAPE_WIDTH; ++y)
                    newLevel.shape[x][y] = line[y] - '0';
                x++;
            }
        }
        if (powerSec == 0 && line == "!") {
            powerSec = 1;
        } else if (powerSec == 1) {
            if (line == "!") {
                powerSec = -1;
                x = 0;
            }
            else {
                for (int y = 0; y < SHAPE_WIDTH; ++y)
                    newLevel.powers[x][y] = ConvertPower(line[y]);
                x++;
            }
        }
    }

    auto it = m_bestScores.find(newLevel.name);
    if (it == m_bestScores.end()) {
        newLevel.bestScore = 0;
        m_bestScores.insert(std::make_pair(newLevel.name, 0));
    } else {
        newLevel.bestScore = it->second;
    }
    return newLevel; 
}

Power LevelReader::ConvertPower(const char power) {
    if (power == POWER_BALL_SLOW_DOWN)
        return Power::BALL_SLOW_DOWN;
    else if (power == POWER_BALL_SPEED_UP)
        return Power::BALL_SPEED_UP;
    else if (power == POWER_PLAYER_SPEED_UP)
        return Power::PLAYER_SPEED_UP;
    else if (power == POWER_PLAYER_SLOW_DOWN)
        return Power::PLAYER_SLOW_DOWN;
    else if (power == POWER_PLUS_LIFE)
        return Power::PLUS_LIFE;
    else if (power == POWER_MINUS_LIFE)
        return Power::MINUS_LIFE;
    else 
        return Power::NOTHING;
}
