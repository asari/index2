#include "index2.h"

index2::index2(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.pushButton, SIGNAL(pressed()), this, SLOT(usemoneybutton()));
	connect(ui.pushButton_3, SIGNAL(pressed()), this, SLOT(usemoneyunlimitedbutton()));
	connect(ui.pushButton_4, SIGNAL(pressed()), this, SLOT(usemoneystopbutton()));
	connect(ui.pushButton_2, SIGNAL(pressed()), this, SLOT(changeFactoryInfo()));
	connect(ui.pushButton_5, SIGNAL(pressed()), this, SLOT(clearstat()));
	connect(ui.pushButton_6, SIGNAL(pressed()), this, SLOT(init()));

	avg_nb_tryal = 0;
	avg_nb_cost = 0;
	nb_complete = 0;
	for(int i=0;i<19;i++){
		dist_tryals.push_back(0);
	}

	createFactoryInfo();
	card_stack cs(info);
	factory = new card_pkg_factory(cs, info);
	factory->create();
	init();
}
index2::~index2(){ }

void index2::createFactoryInfo()
{
	info.nb_level0 = ui.spinBox_5->value();
	info.nb_level1 = ui.spinBox_6->value();
	info.nb_level2 = ui.spinBox_7->value();
	info.nb_level3 = ui.spinBox_8->value();
	info.pb_level0 = 1;
	info.pb_level1 = ui.spinBox_10->value();
	info.pb_level2 = ui.spinBox_11->value();
	info.pb_level3 = ui.spinBox_12->value();
	info.pkg_size = ui.spinBox_13->value();
	info.pkg_cost = ui.spinBox_14->value();

	std::cout << "Create Factory Info" << std::endl;
}

void index2::changeFactoryInfo(){
	delete factory;
	factory = NULL;
	createFactoryInfo();
	card_stack cs(info);
	factory = new card_pkg_factory(cs, info);
	factory->create();
	clearstat();
}

void index2::clearstat()
{
	avg_nb_tryal = 0;
	avg_nb_cost = 0;
	nb_complete = 0;

	for(int i=0;i<19;i++){
		dist_tryals[i] = 0;
	}

	for(int i=0;i<vector_nb_tryals.size();i++){
		vector_nb_tryals.at(i) = 0;
	}
	vector_nb_tryals.clear();
	
	init();
}

void index2::usemoneystopbutton()
{
	flag_stop = true;
}

void index2::usemoneyunlimitedbutton()
{
	if(flag_stop){
		flag_stop = false;
	}
	while(!flag_stop){
		init();
		while(!end){
			update_one(factory->buy());
		}		
		QCoreApplication::processEvents();
	}
}

void index2::init()
{
	nb_tryal = 0;	
	int cost = nb_tryal*380;
	end = false;
	flag_stop = false;
	nb_level0 = 0;
	nb_level1 = 0;
	nb_level2 = 0;
	nb_level3 = 0;
	unb_level0 = 0;
	unb_level1 = 0;
	unb_level2 = 0;
	unb_level3 = 0;

	level0.clear();
	level1.clear();
	level2.clear();
	level3.clear();

	//update gui
	ui.label_12->setText(QString("%1").arg(nb_tryal));
	ui.label_13->setText(QString("%1").arg(cost));

	ui.label_5->setText(QString("%1").arg(nb_level0));
	ui.label_6->setText(QString("%1").arg(nb_level1));
	ui.label_7->setText(QString("%1").arg(nb_level2));
	ui.label_8->setText(QString("%1").arg(nb_level3));

	ui.progressBar->setValue(unb_level0);
	ui.progressBar_2->setValue(unb_level1);
	ui.progressBar_3->setValue(unb_level2);
	ui.progressBar_4->setValue(unb_level3);
}

