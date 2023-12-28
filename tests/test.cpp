#include <gtest/gtest.h>
#include "../components/fighters/Fighter.h"
#include "../components/echelon/Echelon.h"
#include "../components/weapons/gun/gun.h"
#include "../components/weapons/rocket/rocketLauncher.h"
#include "../template/table.h"


// FIGHTER
TEST(FighterTest, InitialValues) {
    Fighter fighter("TestFighter", 100, 100, 10, 5, {}, {0, 0}, 20);
    EXPECT_EQ(fighter.getModel(), "TestFighter");
    EXPECT_EQ(fighter.getHP(), 100);
    EXPECT_EQ(fighter.getMaxHP(), 100);
    EXPECT_EQ(fighter.getSpeed(), 10);
    EXPECT_EQ(fighter.getMaxNumEquipment(), 5);
    EXPECT_EQ(fighter.getCoordinates(), std::make_pair(0, 0));
    EXPECT_EQ(fighter.getDetectionRadius(), 20);
    EXPECT_TRUE(fighter.getEquipment().empty());
}

TEST(FighterTest, SettersAndGetters) {
    Fighter fighter("TestFighter", 100, 100, 10, 5, {}, {0, 0}, 20);

    // Test setters and getters
    fighter.setModel("UpdatedModel");
    EXPECT_EQ(fighter.getModel(), "UpdatedModel");

    fighter.setHP(80);
    EXPECT_EQ(fighter.getHP(), 80);

    fighter.setMaxSurvivability(120);
    EXPECT_EQ(fighter.getMaxHP(), 120);

    fighter.setSpeed(15);
    EXPECT_EQ(fighter.getSpeed(), 15);

    fighter.setMaxNumEquipment(3);
    EXPECT_EQ(fighter.getMaxNumEquipment(), 3);

    fighter.setCoordinates({1, 2});
    EXPECT_EQ(fighter.getCoordinates(), std::make_pair(1, 2));

    fighter.setDetectionRadius(25);
    EXPECT_EQ(fighter.getDetectionRadius(), 25);
}

TEST(FighterTest, AttackRadiusEmptyEquipment) {
    Fighter fighter("TestFighter", 100, 100, 10, 5, {}, {0, 0}, 20);
    ASSERT_THROW(fighter.getAttackRadius(), std::runtime_error);
}

TEST(FighterTest, AttackRadiusNonEmptyEquipment) {
    Gun gun1("gun", 40, 15, 5, 50);
    RocketLauncher gun2("rocket", 40, 10, 5, 50, 5);
    auto g1 = std::make_shared<Gun>(gun1);
    auto g2 = std::make_shared<RocketLauncher>(gun2);
    std::vector<std::shared_ptr<Weapon>> equipment;
    equipment.push_back(g1);
    equipment.push_back(g2);

    Fighter fighter("TestFighter", 100, 100, 10, 5, equipment, {0, 0}, 20);
    EXPECT_EQ(fighter.getAttackRadius(), 15);
}

TEST(FighterTest, GetDamage) {
    Fighter fighter("TestFighter", 100, 100, 10, 5, {}, {0, 0}, 20);
    Projectile projectile(20, 50, WeaponType::GUN);

    fighter.getDamage(projectile);
    EXPECT_EQ(fighter.getHP(), 80);
}

TEST(FighterTest, AttemptAttackSuccessful) {
    auto g1 = std::make_shared<Gun>("gun", 40, 30, 5, 100);

    Fighter attacker("Attacker", 100, 100, 10, 5, {g1}, {0, 0}, 50);
    Fighter target("Target", 100, 100, 10, 5, {g1}, {5, 5}, 20);
    auto t = std::make_shared<Fighter>(target);
    bool attackResult = attacker.attemptAttack(t, g1);
    EXPECT_TRUE(attackResult);
    EXPECT_EQ(t->getHP(), 60);
}

TEST(FighterTest, AttemptAttackFailed) {
    auto g1 = std::make_shared<Gun>("gun", 40, 15, 5, 0);
    std::vector<std::shared_ptr<Weapon>> equipment;
    equipment.push_back(g1);
    Fighter attacker("Attacker", 100, 100, 10, 5, equipment, {0, 0}, 20);
    Fighter target("Target", 100, 100, 10, 5, {}, {5, 5}, 20);

    bool attackResult = attacker.attemptAttack(std::make_shared<Fighter>(target), g1);

    EXPECT_FALSE(attackResult);
    EXPECT_EQ(target.getHP(), 100);
}

TEST(FighterTest, GetMostPowerfulWeapon) {
    auto g1 = std::make_shared<Gun>("gun", 40, 15, 5, 0);
    auto g2 = std::make_shared<Gun>("gun", 10, 15, 5, 0);
    auto g3 = std::make_shared<Gun>("gun", 100, 15, 5, 0);
    Fighter fighter("TestFighter", 100, 100, 10, 5, {g1, g2, g3}, {0, 0}, 20);

    std::shared_ptr<Weapon> mostPowerfulWeapon = fighter.getMostPowerfulWeapon();

    EXPECT_EQ(mostPowerfulWeapon, g3);
}

