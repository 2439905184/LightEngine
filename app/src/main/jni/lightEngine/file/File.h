#ifndef FILE_H
#define FILE_H

#include <android/asset_manager.h>

class File{
    public:
    AAssetManager* assetManager;
    public:
    static File* getFile(){
        static File* file;
        if(file == 0){
            file = new File();
        }
        return file;
    }
    void readAssetTexture(const char* path,int* w,int* h,int* n,unsigned char** image);
    void readAssetFile(const char* path,long& size,char** data);
};

#endif
