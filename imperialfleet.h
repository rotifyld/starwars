#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"

#include <cassert>
#include <type_traits>

template<typename U> // todo
class ImperialStarship {
    U shield;
    U attackPower;

public:
    using valueType = U;

    ImperialStarship(const U shield, const U attackPower)
            : shield(shield), attackPower(attackPower) {
    }

    U getShield() const { return shield; }

    U getAttackPower() const { return attackPower; }

    void takeDamage(const U damage) {
        if (damage > shield) {
            shield = U{0};
        } else {
            shield -= damage;
        }

    }
};

template <typename I, typename R>
void attack(I &imperialShip, R &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

template <typename I, typename R>
void attack(I &imperialShip, Explorer<R> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;


#endif //STARWARS_IMPERIALFLEET_H