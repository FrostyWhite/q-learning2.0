#include "Autobot.hpp"

//constructor
Autobot::Autobot() : color(Qt::blue), angle(0), speed(10), m_rotation(0), m_frict_multip(0.8),
m_traction(true), m_real_x_pos(0), m_real_y_pos(300), m_x_dir(0), m_y_dir(0)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);

	ann = new ANN(7, 6, 1, 5);

	setPos(0, 300);
}

qreal& Autobot::getCx() {
	return m_real_x_pos;
}

qreal& Autobot::getCy() {
	return m_real_y_pos;
}

qreal& Autobot::getCa() {
	return angle;
}

void Autobot::setSPvect(std::vector<std::pair < std::vector<Sensors*>, std::vector<Sensors*>>>& p_spv)
{
	spv = p_spv;
}

std::vector<std::pair < std::vector<Sensors*>, std::vector<Sensors*>>>& Autobot::getSPvect()
{
	return spv;
}

QRectF Autobot::boundingRect() const
{
	return QRectF(-10, -15, 20, 30);
}

qreal Autobot::getAngle() {
	return angle;
}

std::vector<double> Autobot::hitvalues()
{
	std::vector<double> ret;
	double n;
	for (auto i : spv) 
	{
		auto j = i.first;
		n = 0;
		for (auto a : j) 
		{
			QList<QGraphicsItem *> walls = a->collidingItems();
			if (walls.begin() != walls.end()) 
			{
				break;
			}
			else 
			{
				n+=1;
			}
		}
		ret.push_back(n);
		
		j = i.second;
		n = 0;
		for (auto a : j) 
		{
			QList<QGraphicsItem *> walls = a->collidingItems();
			if (walls.begin() != walls.end()) 
			{
				break;
			}
			else 
			{
				n+=1;
			}
		}
		ret.push_back(n);

	}
	return ret;
}

void Autobot::updateCar() 
{
	auto sensordata = hitvalues();
	double Qval = Q_value(sensordata, double(speed));
	sensordata.push_back(double(speed));

	std::vector<unsigned int> c_vals = ann->car_operating_interface(sensordata, Qval);
	ann->Q_tune();
	if (m_traction) 
	{
		switch (c_vals.at(0))
		{
		case 0:
			rotate_left();
			break;
		case 2:
			rotate_right();
			break;
		default:
			break;
		}

		switch (c_vals.at(1))
		{
		case 0:
			decelerate();
			break;
		case 2:
			accelerate();
			break;
		default:
			break;
		}
	}

	m_frict_multip = (m_traction ? 0.8 : 0.7);

	if ((17 * qAbs(m_rotation) * speed * 3.14159265) / 180 > m_frict_multip * 9.81) m_traction = false;
	if (m_traction == false && speed == 0) 
	{
		m_traction = true;
		m_rotation = 0;
		m_x_dir = qSin(qDegreesToRadians(angle));
		m_y_dir = qCos(qDegreesToRadians(angle));
	}

	rotate();
	advance();

	//next part gives sensors the information about car position
	for (auto i : spv)
	{
		auto j = i.first;
		for (auto a : j)
		{
			a->setCvals(m_real_x_pos, m_real_y_pos, angle);
		}

		j = i.second;
		for (auto a : j)
		{
			a->setCvals(m_real_x_pos, m_real_y_pos, angle);
		}
	}
}

void Autobot::rotate()
{
	if (!m_traction) 
	{
		m_rotation *= 0.95;
	}
	angle += (int)(m_rotation * (1.2 * speed / 10));
	setRotation(angle);
}

void Autobot::advance()
{
	QList<QGraphicsItem *> walls = collidingItems(); //find all walls that collide with car
	for (int i = 0, n = walls.size(); i < n; ++i)
	{
		if (typeid(*(walls[i])) == typeid(Wall) || typeid(*(walls[i])) == typeid(Finish))
		{
			reset_car();
		}
	}
	if (speed == 0) { accelerate(); }
	if (m_traction) 
	{
		m_x_dir = qSin(qDegreesToRadians(angle));
		m_y_dir = qCos(qDegreesToRadians(angle));
	}
	else 
	{
		speed -= 0.28;
		if (speed < 0.001) speed = 0.0;
	}
	m_real_x_pos += (speed * m_x_dir);
	m_real_y_pos -= (speed * m_y_dir);

	setPos(m_real_x_pos, m_real_y_pos);
}

void Autobot::accelerate()
{
	if (!m_traction && speed != 0) return;
	if (speed < 10)
		speed += 0.4;
}

void Autobot::decelerate()
{
	if (!m_traction && speed != 0) return;
	if (speed > -10)
		speed -= 0.4;
	if (speed < 0) speed = 0;
}

void Autobot::rotate_left() 
{
	if (!m_traction || speed == 0) return;
	if (m_rotation > -9) m_rotation--;
}

void Autobot::rotate_right() 
{
	if (!m_traction || speed == 0) return;
	if (m_rotation < 9) m_rotation++;
}

void Autobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->setBrush(color);
	painter->drawRect(-10, -15, 20, 30);
}

void Autobot::reset_car()
{
	angle = 0;
	speed = 1;
	setPos(0, 300);
	setRotation(0);
	m_rotation = 0;
	m_frict_multip = 0.8;
	m_traction = true;
	m_x_dir = 0;
	m_y_dir = 0;
	m_real_x_pos = 0;
	m_real_y_pos = 300;
	
    ann->car_operating_interface(hitvalues(), -2);
	
	ann->Q_tune();
}
