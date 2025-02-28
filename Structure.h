// Structure.h
#pragma once
#include <string>
#include <vector>
#include "Enemy.h"
#include "Item.h"
#include "Player.h"

enum class StructureType {
    CAVE,
    CASTLE,
    VILLAGE,
    HOUSE
};

struct Riddle {
    std::string question;
    std::vector<std::string> options; // 4 multiple-choice answers
    int correctIndex;                 // which index (0..3) is correct
    std::vector<std::string> hints;
};

class Structure {
public:
    Structure(StructureType type, int totalRooms);

    std::string getTypeString() const;
    bool isFullyExplored() const;
    bool exploreNextRoom(Player &player);
    bool hasFoundArtifactThisRoom() const { return foundArtifactThisRoom_; }

private:
    StructureType type_;
    int totalRooms_;
    int currentRoomIndex_;
    bool fullyExplored_;
    bool foundArtifactThisRoom_;

    std::vector<Riddle> riddlePool_;
    Riddle riddleToAsk_;

    void initRiddles();
    bool doRiddle(Player &player); 

    void handleRoom(Player &player);
    void handleChest(Player &player);
};
