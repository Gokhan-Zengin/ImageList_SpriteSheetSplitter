# ImageList_SpriteSheetSplitter

A helper code for splitting spritesheets into a ImageList

# Usage

```
#include "SpriteSheetSplitter.h"

int main(){
    int cellSizeX = 32;
    int cellSizeY = 32;

    HIMAGELIST imageList = SplitSpriteSheet("spriteSheetFile.bmp", "maskSpriteSheetFile.bmp", cellSizeX, cellSizeY);
}
```
