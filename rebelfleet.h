#ifndef STARWARS_REBELFLEET_H
#define STARWARS_REBELFLEET_H

#include <cassert>
#include <type_traits>

template<typename U, int minSpeed, int maxSpeed, bool canAttack> // todo
class RebelStarship {
    U shield;
    U speed;
    U attackPower;

    void assert_speed() const {
        assert(speed >= minSpeed && speed <= maxSpeed);
    }

public:

    using valueType = U;

    template<bool b = !canAttack, typename = typename std::enable_if<b>::type>
    RebelStarship(const U shield, const U speed)
            : shield(shield), speed(speed) {
        assert_speed();
    }

    template<bool b = canAttack, typename = typename std::enable_if<b>::type>
    RebelStarship(const U shield, const U speed, const U attackPower)
            : shield(shield), speed(speed), attackPower(attackPower) {
        assert_speed();
    }

    U getShield() const { return shield; }

    U getSpeed() const { return speed; }

    template<bool b = canAttack, typename = typename std::enable_if<b>::type>
    U getAttackPower() const { return attackPower; }

    void takeDamage(const U damage) {
        if (damage > shield) {
            shield = U{0};
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