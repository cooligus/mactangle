#include <vector>
#include <iostream>
#include <string>
#include "PPSaB.h"
#include "mainclasses.h"
#include "map.h"
#include "additionals.h"
#include "mactangle.h"
#include "dacler.h"
#include "bedler.h"
#include "shop.h"
#include "offert.h"

//using namespace std;
//using namespace sf;


MainClass object_main;
sf::Event event;
Map the_map;
Addidtionals addition(object_main);
Mactangle mactangle(the_map, object_main);
Dacler dacler;
Bedler bedler(object_main);
Shop shop(object_main, the_map);
Offert dacler_offert(dacler, dacler.getHimTexture(), 4080, 500, 300, 1.5, object_main, 1);
Offert bedler_offert(bedler, bedler.getHimTexture(), 4080, 1000, 100, 1.5, object_main, 2);

void WindowDoEvents()
{
	while (object_main.m_window.pollEvent(event))
	{
		if (Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))object_main.m_window.close();
	}
}
void WindowDraw()
{
	object_main.m_window.clear();
	the_map.display(object_main);
	for (int i = 1; shop.daclers.size() > i; i++)
	{
		shop.daclers[i].textureReset();
		object_main.m_window.draw(shop.daclers[i]);
	}
	for (int i = 1; shop.mactangles.size() > i; i++)
	{
		shop.mactangles[i].textureReset();
		object_main.m_window.draw(shop.mactangles[i]);
		shop.mactangles[i].displaySomething(object_main);
	}
	for (int i = 1; shop.bedlers.size() > i; i++)
	{
		shop.bedlers[i].textureReset();
		object_main.m_window.draw(shop.bedlers[i]);
		shop.bedlers[i].display(object_main);
	}
	shop.display(object_main);
	dacler_offert.display(shop, object_main);
	bedler_offert.display(shop, object_main);
	addition.display(shop, object_main);

	object_main.m_window.display();
}

int main()
{
	shop.setSomething(object_main);
	dacler_offert.setSomething(object_main);
	bedler_offert.setSomething(object_main);

	while (object_main.m_window.isOpen())
	{
		WindowDoEvents();
		if (object_main.m_gameRuning == true)
		{
			shop.daclers.back().set(the_map, object_main);
			shop.bedlers.back().set(the_map, object_main);
			for (int i = 1; shop.daclers.size() > i; i++)
			{
				shop.daclers[i].work(the_map, object_main);
			}
			for (int i = 1; shop.mactangles.size() > i; i++)
			{
				shop.mactangles[i].moving(the_map);

				if (addition.takeHp(the_map, shop.mactangles[i]) == true)
					shop.mactangles.erase(shop.mactangles.begin());
			}
			for (int i = 1; shop.bedlers.size() > i; i++)
			{
				shop.bedlers[i].work(shop.bedlers[i], the_map, object_main, shop.mactangles);
				if (shop.bedlers[i].addMoney() == true)
				{
					shop.money += 20;
				}
			}
			dacler_offert.offertUseful(shop, object_main);
			bedler_offert.offertUseful(shop, object_main);
			shop.destroyMactangle();
			shop.working(the_map, object_main);
			if (addition.gameOver() == true)
			{
				object_main.m_gameRuning = false;
				return 0;
			}

			WindowDraw();
		}
		else if (object_main.m_gameRuning == false)
		{
			addition.clickToPlay(object_main);
			object_main.m_window.clear();
			the_map.display(object_main);
			addition.display(shop, object_main);

			object_main.m_window.display();
		}
	}
	return 0;
}