#include "SpriteSheetSplitter.h"


HIMAGELIST SplitSpriteSheet(LPCWSTR imageFileName, LPCWSTR maskFileName, int cellSizeY, int cellSizeX) {
    if (imageFileName == NULL || cellSizeX == 0 || cellSizeY == 0)
        return 0;

    int isMasked = maskFileName != NULL;

    HBITMAP spriteSheet = LoadImageW(NULL, imageFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if (spriteSheet == NULL)
        return 0;

    BITMAP bm;
    GetObject(spriteSheet, sizeof(bm), &bm);

    int cellCountX = (bm.bmWidth / cellSizeX);
    int cellCountY = (bm.bmHeight / cellSizeY);

    HIMAGELIST imageList = ImageList_Create(cellSizeX, cellSizeY, ILC_COLOR24 | (isMasked ? ILC_MASK : 0), cellCountX * cellCountY, 0);

    HDC spriteSheetHDC = CreateCompatibleDC(NULL);
    HDC imageHDC = CreateCompatibleDC(NULL);
    HBITMAP imageBM = CreateCompatibleBitmap(GetDC(NULL), cellSizeX, cellSizeY);

    if (spriteSheetHDC == 0 || imageHDC == 0 || imageBM == 0)
        return 0;

    SelectObject(spriteSheetHDC, spriteSheet);

    HBITMAP imageT = NULL;

    if (isMasked) {
        HBITMAP maskSpriteSheet = LoadImageW(NULL, maskFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        HDC maskSpriteSheetHDC = CreateCompatibleDC(NULL);
        HDC maskHDC = CreateCompatibleDC(NULL);

        HBITMAP maskBM = CreateCompatibleBitmap(GetDC(NULL), cellSizeX, cellSizeY);

        if (maskSpriteSheet == 0 || maskSpriteSheetHDC == 0 || maskHDC == 0 || maskBM == 0)
            return 0;

        SelectObject(maskSpriteSheetHDC, maskSpriteSheet);
        HBITMAP maskT = NULL;

        for (int y = 0; y < cellCountY; y++) {
            for (int x = 0; x < cellCountX; x++) {
                imageT = SelectObject(imageHDC, imageBM);
                maskT = SelectObject(maskHDC, maskBM);
                BitBlt(imageHDC, 0, 0, cellSizeX, cellSizeY, spriteSheetHDC, cellSizeX * x, cellSizeY * y, SRCCOPY);
                BitBlt(maskHDC, 0, 0, cellSizeX, cellSizeY, maskSpriteSheetHDC, cellSizeX * x, cellSizeY * y, SRCCOPY);
                SelectObject(imageHDC, imageT);
                SelectObject(maskHDC, maskT);
                if (ImageList_Add(imageList, imageBM, maskBM) == -1)
                    return 0;
            }
        }

        DeleteDC(maskSpriteSheetHDC);
        DeleteDC(maskHDC);
        DeleteObject(maskSpriteSheet);
        DeleteObject(maskBM);
        DeleteObject(maskT);
    }
    else {
        for (int y = 0; y < cellCountY; y++) {
            for (int x = 0; x < cellCountX; x++) {
                imageT = SelectObject(imageHDC, imageBM);
                BitBlt(imageHDC, 0, 0, cellSizeX, cellSizeY, spriteSheetHDC, cellSizeX * x, cellSizeY * y, SRCCOPY);
                SelectObject(imageHDC, imageT);
                if (ImageList_Add(imageList, imageBM, NULL) == -1)
                    return 0;
            }
        }
    }
    DeleteDC(spriteSheetHDC);
    DeleteDC(imageHDC);
    DeleteObject(imageBM);
    DeleteObject(imageT);
    DeleteObject(spriteSheet);

    return imageList;
}