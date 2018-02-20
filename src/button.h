#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>

class Button : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	Button(QString name, QGraphicsItem *parent = NULL);

	void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
	void clicked();

private:
	QGraphicsTextItem *text;
};

#endif //BUTTON_H
