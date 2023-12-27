#ifndef LAB3_MISSION_H
#define LAB3_MISSION_H

#include "../echelon/Echelon.h"
#include "../../template/table.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Mission {
private:
    std::string Mission_name;
    Table<std::shared_ptr<Echelon>> UserTable;
    Table<std::shared_ptr<Echelon>> EnemyTable;
    Table<std::shared_ptr<Echelon>> VisibleUserEchelons;   //  звенья которые видны противнику
    Table<std::shared_ptr<Echelon>> VisibleEnemyEchelons;  //  звенья которые видны игроку

public:
//    static Mission loadMissionFromJsonFile(const std::string &filename) {
//        Mission mission;
//
//        try {
//            std::ifstream file(filename);
//            if (!file.is_open()) {
//                throw std::runtime_error("Failed to open JSON file.");
//            }
//
//            json missionJson;
//            file >> missionJson;
//
//            mission = parseMissionJson(missionJson);
//        } catch (const std::exception &e) {
//            std::cerr << "Error loading mission from JSON: " << e.what() << std::endl;
//        }
//
//        return mission;
//    }
};


#endif //LAB3_MISSION_H
