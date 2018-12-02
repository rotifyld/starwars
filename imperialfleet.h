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
    bool isImperial() { return true; };

    using valueType = U;

    ImperialStarship(const U shield, const U attackPower)
            : shield(shield), attackPower(attackPower), alive(shield != 0) {
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

template<typename U1, typename U2>
void attack(ImperialStarship<U1> &imperialShip, Explorer<U2> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template<typename U1, typename U2>
void attack(ImperialStarship<U1> &imperialShip, StarCruiser<U2> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

template<typename U1, typename U2>
void attack(ImperialStarship<U1> &imperialShip, XWing<U2> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

template<typename S1, typename S2>
void attack(S1 &ship1, S2 &ship2) {
    (void) ship1;
    (void) ship2;
}

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;


#endif //STARWARS_IMPERIALFLEET_H