#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* y; void* x; } ;
typedef  TYPE_1__ POINT ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  BEZIERMAXDEPTH ; 
 void* BEZIERSHIFTUP (void*) ; 
 int BEZIER_INITBUFSIZE ; 
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GDI_InternalBezier (TYPE_1__*,TYPE_1__**,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  TAG_BEZIER ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

POINT *GDI_Bezier( const POINT *Points, INT count, INT *nPtsOut )
{
    POINT *out;
    INT Bezier, dwOut = BEZIER_INITBUFSIZE, i;

    if (count == 1 || (count - 1) % 3 != 0) {
        DPRINT1("Invalid no. of points %d\n", count);
	return NULL;
    }
    *nPtsOut = 0;

    out = ExAllocatePoolWithTag(PagedPool, dwOut * sizeof(POINT), TAG_BEZIER);
    if (!out) return NULL;

    for(Bezier = 0; Bezier < (count-1)/3; Bezier++) {
	POINT ptBuf[4];
	memcpy(ptBuf, Points + Bezier * 3, sizeof(POINT) * 4);
	for(i = 0; i < 4; i++) {
	    ptBuf[i].x = BEZIERSHIFTUP(ptBuf[i].x);
	    ptBuf[i].y = BEZIERSHIFTUP(ptBuf[i].y);
	}
        GDI_InternalBezier( ptBuf, &out, &dwOut, nPtsOut, BEZIERMAXDEPTH );
    }
    DPRINT("Produced %d points\n", *nPtsOut);
    return out;
}