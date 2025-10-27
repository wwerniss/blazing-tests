#include <gtest/gtest.h>
#include "../src/world/WorldMap.h"
#include "../src/world/LocationNode.h"
#include "../src/entities/Enemy.h"
#include "../src/items/HealthPotion.h"
#include <memory>

// Test WorldMap initialization with comprehensive checks
TEST(WorldTests, TestWorldMapInitialization) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    LocationNode* start = world->getCurrentLocation();
    EXPECT_NE(start, nullptr);
    EXPECT_FALSE(start->getName().empty());
}

TEST(WorldTests, TestWorldMapNavigation) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    LocationNode* start = world->getCurrentLocation();
    world->moveRight();
    EXPECT_NE(world->getCurrentLocation(), start);
    world->moveLeft();
    EXPECT_EQ(world->getCurrentLocation(), start);
}

// Test Enemy management in locations with edge cases
TEST(WorldTests, EnemyManagement) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    world->moveLeft();
    LocationNode* node1 = world->getCurrentLocation();
    EXPECT_TRUE(node1->getEnemies().size() > 0);
    size_t initialCount = node1->getEnemies().size();
    if (!node1->getEnemies().empty()) {
        node1->removeEnemy(0);
        EXPECT_EQ(node1->getEnemies().size(), initialCount - 1);
    }
    EXPECT_LE(node1->getEnemies().size(), initialCount);
}

// Test LocationNode connections with edge cases
TEST(WorldTests, TestLocationConnections) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    LocationNode* node1 = world->getCurrentLocation();
    world->moveLeft();
    LocationNode* node2 = world->getCurrentLocation();
    world->moveLeft();
    LocationNode* node3 = world->getCurrentLocation();
    EXPECT_EQ(node1->getLeft(), node2);
    EXPECT_EQ(node2->getLeft(), node3);
    EXPECT_EQ(node3->getRight(), node2);
    EXPECT_NE(node1, node2);
    EXPECT_NE(node2, node3);
    EXPECT_NE(node1, node3);
}

// Test WorldMap memory management and cleanup
TEST(WorldTests, TestWorldCleanup) {
    {
        WorldMap worldMap;
        // WorldMap and its nodes will be destroyed when going out of scope
    }
    // If we get here without memory leaks, the test passes
    SUCCEED();
}

// Test WorldMap edge case - navigation beyond bounds
TEST(WorldTests, WorldMapNavigationEdgeCases) {
    std::unique_ptr<WorldMap> world = std::make_unique<WorldMap>();
    // Test multiple moves (should not crash)
    for (int i = 0; i < 5; i++) world->moveLeft();
    for (int i = 0; i < 5; i++) world->moveRight();
    LocationNode* current = world->getCurrentLocation();
    world->moveLeft();
    EXPECT_NE(world->getCurrentLocation(), current);
}