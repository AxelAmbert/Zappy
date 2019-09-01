//
// Created by akacprzak on 6/19/19.
//

#ifndef PSU_ZAPPY_2018_SCENE_H
#define PSU_ZAPPY_2018_SCENE_H

namespace graphical {
   /**
    * @class Scene
    * @brief Scene class
    */
    class IScene {
    public:
        virtual ~IScene() {};
        virtual void run(size_t &sceneIndex) = 0;
    };
}

#endif //PSU_ZAPPY_2018_SCENE_H
