#ifndef __CARD_PKG_HPP__
#define __CARD_PKG_HPP__

#include "factory_info.hpp"
#include "card.hpp"
#include <iostream>
#include <vector>

class card_pkg{

public:
	card_pkg(factory_info& i){
		_size = i.pkg_size; // ñá/ÉJÅ[Éh
		name = QString();
	}
	card_pkg(QString n, factory_info& i){
		_size = i.pkg_size;
		name = n;
	}
	int size(){ return _size; }
	void push_back(card& c){ _contents.push_back(c); }
	std::vector<card> contents(){ return _contents; }
	QString toString()
	{
		QString temp = QString("Package:\n");
		for(int i=0;i<_contents.size();i++){
			card c = _contents.at(i);
			temp.append(c.toString());
		}
		return temp;
	}

private:
	std::vector<card> _contents;
	int _size;

	QString name;
};

#endif