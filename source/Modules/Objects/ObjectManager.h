#pragma once

#include <QListWidget>
#include <vector>

class Object;

class ObjectManager : public QListWidget
{
	Q_OBJECT
public:
	explicit ObjectManager(QWidget *parent = nullptr);
	~ObjectManager();

signals:

private:
	std::vector<Object*> m_objects;

};