// ECHELON TESTS
TEST(EchelonTest, AddAndRemoveFighter) {
    Echelon echelon;
    Fighter fighter1("fighter1", 100, 100, 10, 5, {}, {5, 5}, 20);
    Fighter fighter2("fighter2", 100, 100, 10, 5, {}, {5, 5}, 20);
    auto f1 = std::make_shared<Fighter>(fighter1);
    auto f2 = std::make_shared<Fighter>(fighter2);
    echelon.addFighter(f1);
    echelon.addFighter(f2);
    EXPECT_EQ(echelon.getNumFighters(), 2);
    echelon.removeFighter(0);
    EXPECT_EQ(echelon.getNumFighters(), 1);
}

TEST(EchelonTest, DetectionRadiusEmptyEchelon) {
    Echelon echelon;
    int detectionRadius = echelon.getEchelonDetectionRadius();
    EXPECT_EQ(detectionRadius, 0);
}

TEST(EchelonTest, DetectionRadiusNonEmptyEchelon) {
    Echelon echelon;
    Fighter fighter1("fighter1", 100, 100, 10, 5, {}, {5, 5}, 20);
    Fighter fighter2("fighter2", 100, 100, 15, 5, {}, {5, 5}, 30);
    echelon.addFighter(std::make_shared<Fighter>(fighter1));
    echelon.addFighter(std::make_shared<Fighter>(fighter2));
    int detectionRadius = echelon.getEchelonDetectionRadius();
    EXPECT_EQ(detectionRadius, 30);
}

TEST(EchelonTest, SimulateAirRaid) {
    Echelon attackerEchelon;
    Echelon targetEchelon;
    auto g1 = std::make_shared<Gun>("gun", 40, 15, 5, 0);
    Fighter attacker("attacker", 100, 100, 10, 5, {g1}, {0, 0}, 20);
    Fighter target("target", 100, 100, 15, 5, {g1}, {10, 10}, 30);
    attackerEchelon.addFighter(std::make_shared<Fighter>(attacker));
    targetEchelon.addFighter(std::make_shared<Fighter>(target));

    std::vector<Bullet> bullets;
    attackerEchelon.simulateAirRaid(targetEchelon, bullets);
    EXPECT_EQ(attacker.getHP(), 100);
}

TEST(EchelonTest, AreAllFightersDead) {
    Echelon echelon;
    Fighter fighter1("fighter1", 0, 100, 10, 5, {}, {5, 5}, 20); // Dead fighter
    Fighter fighter2("fighter2", 50, 100, 15, 5, {}, {5, 5}, 30); // Alive fighter
    echelon.addFighter(std::make_shared<Fighter>(fighter1));
    echelon.addFighter(std::make_shared<Fighter>(fighter2));

    bool allDead = echelon.areAllFightersDead();

    EXPECT_FALSE(allDead);
}

// ROCKET AND GUN TESTS
TEST(RocketTest, Fire) {
    RocketLauncher rocket1("rocket", 40, 15, 5, 50, 200);
    Projectile prg = rocket1.fire();
    EXPECT_EQ(prg.getWeaponType(), WeaponType::ROCKET);
}

TEST(GunTest, Fire){
    Gun gun1("gun", 40, 15, 5, 50);
    Projectile prg = gun1.fire();
    EXPECT_EQ(prg.getWeaponType(), WeaponType::GUN);
}

// TEMPLATE TABLE
TEST(TableTest, AddItem) {
    Table<int> table;
    std::unique_ptr<int> item = std::make_unique<int>(42);
    const std::string callSign = "ABC";

    table.addItem(std::move(item), callSign);

    EXPECT_EQ(table.getCount(), 1);
}

TEST(TableTest, RemoveItem) {
    Table<int> table;
    std::unique_ptr<int> item = std::make_unique<int>(42);
    const std::string callSign = "ABC";
    table.addItem(std::move(item), callSign);

    table.removeItem(callSign);

    EXPECT_EQ(table.getCount(), 0);
}

TEST(TableTest, GetItemByCallSign) {
    Table<int> table;
    std::unique_ptr<int> item = std::make_unique<int>(42);
    const std::string callSign = "ABC";
    table.addItem(std::move(item), callSign);

    auto retrievedItem = table.getEchelonByCallSign(callSign);

    EXPECT_NE(retrievedItem, nullptr);
    EXPECT_EQ(*retrievedItem, 42);
}

TEST(TableTest, IterateTable) {
    Table<int> table;
    std::unique_ptr<int> item1 = std::make_unique<int>(42);
    std::unique_ptr<int> item2 = std::make_unique<int>(77);
    table.addItem(std::move(item1), "ABC");
    table.addItem(std::move(item2), "XYZ");
    int count = 0;
    for (const auto &entry : table) {
        ++count;
    }
    EXPECT_EQ(count, 2);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
