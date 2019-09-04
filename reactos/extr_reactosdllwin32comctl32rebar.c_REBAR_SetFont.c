#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ uNumBands; int /*<<< orphan*/  hFont; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int /*<<< orphan*/  REBAR_BAND ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HFONT ;

/* Variables and functions */
 int /*<<< orphan*/ * REBAR_GetBand (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  REBAR_Layout (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_ValidateBand (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
REBAR_SetFont (REBAR_INFO *infoPtr, HFONT font)
{
    REBAR_BAND *lpBand;
    UINT i;

    infoPtr->hFont = font;

    /* revalidate all bands to change sizes of text in headers of bands */
    for (i=0; i<infoPtr->uNumBands; i++) {
        lpBand = REBAR_GetBand(infoPtr, i);
	REBAR_ValidateBand (infoPtr, lpBand);
    }

    REBAR_Layout(infoPtr);
    return 0;
}