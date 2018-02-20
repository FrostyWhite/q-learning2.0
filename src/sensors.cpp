#include "sensors.h"
#include "wall.h" 
#include <QRectF>
#include <QPainter>
#include <cmath>

QRectF Sensors::boundingRect() const
{
	return QRectF(-10, -15, width, height);
}

Sensors::Sensors(qreal w, qreal h, qreal x, qreal y, qreal p_radius_offset, qreal p_angle_offset)
{
	width = w;
	height = h;
	radius_offset = p_radius_offset;
	angle_offset = p_angle_offset;
	x_offset = x;
	y_offset = y;
	setFlag(QGraphicsItem::ItemIsMovable, true);

	setRotation(p_angle_offset);
	
	setPos(x, y);
}

void Sensors::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->setBrush(color);
	painter->drawRect(-10, -15, width, height);
}

void Sensors::advance()
{
	qreal aa = c_a*3.14/180;
	qreal a = angle_offset + c_a;
	qreal b = a*3.14 / 180;
	setRotation(a);
    setPos(c_x + y_offset*sin(aa) +x_offset*cos(b) +radius_offset * sin(b), c_y - radius_offset* cos(b)  -y_offset*cos(aa) +x_offset*sin(b));
}

void Sensors::setCvals(qreal p_c_x, qreal p_c_y, qreal p_c_a) {
	c_x = p_c_x;
	c_y = p_c_y;
	c_a = p_c_a;
}
