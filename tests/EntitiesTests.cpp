#include "../src/entities/Player.h"
#include "../src/entities/Enemy.h"
#include "../src/common/Logger.h"
#include <gtest/gtest.h>
#include <memory>
#include <typeinfo>

TEST(EntitiesTests, PlayerInitialization) {
    Player player("Test player");
    EXPECT_GT(player.getHealth(), 0);
    EXPECT_GT(player.getMaxHealth(), 0);
    EXPECT_GE(player.getAttack(), 0);
}

TEST(EntitiesTests, EnemyDamage) {
    Player player("Test player");
    Enemy goblin("Goblin", 1, 20, 5, 2, 10);
    int initialHealth = player.getHealth();
    goblin.attackTarget(player);
    int expectedMinDamage = 1;
    int expectedMaxDamage = goblin.getAttack() - (player.getDefense() / 2);
    EXPECT_LT(player.getHealth(), initialHealth);
    EXPECT_GE(player.getHealth(), initialHealth - expectedMaxDamage);
    EXPECT_LE(player.getHealth(), initialHealth - expectedMinDamage);
    
    if (player.getHealth() > 0) EXPECT_TRUE(player.isAlive());
    
    while (goblin.isAlive()) player.attackTarget(goblin);
    EXPECT_FALSE(goblin.isAlive());
}

TEST(EntitiesTests, PlayerHealing) {
    Player player("Test player");
    int initialMaxHealth = player.getMaxHealth();
    
    player.takeDamage(10);
    int damagedHealth = player.getHealth();
    EXPECT_LT(damagedHealth, initialMaxHealth);
    
    int healAmount = 5;
    player.heal(healAmount);
    EXPECT_EQ(player.getHealth(), damagedHealth + healAmount);
}

TEST(EntitiesTests, PlayerDeath) {
    Player player("Test player");
    player.takeDamage(player.getHealth());
    EXPECT_FALSE(player.isAlive());
}

