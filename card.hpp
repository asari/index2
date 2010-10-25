#ifndef __CARD_HPP__
#define __CARD_HPP__

class card{
public:
	card(int i, int t, QString n){
		_id   = i;
		_type = t;
		_name = n;
	}
	bool operator==(const card& obj){ return(this->_id == obj._id && this->_type && obj._type); } 

	QString name(){ return _name; }
	int id(){ return _id; }
	int type(){ return _type; }
	QString toString(){
		QString temp = QString("Card: #%1").arg(_id);
		temp.append(QString(", Type: %1").arg(_type));
		temp.append(QString("\n"));
		return temp;
	}

private:
	QString _name;
	int _id;
	int _type;
};

#endif