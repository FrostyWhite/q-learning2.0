#ifndef SIMULATION_H
#define SIMULATION_H

#include "Autobot.hpp"
#include "sensors.h"
#include "button.h"
#include "wall.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

class Simulation : public QGraphicsView 
{
	Q_OBJECT
public:
	Simulation(QWidget* parent = NULL);

	QGraphicsScene *scene;
	Autobot *bot;
	QTimer *timer;

	void displayMenu();

public slots:
	void start();
	void save();
	void load();

private:
	void createWalls();
	void createSensors();
};

#endif //SIMULATION_H
