#include "ObjectManager.h"

ObjectManager::ObjectManager(QWidget *parent) : QListWidget(parent)
{

}

ObjectManager::~ObjectManager()
{
	delete[] m_objects.data();
}
