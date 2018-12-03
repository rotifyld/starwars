#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"

#include <type_traits>

template<typename U>
class ImperialStarship {
    U shield;
    U attackPower;
    bool alive;

public:
    static constexpr bool isImperial = true;

    using valueType = U;

    ImperialStarship(const U shield, const U attackPower)
            : shield(shield), attackPower(attackPower), alive(shield > 0) {
    }

    U getShield() const { return shield; }

    U getAttackPower() const { return attackPower; }

    bool isAlive() { return alive; }

    void takeDamage(const U damage) {
        if (damage >= shield) {
            shield = U{0};
            alive = false;
        } else {
            shield -= damage;
        }
    }
};

template <typename I, typename T>
void attack(I &imperialShip, Explorer<T> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template <typename I, typename R>
void attack(I &imperialShip, R &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;


#endif //STARWARS_IMPERIALFLEET_H