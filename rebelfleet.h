#ifndef STARWARS_REBELFLEET_H
#define STARWARS_REBELFLEET_H

#include <cassert>
#include <type_traits>

/**
 * Class representing rebellian starship.
 * @tparam U - type of fields storing shield, speed, and attackPower.
 * @tparam minSpeed - minimal amount of speed that given type of starship must have.
 *                                      (defined in usings at the end of the file)
 * @tparam maxSpeed - minimal amount of speed that given type of starship must have.
 * @tparam canAttack - whether the given type of starship is able to attack.
 *                                      (see: usings at the end of the file)
 */
template<typename U, int minSpeed, int maxSpeed, bool canAttack>
class RebelStarship {

    /// Amount of shield that the ship contains. If shield <= 0 then the ship is
    /// considered to be destroyed.
    U shield;

    /// Ship's speed.
    U speed;

    /// Ship's attack power. This field is not used if @tparam canAttack == false.
    U attackPower;

    /// Denotes if given ship is considered alive. @param alive == (@param shield > 0).
    bool alive;

    /// Asserts that the speed given by the user in constructor is adequate to the ships type.
    void assert_speed() const {
        assert(speed >= static_cast<U>(minSpeed) && speed <= static_cast<U>(maxSpeed) &&
               "Given speed is not within a range of the starship.");
    }

public:

    /// Denotes that the ship is indeed not imperial.
    static constexpr bool isImperial = false;

    /// Component representing type of the parameter @tparam U.
    using valueType = U;

    /**
     * Two-parameter variant of a constructor enabled for types of ships that cannot attack.
     * @tparam b - enables constructor iff ship cannot attack.
     * @param shield - initial value of ship's shield.
     * @param speed - initial value of ship's speed.
     */
    template<bool b = !canAttack, typename = typename std::enable_if<b>::type>
    RebelStarship(const U shield, const U speed)
            : shield(shield), speed(speed), alive(shield > 0) {
        assert_speed();
    }

    /**
     * Three-parameter variant of a constructor enabled for types of ships that can attack.
     * @tparam b - enables constructor iff ship can attack.
     * @param shield - initial value of ship's shield.
     * @param speed - initial value of ship's speed.
     * @param attackPower - initial value of ship's attack power.
     */
    template<bool b = canAttack, typename = typename std::enable_if<b>::type>
    RebelStarship(const U shield, const U speed, const U attackPower)
            : shield(shield), speed(speed), attackPower(attackPower), alive(shield > 0) {
        assert_speed();
    }

    /**
     * Getter to the ship's shield value.
     * @return ship's shield.
     */
    U getShield() const { return shield; }

    /**
     * Getter to the ship's speed value.
     * @return ship's speed.
     */
    U getSpeed() const { return speed; }

    /**
     * Getter to the ship's attackPower value.
     * @tparam b - enables getter iff ship can attack.
     * @return ship's attack power.
     */
    template<bool b = canAttack, typename = typename std::enable_if<b>::type>
    U getAttackPower() const { return attackPower; }

    /**
     * Getter to the ship's alive value.
     * @return true - if ship is alive, false otherwise.
     */
    bool isAlive() const { return alive; }

    /**
     * Simulates being hit with a missile of a power @param damage. If damage > shield sets
     * its value to 0 and denotes that the ship is dead.
     * @param damage - damage took.
     */
    void takeDamage(const U damage) {
        if (damage >= shield) {
            shield = U{0};
            alive = false;
        } else {
            shield -= damage;
        }
    }
};

/// Defines Explorer ship as a specialization of the RebelStarship class
/// with speed in range [299796, 2997960] and that cannot attack.
template<typename U>
using Explorer = RebelStarship<U, 299796, 2997960, false>;

/// Defines StarCruiser ship as a specialization of the RebelStarship class
/// with speed in range [99999, 299795] and that can attack.
template<typename U>
using StarCruiser = RebelStarship<U, 99999, 299795, true>;

/// Defines XWing ship as a specialization of the RebelStarship class
/// with speed in range [299796, 2997960] and that can attack.
template<typename U>
using XWing = RebelStarship<U, 299796, 2997960, true>;

#endif //STARWARS_REBELFLEET_H