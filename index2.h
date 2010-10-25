#ifndef INDEX2_H
#define INDEX2_H

#include <QtGui/QMainWindow>
#include "ui_index2.h"
#include "card_stack.hpp"
#include "card_pkg.hpp"
#include "card_pkg_factory.hpp"
#include "card.hpp"
#include "factory_info.hpp"

class index2 : public QMainWindow
{
	Q_OBJECT

public:
	index2(QWidget *parent = 0, Qt::WFlags flags = 0);
	~index2();


public slots:
	void usemoneybutton();
	void usemoneyunlimitedbutton();
	void usemoneystopbutton();
	void clearstat();
	void changeFactoryInfo();
	void init();

private:
	Ui::index2Class ui;
	void update_one(card_pkg p);

	int nb_tryal;
	factory_info info;
	card_pkg_factory* factory;
	bool end;
	bool flag_stop;

	int nb_level0;
	int nb_level1;
	int nb_level2;
	int nb_level3;

	int unb_level0;
	int unb_level1;
	int unb_level2;
	int unb_level3;
	std::vector<card> level0;
	std::vector<card> level1;
	std::vector<card> level2;
	std::vector<card> level3;

	int avg_nb_tryal;
	int avg_nb_cost;
	int nb_complete;

	std::vector<int> vector_nb_tryals;
	std::vector<int> dist_tryals;
	void createFactoryInfo();

	bool check_push_back(std::vector<card> &v1, card &v2){
		bool unique = true;
		for(int i=0;i<v1.size();i++){
			if(v1.at(i) == v2){
				unique = false;
				break;
			}
		}

		if(unique){
			v1.push_back(v2);
			return true;
		}else{
			return false;
		}
	}

	int vector_average(std::vector<int> &v)
	{
		int j = 0;
		for(int i=0;i<v.size();i++) j+= v[i];
		return (float)j/(float)v.size();
	}

	int vector_prob(std::vector<int> &v, int limit){

		int c = 0;
		for(int i=0;i<v.size();i++){
			if(v[i] <= limit){
				c++;
			}
		}
		return ((float)c/(float)v.size())*100;
	}

	bool vector_find(std::vector<card> &v1, int id)
	{
		for(int i=0;i<v1.size();i++){
			if(v1.at(i).id() == id) return true;
		}
		return false;
	}

	bool end_condition();
};

#endif // INDEX2_H
