#include "../src/items/Weapon.h"
#include "../src/entities/Player.h"
#include "../src/items/HealthPotion.h"
#include <gtest/gtest.h>
#include <memory>
#include <typeinfo>

// Test Weapon usage with edge cases and proper validation
TEST(ItemsTests, WeaponUsage) {
    Weapon sword("Sword", "Sharp sword", 15, 10);
    EXPECT_EQ(sword.getName(), "Sword");
    EXPECT_EQ(sword.getDamage(), 15);
    Player player("Test player");
    player.equipWeapon(std::make_shared<Weapon>(sword));
    EXPECT_GT(player.getAttack(), 15);
}

// Test Weapon usage edge cases - invalid weapon usage
TEST(ItemsTests, WeaponUsageEdgeCases) {
    Weapon sword("Sword", "Sharp sword", 15, 10);
    Player player("Test player");
    EXPECT_EQ(sword.getName(), "Sword");
    EXPECT_EQ(sword.getDamage(), 15);
    player.equipWeapon(std::make_shared<Weapon>(sword));
    int attackAfterFirstEquip = player.getAttack();
    player.equipWeapon(std::make_shared<Weapon>(sword));
    EXPECT_EQ(player.getAttack(), attackAfterFirstEquip);
}

// Test HealthPotion usage with edge cases and proper validation
TEST(ItemsTests, HealthPotionUsage) {
    HealthPotion potion;
    Player player("Test player");
    int initialHealth = player.getHealth();
    int damage = 20;
    player.takeDamage(damage);
    EXPECT_LT(player.getHealth(), initialHealth);
    potion.use(player);
    EXPECT_GE(player.getHealth(), initialHealth - damage);
    EXPECT_LE(player.getHealth(), player.getMaxHealth());
    EXPECT_GT(potion.getHealAmount(), 0);
}

// Test HealthPotion usage edge case - already full health
TEST(ItemsTests, HealthPotionAlreadyFullHealth) {
    Player player("Test player");
    int maxHealth = player.getMaxHealth();
    EXPECT_EQ(player.getHealth(), player.getMaxHealth());
    HealthPotion potion;
    potion.use(player);
    EXPECT_LE(player.getHealth(), maxHealth);
    EXPECT_EQ(player.getHealth(), maxHealth);
}

// Test edge case - weapon with negative damage (should be handled properly)
TEST(ItemsTests, WeaponNegativeDamage) {
    Weapon sword("Sword", "Sharp sword", -5, 10);
    Player player("Test player");
    player.equipWeapon(std::make_shared<Weapon>(sword));
    EXPECT_GE(player.getAttack(), 0);
}

// Test Weapon and HealthPotion together
TEST(ItemsTests, WeaponAndHealthPotionCombined) {
    Weapon sword("Sword", "Sharp sword", 15, 10);
    HealthPotion potion;
    Player player("Test player");
    player.equipWeapon(std::make_shared<Weapon>(sword));
    player.takeDamage(20);
    potion.use(player);
    EXPECT_LE(player.getHealth(), player.getMaxHealth());
    EXPECT_GT(player.getAttack(), 15); // Should include weapon damage
}