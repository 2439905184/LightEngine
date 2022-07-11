#ifndef SCREEN_WINDOW_H
#define SCREEN_WINDOW_H

class ScreenWindow{
    public:
    int width = 0,height = 0;
    public:
    static ScreenWindow* getScreenWindow();
    void setScreenWidth(int width);
    void setScreenHeight(int height);
    int getScreenWidth() const;
    int getScreenHeight() const;
};

#endif
