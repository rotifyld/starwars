#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include <cassert>
#include <iostream>

int main() {
    XWing<float> xwing(100.0f, 300000.0f, 50.0f);
    Explorer<int> explorer(150, 400000);
    StarCruiser<unsigned> cruiser(1234, 100000, 11);

    assert(xwing.getAttackPower() == 50.0f);
    assert(explorer.getShield() == 150);
    assert(cruiser.getSpeed() == 100000);

    DeathStar<long> deathStar(10000, 75);
    TIEFighter<unsigned> fighter(50, 9);
    ImperialDestroyer<int> destroyer(150, 20);

    std::cout << deathStar.getShield() << "\n";
    attack(deathStar, xwing);
    std::cout << deathStar.getShield() << "\n";

//    auto battle = SpaceBattle<short, 1, 23,
//                              DeathStar<long>,
//                              Explorer<int>,
//                              TIEFighter<unsigned>,
//                              XWing<float>>(deathStar,
//                                            explorer,
//                                            fighter,
//                                            xwing);
//
//    assert(battle.countRebelFleet() == 2);
//    assert(battle.countImperialFleet() == 2);
//
//    battle.tick(2);
//    assert(battle.countRebelFleet() == 2);
//    assert(battle.countImperialFleet() == 1);
//
//    battle.tick(1);
//    assert(battle.countRebelFleet() == 2);
//    assert(battle.countImperialFleet() == 1);
//
//    battle.tick(4);
//    assert(battle.countRebelFleet() == 0);
//    assert(battle.countImperialFleet() == 1);
//
//    battle.tick(1); // Wypisuje "IMPERIUM WON\n".
}
