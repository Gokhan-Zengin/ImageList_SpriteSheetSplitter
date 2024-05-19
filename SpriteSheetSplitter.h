#pragma once

#include <windows.h>
#include <stdio.h>
#include <commctrl.h>

/*
    DESCRIPTION

    maskFileName is optional, if NULL ImageList will be created wihtout mask
    cells will be splittet line by line, starting from top left

    RETURNS
    returns NULL if unsuccesfull else HIMAGELIST
*/
HIMAGELIST SplitSpriteSheet(LPCWSTR imageFileName, LPCWSTR maskFileName, int cellSizeY, int cellSizeX);