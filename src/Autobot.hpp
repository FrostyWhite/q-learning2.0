#ifndef _AUTOBOT_H_
#define _AUTOBOT_H_

#include "Q_function.hpp"
#include "sensors.h"
#include "ANN.hpp"
#include "wall.h"

#include <QGraphicsObject>
#include <QPainter>
#include <qmath.h>
#include <QBrush>
#include <QTimer>
#include <QList>

class Autobot: public QGraphicsObject {
	Q_OBJECT
public:
	Autobot();

	QRectF boundingRect() const;
	qreal getAngle();
	qreal& getCx();
	qreal& getCy();
	qreal& getCa();
	void setSPvect(std::vector<std::pair < std::vector<Sensors*>, std::vector<Sensors*>>>& p_spv);
	std::vector<std::pair < std::vector<Sensors*>, std::vector<Sensors*>>>& getSPvect();
    std::vector<double> hitvalues();
	ANN *ann;

public Q_SLOTS:
	void accelerate();
	void decelerate();
	void rotate_left();
	void rotate_right();
	void updateCar();
	void rotate();
	void advance();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	void reset_car();

private:
	QBrush color;
	bool m_traction;
	qreal angle;
	qreal speed;
	qreal m_x_dir;
	qreal m_y_dir;
	qreal m_rotation;
	qreal m_scrn_y_pos;
	qreal m_scrn_x_pos;
	qreal m_real_y_pos;
	qreal m_real_x_pos;
	double m_frict_multip;

	std::vector<std::pair < std::vector<Sensors*>, std::vector<Sensors*>>> spv;
};

#endif //_AUTOBOT_H_
