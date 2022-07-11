#ifndef WINDOW_H
#define WINDOW_H

class GameSprite;

class Window{
    public:
        virtual void init(GameSprite* gameSprite) = 0;
};

#endif
