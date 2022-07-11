#include "ScreenWindow.h"

ScreenWindow* ScreenWindow::getScreenWindow(){
    static ScreenWindow* screenwindow;
    if(screenwindow == 0){
        screenwindow = new ScreenWindow();
    }
    return screenwindow;
}

void ScreenWindow::setScreenWidth(int width){
    this->width = width;
}

void ScreenWindow::setScreenHeight(int height){
    this->height = height;
}

int ScreenWindow::getScreenWidth() const{
    return this->width;
}

int ScreenWindow::getScreenHeight() const{
    return this->height;
}

