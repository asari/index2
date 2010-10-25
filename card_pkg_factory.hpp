#ifndef __CARD_PKG_FACTORY_HPP__
#define __CARD_PKG_FACTORY_HPP__

#include "factory_info.hpp"
#include "card_pkg.hpp"
#include <time.h>

class card_pkg_factory{

public:
	card_pkg_factory(card_stack s, factory_info info)
	{ 
		cs = s; 
		stock_size = 10000;
		flag_level1 = true;
		flag_level2 = true;
		flag_level3 = true;
		srand((unsigned)time(NULL));
		_info = info;
		stock_counter = 0;
	}

	void create()
	{
		for(int i=0;i<stock_size;i++){
			create_one();
		}
	}

	std::vector<card_pkg> factory(){ return stock; }

	card_pkg buy()
	{
		int ran = rand()%stock_size;
		return stock.at(ran);
	}

private:
	void create_one()
	{
		stock_counter++;
		card_pkg pkg(_info);
		int size = pkg.size();
		int nb_card = 0;
		std::vector<card> dupl_check;

		if(stock_counter%_info.pb_level1 == 0) flag_level1 = true;
		else flag_level1 = false;

		if(stock_counter%_info.pb_level2 == 0) flag_level2 = true;
		else flag_level2 = false;

		if(stock_counter%_info.pb_level3 == 0) flag_level3 = true;
		else flag_level3 = false;

		// handle special cards
		if(flag_level1){
			pkg.push_back(cs.getLevel1());
			nb_card++;
		}
		if(flag_level2){
			pkg.push_back(cs.getLevel2());
			nb_card++;
		}
		if(flag_level3){
			pkg.push_back(cs.getLevel3());
			nb_card++;
		}

		// handle regular card
		for(int i=0;i<(size-nb_card);i++){
			while(true){
				bool unique = true;
				card c = cs.getLevel0();
				for(int j=0;j<dupl_check.size();j++){
					if(c == dupl_check.at(j)){
						unique = false;
						break;
					}
				}
				if(unique){
					pkg.push_back(c);			
					dupl_check.push_back(c);
					break;
				}
			}
		}

		// save stock
		stock.push_back(pkg);
	}

	bool flag_level1; // always true
	bool flag_level2; // 1/3 true
	bool flag_level3; // 1/6 true

	card_stack cs;
	std::vector<card_pkg> stock;
	int stock_size;
	int stock_counter;
	factory_info _info;
};

#endif