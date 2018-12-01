#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include<tuple>
#include<iostream>
#include"imperialfleet.h"
#include"rebelfleet.h"

using namespace std;


template<typename T, T t0, T t1, typename ...S>
class SpaceBattle
{
	tuple<S...> imperial_fleet;
	tuple<S...> rebel_fleet;

public:
	SpaceBattle(const S&... ships) : imperial_fleet(ships...), rebel_fleet(ships...) {};

	size_t countImperialFleet() {return 0;};
	size_t countRebelFleet() {return 0;};
	void tick(T timeStep) {};
};




#endif //STARWARS_BATTLE_H
