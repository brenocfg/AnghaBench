#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ iBitmap; } ;
struct TYPE_12__ {int /*<<< orphan*/  nNumBitmaps; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ TBUTTON_INFO ;
typedef  scalar_t__ INT ;
typedef  int IMAGE_LIST_TYPE ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/ * GETDEFIMAGELIST (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GETDISIMAGELIST (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETHIMLID (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/ * GETHOTIMAGELIST (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (scalar_t__) ; 
#define  IMAGE_LIST_DEFAULT 130 
#define  IMAGE_LIST_DISABLED 129 
#define  IMAGE_LIST_HOT 128 
 scalar_t__ I_IMAGECALLBACK ; 
 scalar_t__ I_IMAGENONE ; 
 int /*<<< orphan*/  LOWORD (scalar_t__) ; 
 scalar_t__ TOOLBAR_GetBitmapIndex (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  TOOLBAR_IsValidBitmapIndex (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HIMAGELIST
TOOLBAR_GetImageListForDrawing (const TOOLBAR_INFO *infoPtr, TBUTTON_INFO *btnPtr,
                                IMAGE_LIST_TYPE imagelist, INT * index)
{
    HIMAGELIST himl;

    if (!TOOLBAR_IsValidBitmapIndex(infoPtr,btnPtr->iBitmap)) {
	if (btnPtr->iBitmap == I_IMAGENONE) return NULL;
	WARN("bitmap for ID %d, index %d is not valid, number of bitmaps in imagelist: %d\n",
	    HIWORD(btnPtr->iBitmap), LOWORD(btnPtr->iBitmap), infoPtr->nNumBitmaps);
	return NULL;
    }

    if ((*index = TOOLBAR_GetBitmapIndex(infoPtr, btnPtr)) < 0) {
	if ((*index == I_IMAGECALLBACK) ||
	    (*index == I_IMAGENONE)) return NULL;
	ERR("TBN_GETDISPINFO returned invalid index %d\n",
	    *index);
	return NULL;
    }

    switch(imagelist)
    {
    case IMAGE_LIST_DEFAULT:
        himl = GETDEFIMAGELIST(infoPtr, GETHIMLID(infoPtr, btnPtr->iBitmap));
        break;
    case IMAGE_LIST_HOT:
        himl = GETHOTIMAGELIST(infoPtr, GETHIMLID(infoPtr, btnPtr->iBitmap));
        break;
    case IMAGE_LIST_DISABLED:
        himl = GETDISIMAGELIST(infoPtr, GETHIMLID(infoPtr, btnPtr->iBitmap));
        break;
    default:
        himl = NULL;
        FIXME("Shouldn't reach here\n");
    }

    if (!himl)
       TRACE("no image list\n");

    return himl;
}