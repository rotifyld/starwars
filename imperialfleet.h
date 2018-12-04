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

    bool isAlive() const { return alive; }

    void takeDamage(const U damage) {
        if (damage >= shield) {
            shield = U{0};
            alive = false;
        } else {
            shield -= damage;
        }
    }
};

//template<typename S1, typename S2, bool attack, bool attackBack>
//void performAttack(S1 &ship1, S2 &ship2) {
//    if constexpr (attack)       ship2.takeDamage(ship1.getAttackPower());
//    if constexpr (attackBack)   ship1.takeDamage(ship2.getAttackPower());
//}

//template <typename U1, typename U2>
//using attack<ImperialStarship<int>, RebelStarship<int>>() = performAttack<U1, U2, true, true>();


template<typename S1, typename S2>
void performAttack(S1 &ship1, S2 &ship2) {
    (void) ship1;
    (void) ship2;
}

template<typename U1, typename U2>
void performAttack(ImperialStarship<U1> &ship1, ImperialStarship<U2> &ship2) {
    (void) ship1;
    (void) ship2;
}

template<typename U, typename R>
void performAttack(ImperialStarship<U> &imperialShip, R &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

template<typename U1, typename U2>
void performAttack(ImperialStarship<U1> &imperialShip, Explorer<U2> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template<typename S1, typename S2>
void attack(S1 &ship1, S2 &ship2) {
    performAttack(ship1, ship2);
}

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;


#endif //STARWARS_IMPERIALFLEET_H