//
// Created by pewie on 16.09.2023.
//

#include "MainExecutor.h"
#include "BaseClasses/PositionableEntity.h"

MainExecutor::MainExecutor()
        : object_main(), event(), the_map(), addition(object_main), mactangle(the_map, object_main), dacler(),
          bedler(object_main),
          shop(object_main, the_map),
          dacler_offert(dacler, dacler.getHimTexture(), 4080, 500, 300, 1.5, object_main, 1),
          bedler_offert(bedler, bedler.getHimTexture(), 4080, 1000, 100, 1.5, object_main, 2),
          inputs(&object_main.m_window) {
}

void MainExecutor::start() {
    shop.setSomething(object_main);
    dacler_offert.setSomething(object_main);
    bedler_offert.setSomething(object_main);

    while (object_main.m_window.isOpen()) {
        //InputManager::checkEvents();
        if (object_main.m_gameRuning) {
            shop.daclers.back().set(the_map, object_main);
            shop.bedlers.back().set(the_map, object_main);
            for (int i = 1; shop.daclers.size() > i; i++) {
                shop.daclers[i].work(the_map, object_main);
            }
            for (int i = 1; shop.mactangles.size() > i; i++) {
                shop.mactangles[i].moving(the_map);

                if (addition.takeHp(the_map, shop.mactangles[i]))
                    shop.mactangles.erase(shop.mactangles.begin());
            }
            for (int i = 1; shop.bedlers.size() > i; i++) {
                shop.bedlers[i].work(shop.bedlers[i], the_map, object_main, shop.mactangles);
                if (shop.bedlers[i].addMoney()) {
                    shop.money += 20;
                }
            }
            dacler_offert.offertUseful(shop, object_main);
            bedler_offert.offertUseful(shop, object_main);
            shop.destroyMactangle();
            shop.working(the_map, object_main);
            if (addition.gameOver()) {
                object_main.m_gameRuning = false;
                return;
            }

            object_main.m_window.clear();
            the_map.display(object_main);
            for (int i = 1; shop.daclers.size() > i; i++) {
                shop.daclers[i].textureReset();
                object_main.m_window.draw(shop.daclers[i]);
            }
            for (int i = 1; shop.mactangles.size() > i; i++) {
                shop.mactangles[i].textureReset();
                object_main.m_window.draw(shop.mactangles[i]);
                shop.mactangles[i].displaySomething(object_main);
            }
            for (int i = 1; shop.bedlers.size() > i; i++) {
                shop.bedlers[i].textureReset();
                object_main.m_window.draw(shop.bedlers[i]);
                shop.bedlers[i].display(object_main);
            }
            shop.display(object_main);
            dacler_offert.display(shop, object_main);
            bedler_offert.display(shop, object_main);
            addition.display(shop, object_main);
            object_main.m_window.display();
        } else if (!object_main.m_gameRuning) {
            addition.clickToPlay(object_main);
            object_main.m_window.clear();
            the_map.display(object_main);
            addition.display(shop, object_main);

            object_main.m_window.display();
        }
        //InputManager::clearKeys();
    }

}
