#include "../src/items/Weapon.h"
#include "../src/entities/Player.h"
#include "../src/items/HealthPotion.h"
#include <gtest/gtest.h>
#include <memory>
#include <typeinfo>

TEST(ItemUsabilityTest, WeaponUsage) {
    Weapon sword("Sword", "Sharp sword", 15, 10);
    EXPECT_EQ(sword.getName(), "Sword");
    EXPECT_EQ(sword.getDamage(), 15);
    Player player("Test player");
    player.equipWeapon(std::make_shared<Weapon>(sword));
    EXPECT_GT(player.getAttack(), 15);
}

TEST(ItemUsabilityTest, HealthPotionUsage) {
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
