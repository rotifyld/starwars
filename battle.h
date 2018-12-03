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
 */

/**
 * todo
 *
 * odpowiedź z moodle'a shield == 0
 */

#include "imperialfleet.h"
#include "rebelfleet.h"

#include <tuple>
#include <iostream>
#include <unordered_set>

template<typename T, T t0, T t1, typename ...S>
class SpaceBattle {
    std::tuple<S...> ships;
    size_t imperialFleet;
    size_t rebelFleet;
    T actualTime;

    static std::unordered_set<T> attackTimes;

    template<T t = 0>
    static constexpr std::unordered_set<T> countAttackTimes(std::unordered_set<T> times) {
        constexpr T t_sq = t * t;
        if constexpr (t_sq < t1) {
            times.insert(t_sq);
            return countAttackTimes<t + 1>(times);
        }
        return times;
    }

    // counts ships via iterating over the tuple
    template<size_t n = 0>
    constexpr void iterateCountShips() {
        if constexpr(n < sizeof...(S)) {
            if constexpr (std::get<n>(ships).isImperial) {
                imperialFleet++;
            } else {
                rebelFleet++;
            }
            iterateCountShips<n + 1>();
        }
    }

    template<size_t n = 0, typename Imperial>
    constexpr void iterateFindRebel(Imperial &attacker) {
        if constexpr(n < sizeof...(S)) {
            auto &ship = std::get<n>(ships);
            if constexpr (!ship.isImperial) {
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
        if constexpr(n < sizeof...(S)) {
            auto &ship = std::get<n>(ships);
            if constexpr (ship.isImperial) {
                iterateFindRebel<>(ship);
            }
            iterateFindImperial<n + 1>();
        }
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
        if (imperialFleet == 0 && rebelFleet == 0) std::cout << "DRAW\n";
        else if (imperialFleet == 0) std::cout << "REBELLION WON\n";
        else if (rebelFleet == 0) std::cout << "IMPERIUM WON\n";
        else {
            if (attackTimes.find(actualTime) != attackTimes.end()) {
                iterateFindImperial();
            }
            actualTime = (actualTime + timeStep) % t1;
        }
    };
};

template<typename T, T t0, T t1, typename... S>
std::unordered_set<T> SpaceBattle<T, t0, t1, S...>::attackTimes = countAttackTimes(
        std::unordered_set<T>{});

#endif //STARWARS_BATTLE_H
