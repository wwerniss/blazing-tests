#include <gtest/gtest.h>
#include "../src/world/WorldMap.h"
#include "../src/world/LocationNode.h"
#include "../src/entities/Enemy.h"
#include "../src/items/HealthPotion.h"
#include <memory>

TEST(WorldTest, TestLocationNodeInitialization) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    LocationNode* node1 = world->getCurrentLocation();
    EXPECT_EQ(node1->getName(), "Село");
    EXPECT_FALSE(node1->hasEnemies());
}

TEST(WorldTest, TestWorldMapInitialization) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    LocationNode* start = world->getCurrentLocation();
    EXPECT_NE(start, nullptr);
    EXPECT_FALSE(start->getName().empty());
}

TEST(WorldTest, TestWorldMapNavigation) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    LocationNode* start = world->getCurrentLocation();
    world->moveRight();
    EXPECT_NE(world->getCurrentLocation(), start);
    world->moveLeft();
    EXPECT_EQ(world->getCurrentLocation(), start);
}

TEST(WorldTest, TestEnemyManagement) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    world->moveLeft();
    LocationNode* node1 = world->getCurrentLocation();
    EXPECT_TRUE(node1->getEnemies().size() > 0);
    size_t initialCount = node1->getEnemies().size();
    node1->removeEnemy(0);
    EXPECT_EQ(node1->getEnemies().size(), initialCount - 1);
}

TEST(WorldTest, TestLocationConnections) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    LocationNode* node1 = world->getCurrentLocation();
    world->moveLeft();
    LocationNode* node2 = world->getCurrentLocation();
    world->moveLeft();
    LocationNode* node3 = world->getCurrentLocation();
    EXPECT_EQ(node1->getLeft(), node2);
    EXPECT_EQ(node2->getLeft(), node3);
    EXPECT_EQ(node3->getRight(), node2);
}

TEST(WorldDestructionTest, TestWorldCleanup) {
    {
        WorldMap worldMap;
        // WorldMap and its nodes will be destroyed when going out of scope
    }
    // If we get here without memory leaks, the test passes
    SUCCEED();
}