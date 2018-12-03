#ifndef STARWARS_REBELFLEET_H
#define STARWARS_REBELFLEET_H

#include <cassert>
#include <type_traits>

template<typename U, int minSpeed, int maxSpeed, bool canAttack>
class RebelStarship {
    U shield;
    U speed;
    U attackPower;
    bool alive;

    void assert_speed() const {
        assert(speed >= static_cast<U>(minSpeed) && speed <= static_cast<U>(maxSpeed) &&
               "Given speed is not within a range of chosen starship.");
    }

public:
    static constexpr bool isImperial = false;

    using valueType = U;

    template<bool b = !canAttack, typename = typename std::enable_if<b>::type>
    RebelStarship(const U shield, const U speed)
            : shield(shield), speed(speed), alive(shield != 0) {
        assert_speed();
    }

    template<bool b = canAttack, typename = typename std::enable_if<b>::type>
    RebelStarship(const U shield, const U speed, const U attackPower)
            : shield(shield), speed(speed), attackPower(attackPower), alive(shield != 0) {
        assert_speed();
    }

    U getShield() const { return shield; }

    U getSpeed() const { return speed; }

    template<bool b = canAttack, typename = typename std::enable_if<b>::type>
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

template<typename U>
using Explorer = RebelStarship<U, 299796, 2997960, false>;

template<typename U>
using StarCruiser = RebelStarship<U, 99999, 299795, true>;

template<typename U>
using XWing = RebelStarship<U, 299796, 2997960, true>;

#endif //STARWARS_REBELFLEET_H