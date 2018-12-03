#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

/** todo pytania
 *
 * countAttackTimes(std::vector<T> times)
 *                                ^ & czy nie &
 *
 * konstruktor explicit
 *
 * assert shield, attack, itd.
 *
 * valueType?
 */

#include "imperialfleet.h"
#include "rebelfleet.h"

#include <tuple>
#include <iostream>
#include <unordered_set>
#include <vector>

template<typename T, T t0, T t1, typename ...S>
class SpaceBattle {
    std::tuple<S...> ships;
    size_t imperialFleet;
    size_t rebelFleet;
    std::vector<size_t> imperialIndices;
    std::vector<size_t> rebelIndices;
    T actualTime;

    template<T i = 0, T i_sq = 0>
    static constexpr size_t sqrt_t1() {
        if constexpr (i_sq < t1) {
            return sqrt_t1<i + 1, i_sq + (2 * i) + 1>();
        } else {
            return static_cast<size_t>(i);
        }
    }

    static constexpr size_t attackTimesSize = sqrt_t1();

    template<T i = 0, T i_sq = 0>
    static constexpr std::array<T, attackTimesSize> countAttackTimes(std::array<T, attackTimesSize> times) {
        if constexpr (i_sq < t1) {
            times[static_cast<size_t>(i)] = i_sq;
            return countAttackTimes<i + 1, i_sq + (2 * i) + 1>(times);
        }
        return times;
    }

    static constexpr std::array<T, attackTimesSize> attackTimes = countAttackTimes(
            std::array<T, attackTimesSize>{});


    template<size_t n = 0>
    constexpr void iterateCountShips() {
        if constexpr(n < sizeof...(S)) {
            auto ship = std::get<n>(ships);
            if (ship.isImperial) {
                if (ship.isAlive()) {
                    imperialFleet++;
                }
                imperialIndices.push_back(n); // todo
            } else {
                if (ship.isAlive()) {
                    rebelFleet++;
                }
                rebelIndices.push_back(n);
            }
            iterateCountShips<n + 1>();
        }
    }

    template<size_t n = 0, typename Imperial>
    constexpr void iterateFindRebel(Imperial &attacker) {
        if constexpr(n < sizeof...(S)) {
            auto &ship = std::get<n>(ships);
            if (!ship.isImperial) {                             //constexpr
                if (attacker.isAlive() && ship.isAlive()) {
                    attack(attacker, ship);
                    if (!attacker.isAlive()) imperialFleet--;
                    if (!ship.isAlive()) rebelFleet--;
                }
            }
            iterateFindRebel<n + 1>(attacker);
        }
    }

    template<size_t n = 0>
    constexpr void iterateFindImperial() {
        if constexpr (n < sizeof ...(S)) {
            auto &ship = std::get<n>(ships);
            if (ship.isImperial) {
                iterateFindRebel<>(ship);
            }
            iterateFindImperial<n + 1>();
        }
    }

    bool isASquareTime(T t) {
        for (size_t i = 0; i < attackTimesSize; ++i) {
            if (t == attackTimes[i]) {
                return true;
            }
        }
        return false;
    }

public:
    explicit SpaceBattle(const S &... s) : ships(s...), actualTime(t0) {
        static_assert(t1 > T{0}, "t1 must be bigger than 0.");
        static_assert(t0 >= T{0} && t0 < t1, "t0 must be within [0, t1) range.");

        imperialFleet = 0;
        rebelFleet = 0;
        iterateCountShips<0>();
    };

    size_t countImperialFleet() const { return imperialFleet; };

    size_t countRebelFleet() const { return rebelFleet; };

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

//template<typename T, T t0, T t1, typename... S>
//std::array<T, SpaceBattle<T, t0, t1, S ...>::attackTimesSize> SpaceBattle<T, t0, t1, S...>::attackTimes = countAttackTimes(
//        attackTimes);

#endif //STARWARS_BATTLE_H
