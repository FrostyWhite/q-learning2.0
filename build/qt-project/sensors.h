#ifndef SENSORS_H
#define SENSORS_H

#include "wall.h"

#include <QGraphicsObject>
#include <QPainter>
#include <QBrush>
#include <QRectF>
#include <cmath>

class Sensors : public QGraphicsObject
{
	Q_OBJECT
public:
	QRectF boundingRect() const;
	Sensors() {} 
	Sensors(qreal w, qreal h, qreal x, qreal y, qreal p_radius_offset, qreal p_angle_offset);
	void setCvals(qreal p_c_x, qreal p_c_y, qreal p_c_a);

public Q_SLOTS:
	void advance();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
	QBrush color = Qt::white;
	qreal width;
	qreal height;
	qreal radius_offset;
	qreal angle_offset;
	qreal x_offset;
	qreal y_offset;
	qreal c_x, c_y, c_a;
};

#endif //SENSORS_H
