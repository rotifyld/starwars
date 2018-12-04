#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include "imperialfleet.h"
#include "rebelfleet.h"

#include <iostream>
#include <tuple>
#include <algorithm>

/**
 * Class representing battle between forces of Empire and Rebellion.
 * @tparam T - type representing time point.
 * @tparam t0 - variable representing beginning battle time.
 * @tparam t1 - variable representing end of cycle in which we measure time.
 * @tparam S - represents various ships of both sides of the conflict.
 */
template<typename T, T t0, T t1, typename ...S>
class SpaceBattle {

    /// Tuple containing ships of both sides of the conflict.
    std::tuple<S...> ships;

    /// Number of imperial ships (that are currently alive).
    size_t imperialFleet;

    /// Number of rebel ships (that are currently alive).
    size_t rebelFleet;

    /// Variable that stores current interstellar time.
    T actualTime;

    /**
     * Function comparing square root of t1, which (floor) is equal to numbers of square
     * seconds
     * between 0 and t1. We iterate from 0 up to first second which square is greater
     * than t1.
     * @tparam i - current index in loop.
     * @tparam i_sq - square of i.
     * @return - number of square seconds between 0 and t1.
     */
    template<T i = 0, T i_sq = 0>
    static constexpr size_t sqrt_t1() {
        if constexpr (i_sq < t1) {
            return sqrt_t1<i + 1, i_sq + (2 * i) + 1>();
        } else {
            return static_cast<size_t>(i);
        }
    }

    /// Variable representing size of an array containing square seconds - times of attacks.
    static constexpr size_t attackTimesSize = sqrt_t1();

    /**
     * Function filling an array with square seconds - times of attacks.
     * Fills the array via iterating over all seconds from 0 to number of attack Times (which is
     * equal to floor of square root of t1).
     * @tparam i - index in loop.
     * @tparam i_sq - square of i.
     * @param times - aray of square seconds.
     * @return - the array filled with square seconds.
     */
    template<T i = 0, T i_sq = 0>
    static constexpr std::array<T, attackTimesSize>
    countAttackTimes(std::array<T, attackTimesSize> times) {
        if constexpr (i_sq < t1) {
            times[static_cast<size_t>(i)] = i_sq;
            return countAttackTimes<i + 1, i_sq + (2 * i) + 1>(times);
        }
        return times;
    }

    /// Variable which is the container for square seconds.
    static constexpr std::array<T, attackTimesSize> attackTimes = countAttackTimes(
            std::array<T, attackTimesSize>{});

    /**
     * Function that iterates through every ship in tuple ships and counts how many rebel and
     * and how many imperial ships are alive.
     * @tparam n - current index in tuple.
     */
    template<size_t n = 0>
    void iterateCountShips() {
        if constexpr(n < sizeof...(S)) {
            auto ship = std::get<n>(ships);
            if (ship.isImperial) {
                if (ship.isAlive()) imperialFleet++;
            } else {
                if (ship.isAlive()) rebelFleet++;
            }
            iterateCountShips<n + 1>();
        }
    }

    /**
     * Function that finds imperial ships in tuple of ships and then searches for rebel ships
     * to battle.
     * @tparam n - current index in tuple.
     */
    template<size_t n = 0>
    void iterateFindImperial() {
        if constexpr (n < sizeof ...(S)) {
            auto &ship = std::get<n>(ships);
            if (ship.isImperial) {
                iterateFindRebel<>(ship);
            }
            iterateFindImperial<n + 1>();
        }
    }

    /**
     * Function that gets an imperial ship and finds a rebel one to battle with
     * by iterating through tuple of ships.
     * @tparam n - current index in tuple.
     * @tparam Imperial - type of the imperial ship.
     * @param attacker - imperial ship that's going to attack a rebel ship.
     */
    template<size_t n = 0, typename Imperial>
    void iterateFindRebel(Imperial &attacker) {
        if constexpr(n < sizeof...(S)) {
            auto &ship = std::get<n>(ships);
            if (!ship.isImperial) {
                if (attacker.isAlive() && ship.isAlive()) {
                    attack(attacker, ship);
                    if (!attacker.isAlive()) imperialFleet--;
                    if (!ship.isAlive()) rebelFleet--;
                }
            }
            iterateFindRebel<n + 1>(attacker);
        }
    }

    /**
     * Function that checks whether given second t is a square.
     * It checks that by finding whether array with square seconds contains given t.
     * @param t - second we want to check.
     * @return - true if t is a square second, false otherwise.
     */
    bool isASquareTime(const T t) const {
        return std::binary_search(attackTimes.cbegin(), attackTimes.cend(), t);
    }

public:

    /**
     * SpaceBattle constructor - it takes various ships, initializes t0 and t1,
     * checks whether they're valid in compile time
     * and counts alive ships in rebel and imperial fleets.
     * @param s - variable representing ships of both fleets.
     */
    explicit SpaceBattle(const S &... s) : ships(s...), actualTime(t0) {
        static_assert(t1 > T{0}, "t1 must be bigger than 0.");
        static_assert(t0 >= T{0} && t0 < t1, "t0 must be within [0, t1) range.");

        imperialFleet = 0;
        rebelFleet = 0;
        iterateCountShips<0>();
    };

    /// Function that returns number of alive imperial ships at the moment.
    size_t countImperialFleet() const { return imperialFleet; };

    /// Function that returns number of alive rebel ships at the moment.
    size_t countRebelFleet() const { return rebelFleet; };

    /**
     * Function that checks whether battle is over;
     * if not, it checks whether it's time of attack (if so - the attack occurs).
     * At last it adds timeStep to actualTime (to represent passing time).
     * @param timeStep - variable representing time difference.
     */
    void tick(const T &timeStep) {
        if (imperialFleet == 0 && rebelFleet == 0) {
            std::cout << "DRAW\n";
        } else if (imperialFleet == 0) {
            std::cout << "REBELLION WON\n";
        } else if (rebelFleet == 0) {
            std::cout << "IMPERIUM WON\n";
        } else {
            if (isASquareTime(actualTime)) {
                iterateFindImperial();
            }
            actualTime = (actualTime + timeStep) % t1;
        }
    };
};


#endif //STARWARS_BATTLE_H
