#include <QGraphicsRectItem>
#include <QObject>

#ifndef WALL_H
#define WALL_H

class Wall : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	Wall();
};

#endif //WALL_H

#ifndef FINISH_H
#define FINISH_H

class Finish : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	Finish();
};

#endif //FINISH_H
