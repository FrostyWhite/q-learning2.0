#include "simulation.h"

Simulation::Simulation(QWidget *parent)
{
	//Set up the screen
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(1024, 768);

	//Create scene
	scene = new QGraphicsScene();
	scene->setSceneRect(-500, -500, 1000, 1000);
	setScene(scene);
}

void Simulation::start()
{
	bot = new Autobot();
	scene->addItem(bot);

	createSensors();
	createWalls();

	timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), bot, SLOT(updateCar()));
	for (auto i : bot->getSPvect())
	{
		auto j = i.first;
		for (auto a : j)
		{
			QObject::connect(timer, SIGNAL(timeout()), a, SLOT(advance()));
		}

		j = i.second;
		for (auto a : j)
		{
			QObject::connect(timer, SIGNAL(timeout()), a, SLOT(advance()));
		}
	}
	timer->start(5);
}

void Simulation::save()
{
	bot->ann->save_to_file();
}

void Simulation::load()
{
	start();
    bot->ann = new ANN();
}

void Simulation::displayMenu()
{
	//Bug: multiple presses on start button creates multiple cars
	//TODO: fix
	Button* start = new Button(QString("start"));
	int stx = -225;
	int sty = -350;
	start->setPos(stx, sty);
	connect(start, SIGNAL(clicked()), this, SLOT(start()));
	scene->addItem(start);

	//Fully functional motherfucking save button
	Button* save = new Button(QString("Save"));
	int svx = -75;
	int svy = -350;
	save->setPos(svx, svy);
	connect(save, SIGNAL(clicked()), this, SLOT(save()));
	scene->addItem(save);

	//Load button
	Button* load = new Button(QString("Load"));
	int lx = 75;
	int ly = -350;
	load->setPos(lx, ly);
	connect(load, SIGNAL(clicked()), this, SLOT(load()));
	scene->addItem(load);

	//Quit button
	Button* quit = new Button(QString("Quit"));
	int qx = 225;
	int qy = -350;
	quit->setPos(qx, qy);
	connect(quit, SIGNAL(clicked()), this, SLOT(close()));
	scene->addItem(quit);
}

//Create sensors
void Simulation::createSensors()
{
	qreal npairs = 3;
	qreal nsensors = 3;
	qreal yoffmax = 100;
	qreal yoffmin = 0;
	qreal sensor_offset = 20;
	qreal amax = 50;
	qreal amin = 10;
	std::vector<std::pair < std::vector<Sensors*>, std::vector<Sensors*>>> sp_vector;
	qreal yoffset_step = (yoffmax - yoffmin) / nsensors;
	qreal sensorlength = 25;
	qreal angle_step = (amax - amin) / nsensors;
	std::vector<Sensors*> sbuff1, sbuff2;

	for (qreal i = 0; i < npairs; i++)
	{
		for (qreal j = 0; j < nsensors; j++)
		{
			//Sensors(qreal w, qreal h, qreal x, qreal y, qreal p_radius_offset, qreal p_angle_offset,Car* p_c)
			Sensors *s1 = new Sensors(2, sensorlength, 20, (yoffmin + i*yoffset_step), sensor_offset + j*sensorlength, (amax - i*angle_step));
			Sensors *s2 = new Sensors(2, sensorlength, 0, (yoffmin + i*yoffset_step), sensor_offset + j*sensorlength, -(amax - i*angle_step));
			s1->setCvals(bot->getCx(), bot->getCy(), bot->getCa());
			s2->setCvals(bot->getCx(), bot->getCy(), bot->getCa());
			scene->addItem(s1);
			scene->addItem(s2);

			sbuff1.push_back(s1);
			sbuff2.push_back(s2);
		}
		std::pair < std::vector<Sensors*>, std::vector<Sensors*>> sp(sbuff1, sbuff2);//<Sensors, Sensors>
		sp_vector.push_back(sp);

		sbuff1.clear();
		sbuff2.clear();
	}

	bot->setSPvect(sp_vector);
}

//Create walls
void Simulation::createWalls()
{
	Wall *wall = new Wall();
	wall->setPos(-100, 350);
	wall->setRect(0, 0, 200, 10);
	wall->setBrush(Qt::black);
	scene->addItem(wall);

	Wall *wall2 = new Wall();
	wall2->setPos(-100, 210);
	wall2->setRect(0, 0, 150, 10);
	wall2->setRotation(90);
	wall2->setBrush(Qt::black);
	scene->addItem(wall2);

	Wall *wall3 = new Wall();
	wall3->setPos(110, 160);
	wall3->setRect(0, 0, 200, 10);
	wall3->setRotation(90);
	wall3->setBrush(Qt::black);
	scene->addItem(wall3);

	Wall *wall4 = new Wall();
	wall4->setPos(-115, 30);
	wall4->setRect(0, 0, 260, 10);
	wall4->setRotation(30);
	wall4->setBrush(Qt::black);
	scene->addItem(wall4);

	Wall *wall5 = new Wall();
	wall5->setPos(-215, 10);
	wall5->setRect(0, 0, 100, 30);
	wall5->setBrush(Qt::black);
	scene->addItem(wall5);

	Wall *wall6 = new Wall();
	wall6->setPos(-260, 210);
	wall6->setRect(0, 0, 150, 10);
	wall6->setBrush(Qt::black);
	scene->addItem(wall6);

	Wall *wall12 = new Wall();
	wall12->setPos(-360, 110);
	wall12->setRect(0, 0, 150, 10);
	wall12->setRotation(45);
	wall12->setBrush(Qt::black);
	scene->addItem(wall12);

	Wall *wall7 = new Wall();
	wall7->setPos(-360, -80);
	wall7->setRect(0, 0, 200, 10);
	wall7->setRotation(90);
	wall7->setBrush(Qt::black);
	scene->addItem(wall7);

	Wall *wall13 = new Wall();
	wall13->setPos(-370, -80);
	wall13->setRect(0, 0, 140, 10);
	wall13->setRotation(-45);
	wall13->setBrush(Qt::black);
	scene->addItem(wall13);

	Wall *wall8 = new Wall();
	wall8->setPos(-270, -180);
	wall8->setRect(0, 0, 220, 10);
	wall8->setBrush(Qt::black);
	scene->addItem(wall8);

	Wall *wall9 = new Wall();
	wall9->setPos(-50, -180);
	wall9->setRect(0, 0, 302, 10);
	wall9->setRotation(45);
	wall9->setBrush(Qt::black);
	scene->addItem(wall9);

	Wall *wall10 = new Wall();
	wall10->setPos(110, 160);
	wall10->setRect(0, 0, 300, 10);
	wall10->setBrush(Qt::black);
	scene->addItem(wall10);

	Wall *wall11 = new Wall();
	wall11->setPos(158, 32);
	wall11->setRect(0, 0, 242, 10);
	wall11->setBrush(Qt::black);
	scene->addItem(wall11);

	Finish *finish = new Finish();
	finish->setPos(410, 32);
	finish->setRect(0, 0, 138, 10);
	finish->setRotation(90);
	finish->setBrush(Qt::white);
	scene->addItem(finish);
}
