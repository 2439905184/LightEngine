#include "File.h"
#include <stdlib.h>
#include <string.h>
#include <lightEngine/texture/image/stb_image.h>

void File::readAssetFile(const char* path,long& size,char** data){
    AAsset* asset = AAssetManager_open(this->assetManager, path, AASSET_MODE_UNKNOWN);
    size = AAsset_getLength(asset);
    *data = (char*) malloc (sizeof(char)*size);
    AAsset_read (asset, *data, size);
    AAsset_close(asset);
}

void File::readAssetTexture(const char* path,int* width,int* height,int* n,unsigned char** data){
   AAsset *pathAsset = AAssetManager_open(this->assetManager,path, AASSET_MODE_UNKNOWN);
   if(pathAsset){
       off_t assetLength = AAsset_getLength(pathAsset);
       unsigned char *fileData = (unsigned char *) AAsset_getBuffer(pathAsset);
       *data = stbi_load_from_memory(fileData,assetLength, width, height,n, 0);
       AAsset_close(pathAsset);
   }
}

