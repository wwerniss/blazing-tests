#include "../src/entities/Player.h"
#include "../src/entities/Enemy.h"
#include "../src/common/Logger.h"
#include "../src/items/HealthPotion.h"
#include "../src/items/Weapon.h"
#include <gtest/gtest.h>
#include <memory>
#include <typeinfo>

// Test Player initialization with comprehensive checks
TEST(EntitiesTests, PlayerInitialization) {
    Player player("Test player");
    EXPECT_GT(player.getHealth(), 0);
    EXPECT_GT(player.getMaxHealth(), 0);
    EXPECT_GE(player.getAttack(), 0);
    EXPECT_GT(player.getLevel(), 0);
    EXPECT_GE(player.getExperience(), 0);
    EXPECT_GT(player.getExperienceToNextLevel(), 0);
    EXPECT_EQ(player.getInventory().size(), 0);
    EXPECT_FALSE(player.hasWeaponEquipped());
}

// Test edge cases for EnemyDamage - now properly focused on single responsibility
TEST(EntitiesTests, EnemyDamageWithValidDamage) {
    Player player("Test player");
    Enemy goblin("Goblin", 1, 20, 5, 2, 10);
    int initialHealth = player.getHealth();
    goblin.attackTarget(player);
    EXPECT_LT(player.getHealth(), initialHealth);
    EXPECT_GE(player.getHealth(), 0);
    if (player.getHealth() > 0) EXPECT_TRUE(player.isAlive());
    player.takeDamage(player.getHealth());
    EXPECT_FALSE(player.isAlive());
}

// Test edge cases for EnemyDamage - multiple attacks
TEST(EntitiesTests, EnemyDamageMultipleAttacks) {
    Player player("Test player");
    Enemy goblin("Goblin", 1, 20, 5, 2, 10);
    int damagePerAttack = goblin.getAttack() - (player.getDefense() / 2);
    EXPECT_GT(damagePerAttack, 0);
    while (player.isAlive() && goblin.isAlive()) goblin.attackTarget(player);
    EXPECT_FALSE(player.isAlive());
}

// Test invalid damage inputs - edge case for negative values
TEST(EntitiesTests, PlayerDamageWithNegativeValues) {
    Player player("Test player");
    int initialHealth = player.getHealth();
    int damage = -5;
    player.takeDamage(damage);
    EXPECT_GE(player.getHealth(), initialHealth);
}

// Test healing with edge cases - exceed max health
TEST(EntitiesTests, PlayerHealingExceedsMaxHealth) {
    Player player("Test player");
    player.takeDamage(10);
    int damagedHealth = player.getHealth();
    int healAmount = 20;
    player.heal(healAmount);
    EXPECT_LE(player.getHealth(), player.getMaxHealth());
    EXPECT_GE(player.getHealth(), damagedHealth);
}

// Test player death edge cases
TEST(EntitiesTests, PlayerDeathExactCondition) {
    Player player("Test player");
    int health = player.getHealth();
    int damage = health;
    player.takeDamage(damage);
    EXPECT_FALSE(player.isAlive());
    EXPECT_EQ(player.getHealth(), 0);
}

// Test weapon equipment edge cases
TEST(EntitiesTests, PlayerWeaponEquipping) {
    Player player("Test player");
    EXPECT_FALSE(player.hasWeaponEquipped());
    Weapon sword("Sword", "Sharp sword", 15, 10);
    player.equipWeapon(std::make_shared<Weapon>(sword));
    EXPECT_TRUE(player.hasWeaponEquipped());
    EXPECT_GT(player.getAttack(), 15); // Base attack should be higher than weapon damage alone
}

// Test inventory management edge cases
TEST(EntitiesTests, PlayerInventoryManagement) {
    Player player("Test player");
    EXPECT_EQ(player.getInventory().size(), 0);
    HealthPotion potion;
    player.addItem(std::make_shared<HealthPotion>(potion));
    EXPECT_EQ(player.getInventory().size(), 1);
    player.useItem(0); 
    EXPECT_EQ(player.getInventory().size(), 0);
}

// Test Player level up edge cases
TEST(EntitiesTests, PlayerLevelUpEdgeCases) {
    Player player("Test player");
    int initialLevel = player.getLevel();
    int initialMaxHealth = player.getMaxHealth();
    int initialAttack = player.getAttack();
    int initialDefense = player.getDefense();
    player.gainExperience(100);  // Should trigger level up
    EXPECT_GT(player.getLevel(), initialLevel);
    EXPECT_GT(player.getMaxHealth(), initialMaxHealth);
    EXPECT_GT(player.getAttack(), initialAttack);
    EXPECT_GT(player.getDefense(), initialDefense);
    EXPECT_LE(player.getExperience(), player.getExperienceToNextLevel());
}

// Test edge case - invalid item index usage
TEST(EntitiesTests, PlayerInvalidItemIndex) {
    Player player("Test player");
    player.useItem(999);  // Invalid index
    EXPECT_TRUE(player.isAlive());
}

