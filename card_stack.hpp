#ifndef __CARD_STACK_HPP__
#define __CARD_STACK_HPP__

#include <iostream>
#include <vector>
#include <time.h>
#include "card.hpp"
#include "card_pkg.hpp"
#include "factory_info.hpp"

class card_stack{
public:
	card_stack(){}

	card_stack(factory_info info){
		_info = info;
		init();
		srand((unsigned)time(NULL));
	}
	void init(){
		for(int i=0;i<_info.nb_level0;i++){
			card c(i,0,QString("level0 card #%1").arg(i));
			level0.push_back(c);
		}
		for(int i=0;i<_info.nb_level1;i++){
			card c(i,1,QString("level1 card #%1").arg(i));
			level1.push_back(c);
		}
		for(int i=0;i<_info.nb_level2;i++){
			card c(i,2,QString("level2 card #%1").arg(i));
			level2.push_back(c);
		}
		for(int i=0;i<_info.nb_level3;i++){
			card c(i,3,QString("level3 card #%1").arg(i));
			level3.push_back(c);
		}
	}
	card getLevel0(){ return level0.at(rand()%_info.nb_level0); }
	card getLevel1(){ return level1.at(rand()%_info.nb_level1); }
	card getLevel2(){ return level2.at(rand()%_info.nb_level2); }
	card getLevel3(){ return level3.at(rand()%_info.nb_level3); }

private:
	std::vector<card> level0; // 90
	std::vector<card> level1; // 18(1/1)
	std::vector<card> level2; //  9(1/3)
	std::vector<card> level3; //  6(1/6)
	factory_info _info;
};

#endif