void index2::update_one(card_pkg p)
{
	nb_tryal++;		
	int cost = nb_tryal*info.pkg_cost;

	//total number of cards
	std::vector<card> cards = p.contents();
	for(int i=0;i<cards.size();i++){
		if(cards.at(i).type() == 0){
			check_push_back(level0,cards.at(i));
			nb_level0++;
			unb_level0 = ((float)level0.size()/(float)info.nb_level0)*100;
			if(unb_level0 >= 100) unb_level0 = 100;
		}else if(cards.at(i).type() == 1){
			check_push_back(level1,cards.at(i));
			nb_level1++;
			unb_level1 = ((float)level1.size()/(float)info.nb_level1)*100;
			if(unb_level1 >= 100) unb_level1 = 100;
		}else if(cards.at(i).type() == 2){
			check_push_back(level2,cards.at(i));
			nb_level2++;
			unb_level2 = ((float)level2.size()/(float)info.nb_level2)*100;
			if(unb_level2 >= 100) unb_level1 = 100;
		}else if(cards.at(i).type() == 3){
			check_push_back(level3,cards.at(i));
			nb_level3++;
			unb_level3 = ((float)level3.size()/(float)info.nb_level3)*100;
			if(unb_level3 >= 100) unb_level1 = 100;
		}
	}

	if(end_condition()){
		end = true;
		nb_complete++;
		vector_nb_tryals.push_back(nb_tryal);
		if(nb_complete%10 == 0){
			avg_nb_tryal = vector_average(vector_nb_tryals);

			ui.label_34->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,20)));
			ui.label_35->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,30)));
			ui.label_36->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,40)));
			ui.label_37->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,50)));
			ui.label_38->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,60)));
			ui.label_39->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,70)));
			ui.label_40->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,80)));
			ui.label_41->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,90)));
			ui.label_42->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,100)));
			ui.label_43->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,110)));
			ui.label_44->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,120)));
			ui.label_45->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,130)));
			ui.label_47->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,140)));
			ui.label_54->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,150)));
			ui.label_55->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,160)));
			ui.label_56->setText(QString("%1 %").arg(vector_prob(vector_nb_tryals,170)));
			ui.label_57->setText(QString("%1 %").arg(1.0));
		}
		avg_nb_cost  = avg_nb_tryal * info.pkg_cost;

		ui.label_14->setText(QString("%1").arg(nb_complete));
		ui.label_17->setText(QString("%1").arg(avg_nb_tryal));
		ui.label_18->setText(QString("%1").arg(avg_nb_cost));		

		if(nb_tryal < 20) dist_tryals[0]++;
		else if(nb_tryal < 30) dist_tryals[1]++;
		else if(nb_tryal < 40) dist_tryals[2]++;
		else if(nb_tryal < 50) dist_tryals[3]++;
		else if(nb_tryal < 60) dist_tryals[4]++;
		else if(nb_tryal < 70) dist_tryals[5]++;
		else if(nb_tryal < 80) dist_tryals[6]++;
		else if(nb_tryal < 90) dist_tryals[7]++;
		else if(nb_tryal < 100) dist_tryals[8]++;
		else if(nb_tryal < 110) dist_tryals[9]++;
		else if(nb_tryal < 120) dist_tryals[10]++;
		else if(nb_tryal < 130) dist_tryals[11]++;
		else if(nb_tryal < 140) dist_tryals[12]++;
		else if(nb_tryal < 150) dist_tryals[13]++;
		else if(nb_tryal < 160) dist_tryals[14]++;
		else if(nb_tryal < 170) dist_tryals[15]++;
		else if(nb_tryal < 180) dist_tryals[16]++;
		else if(nb_tryal < 190) dist_tryals[17]++;
		else if(200 <= nb_tryal) dist_tryals[18]++;

		float typ = 2.5;
		if(nb_complete > 1000) typ = 5.0;
		if(nb_complete > 3000) typ = 10.0;
		if(nb_complete > 6000) typ = 20.0;
		if(nb_complete >12000) typ = 40.0;

		ui.progressBar_5->setValue(dist_tryals[0]/typ);
		ui.progressBar_6->setValue(dist_tryals[1]/typ);
		ui.progressBar_7->setValue(dist_tryals[2]/typ);
		ui.progressBar_8->setValue(dist_tryals[3]/typ);
		ui.progressBar_9->setValue(dist_tryals[4]/typ);
		ui.progressBar_10->setValue(dist_tryals[5]/typ);
		ui.progressBar_11->setValue(dist_tryals[6]/typ);
		ui.progressBar_12->setValue(dist_tryals[7]/typ);
		ui.progressBar_13->setValue(dist_tryals[8]/typ);
		ui.progressBar_14->setValue(dist_tryals[9]/typ);
		ui.progressBar_15->setValue(dist_tryals[10]/typ);
		ui.progressBar_16->setValue(dist_tryals[11]/typ);
		ui.progressBar_17->setValue(dist_tryals[12]/typ);
		ui.progressBar_18->setValue(dist_tryals[13]/typ);
		ui.progressBar_19->setValue(dist_tryals[14]/typ);
		ui.progressBar_20->setValue(dist_tryals[15]/typ);
		ui.progressBar_21->setValue(dist_tryals[16]/typ);
		//ui.progressBar_22->setValue(dist_tryals[17]/typ);
		//ui.progressBar_23->setValue(dist_tryals[18]/typ);

	}

	//update gui
	ui.label_12->setText(QString("%1").arg(nb_tryal));
	ui.label_13->setText(QString("%1").arg(cost));

	ui.label_5->setText(QString("%1").arg(nb_level0));
	ui.label_6->setText(QString("%1").arg(nb_level1));
	ui.label_7->setText(QString("%1").arg(nb_level2));
	ui.label_8->setText(QString("%1").arg(nb_level3));

	ui.progressBar->setValue(unb_level0);
	ui.progressBar_2->setValue(unb_level1);
	ui.progressBar_3->setValue(unb_level2);
	ui.progressBar_4->setValue(unb_level3);
}

bool index2::end_condition()
{
	//“Á’è
	if(ui.comboBox->currentIndex() == 2){
		bool tokutei = true;

		for(int i=0;i<ui.spinBox->value();i++){
			if(!vector_find(level0,i)){
				tokutei = false;
			}
		}
		for(int i=0;i<ui.spinBox_2->value();i++){
			if(!vector_find(level1,i)){
				tokutei = false;
			}
		}
		for(int i=0;i<ui.spinBox_3->value();i++){
			if(!vector_find(level2,i)){
				tokutei = false;
			}
		}
		for(int i=0;i<ui.spinBox_4->value();i++){
			if(!vector_find(level3,i)){
				tokutei = false;
			}
		}
		if(tokutei) return true;
		return false;
	}else{
		//’Êí
		if(
			level0.size() >= info.nb_level0-(int)ui.spinBox->value() && 
			level1.size() >= info.nb_level1-(int)ui.spinBox_2->value() && 
			level2.size() >= info.nb_level2-(int)ui.spinBox_3->value() && 
			level3.size() >= info.nb_level3-(int)ui.spinBox_4->value()){
			return true;
		}
	}
	return false;
}

void index2::usemoneybutton(){ 
	if(ui.checkBox->isChecked()){
		while(!end){
			update_one(factory->buy());
		}
	}else{
		update_one(factory->buy());
	}
}
