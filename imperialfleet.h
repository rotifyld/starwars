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

//template<typename T1, typename T2>
//void attack(T1 &ship1, T2& ship2)
//{
//    if(ship1.isImperial && !ship2.isImperial) {
//        ship2.takeDamage(ship1.getAttackPower());
//        ship1.takeDamage(ship2.getAttackPower());
//    }
//}

template <typename T1, typename T2>
void attack(T1 ship1, T2 ship2) {
    (void)ship1;
    (void)ship2;
}

template <typename T1, typename T2>
void attack(ImperialStarship<T1> ship1, ImperialStarship<T2> ship2) {
    (void)ship1;
    (void)ship2;
}

template <typename T1, typename T2>
void attack(ImperialStarship<T2>& imperialShip, T1& rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

template <typename I, typename T>
void attack(ImperialStarship<I> &imperialShip, Explorer<T> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;


#endif //STARWARS_IMPERIALFLEET_H