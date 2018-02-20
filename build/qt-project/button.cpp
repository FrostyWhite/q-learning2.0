#include "button.h"

//Create button
Button::Button(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	setRect(0, 0, 100, 50);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::darkCyan);
	setBrush(brush);

	//Set text to the middle of the button
	text = new QGraphicsTextItem(name, this);
	int x = rect().width() / 2 - text->boundingRect().width()/2;
	int y = rect().height() / 2 - text->boundingRect().height() / 2;
	text->setPos(x, y);
}

//Set button to emit signal when clicked
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	emit clicked();
}
