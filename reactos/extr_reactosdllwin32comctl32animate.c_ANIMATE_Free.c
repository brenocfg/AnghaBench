#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* fnICClose ) (scalar_t__) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  transparentColor; scalar_t__ currFrame; scalar_t__ nLoop; scalar_t__ nToFrame; scalar_t__ nFromFrame; int /*<<< orphan*/  ash; int /*<<< orphan*/  mah; scalar_t__ hbmPrevFrame; int /*<<< orphan*/ * outdata; int /*<<< orphan*/ * indata; int /*<<< orphan*/ * outbih; int /*<<< orphan*/ * inbih; scalar_t__ hic; int /*<<< orphan*/ * lpIndex; scalar_t__ hRes; scalar_t__ hMMio; } ;
typedef  TYPE_1__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ANIMATE_COLOR_NONE ; 
 int /*<<< orphan*/  ANIMATE_DoStop (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  FreeResource (scalar_t__) ; 
 TYPE_2__ fnIC ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmioClose (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void ANIMATE_Free(ANIMATE_INFO *infoPtr)
{
    if (infoPtr->hMMio)
    {
        ANIMATE_DoStop(infoPtr);
        mmioClose(infoPtr->hMMio, 0);
        if (infoPtr->hRes)
        {
            FreeResource(infoPtr->hRes);
            infoPtr->hRes = 0;
        }
        heap_free (infoPtr->lpIndex);
        infoPtr->lpIndex = NULL;
        if (infoPtr->hic)
        {
            fnIC.fnICClose(infoPtr->hic);
            infoPtr->hic = 0;
        }
        heap_free (infoPtr->inbih);
        infoPtr->inbih = NULL;
        heap_free (infoPtr->outbih);
        infoPtr->outbih = NULL;
        heap_free (infoPtr->indata);
        infoPtr->indata = NULL;
        heap_free (infoPtr->outdata);
        infoPtr->outdata = NULL;
        if (infoPtr->hbmPrevFrame)
        {
            DeleteObject(infoPtr->hbmPrevFrame);
            infoPtr->hbmPrevFrame = 0;
        }

        memset(&infoPtr->mah, 0, sizeof(infoPtr->mah));
        memset(&infoPtr->ash, 0, sizeof(infoPtr->ash));
        infoPtr->nFromFrame = infoPtr->nToFrame = infoPtr->nLoop = infoPtr->currFrame = 0;
    }
    infoPtr->transparentColor = ANIMATE_COLOR_NONE;
}