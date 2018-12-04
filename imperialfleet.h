#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"

/**
 * Class representing imperial starship.
 * @tparam U - type of fields storing shield, speed, and attackPower.
 */
template<typename U>
class ImperialStarship {

    /// Amount of shield that the ship contains. If shield <= 0 then the ship is
    /// considered to be destroyed.
    U shield;

    /// Ship's attack power. This field is not used if @tparam canAttack == false.
    U attackPower;

    /// Denotes if given ship is considered alive. @param alive == (@param shield > 0).
    bool alive;

public:

    /// Denotes that the ship is indeed imperial.
    static constexpr bool isImperial = true;

    /// Component representing type of the parameter @tparam U.
    using valueType = U;

    /**
     * Default constructor
     * @param shield - initial value of ship's shield.
     * @param attackPower - initial value of ship's attack power.
     */
    ImperialStarship(const U shield, const U attackPower)
            : shield(shield), attackPower(attackPower), alive(shield > 0) {
    }

    /**
     * Getter to the ship's shield value.
     * @return ship's shield.
     */
    U getShield() const { return shield; }

    /**
     * Getter to the ship's attack power value.
     * @return ship's attack power.
     */
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

/**
 * One of the helper functions to the @fn attack() function.
 * Here, first special case is considered, where both ships are Imperial - then nothing happens.
 * Casting to void are artificial commands to avoid compiler warnings.
 * @tparam U1 - first imperial ship's U parameter.
 * @tparam U2 - second imperial ship's U parameter
 * @param ship1 - first imperial ship.
 * @param ship2 - second imperial ship.
 */
template<typename U1, typename U2>
void performAttack(ImperialStarship<U1> &ship1, ImperialStarship<U2> &ship2) {
    (void) ship1;
    (void) ship2;
}

/**
 * One of the helper functions to the @fn attack() function.
 * In second special case, first ship is and imperial ship and the second is Explorer - thus the
 * only rebel ship that cannot attack. Then only imperial ship deals damage.
 * @tparam U1 - imperial ship's U parameter.
 * @tparam U2 - Explorer's U parameter
 * @param imperial - attacking imperial ship.
 * @param explorer - attacked Explorer.
 */
template<typename U1, typename U2>
void performAttack(ImperialStarship<U1> &imperial, Explorer<U2> &explorer) {
    explorer.takeDamage(imperial.getAttackPower());
}

/**
 * One of the helper functions to the @fn attack() function.
 * In third case, first ship is and imperial ship and the second is rebel ship that can attack.
 * As typename R allows any type to get in here, we depend on first two functions to process
 * edge cases and thus only allow here desired ships. Attack is executed two-way.
 * @tparam U1 - imperial ship's U parameter.
 * @tparam R - rebel ship's type
 * @param imperial - attacking imperial ship.
 * @param rebel - attacked rebel ship that can attack.
 */
template<typename U, typename R>
void performAttack(ImperialStarship<U> &imperial, R &rebel) {
    rebel.takeDamage(imperial.getAttackPower());
    imperial.takeDamage(rebel.getAttackPower());
}

/**
 * One of the helper functions to the @fn attack() function.
 * In final case, the @fn attack() function's call was not captured by ay of the above cases.
 * Thus we can either have an rebel ship on both sides of an attack or rebel ship trying to attack
 * imperial ship - both of which cases are not allowed. Thus nothing happens.
 * Casting to void are artificial commands to avoid compiler warnings.
 * @tparam S1 - first ship's type.
 * @tparam S2 - second ship's type.
 * @param ship1 - first ship.
 * @param ship2 - second ship.
 */
template<typename S1, typename S2>
void performAttack(S1 &ship1, S2 &ship2) {
    (void) ship1;
    (void) ship2;
}

/**
 * Disambiguating function that takes two ships as an argument and iff first one is a RebelShip and
 * second ImperialShip performs an attack. Type check is made via auto type matching to one of the
 * helper functions @fn performAttack().
 * @tparam S1 - first ship's type.
 * @tparam S2 - second ship's type.
 * @param ship1 - first ship.
 * @param ship2 - second ship.
 */
template<typename S1, typename S2>
void attack(S1 &ship1, S2 &ship2) {
    performAttack(ship1, ship2);
}

/// Defines TIEFighter ship as a specialization of the ImperialShip class
template<typename U>
using DeathStar = ImperialStarship<U>;

/// Defines TIEFighter ship as a specialization of the ImperialShip class
template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

/// Defines TIEFighter ship as a specialization of the ImperialShip class
template<typename U>
using TIEFighter = ImperialStarship<U>;


#endif //STARWARS_IMPERIALFLEET_H