#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_11__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_8__ {scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int /*<<< orphan*/  elpColor; int /*<<< orphan*/  lopnColor; TYPE_1__ lopnWidth; int /*<<< orphan*/  elpWidth; int /*<<< orphan*/  elpPenStyle; int /*<<< orphan*/  lopnStyle; } ;
struct TYPE_10__ {TYPE_7__ emr; scalar_t__ ihPen; TYPE_2__ lopn; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  TYPE_2__ EXTLOGPEN ;
typedef  TYPE_3__ EMRCREATEPEN ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ EMFDRV_AddHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  EMR_CREATEPEN ; 
 int GetObjectW (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static DWORD EMFDRV_CreatePenIndirect(PHYSDEV dev, HPEN hPen)
{
    EMRCREATEPEN emr;
    DWORD index = 0;

    if (!GetObjectW( hPen, sizeof(emr.lopn), &emr.lopn ))
    {
        /* must be an extended pen */
        EXTLOGPEN *elp;
        INT size = GetObjectW( hPen, 0, NULL );

        if (!size) return 0;

        elp = HeapAlloc( GetProcessHeap(), 0, size );

        GetObjectW( hPen, size, elp );
        /* FIXME: add support for user style pens */
        emr.lopn.lopnStyle = elp->elpPenStyle;
        emr.lopn.lopnWidth.x = elp->elpWidth;
        emr.lopn.lopnWidth.y = 0;
        emr.lopn.lopnColor = elp->elpColor;

        HeapFree( GetProcessHeap(), 0, elp );
    }

    emr.emr.iType = EMR_CREATEPEN;
    emr.emr.nSize = sizeof(emr);
    emr.ihPen = index = EMFDRV_AddHandle( dev, hPen );

    if(!EMFDRV_WriteRecord( dev, &emr.emr ))
        index = 0;
    return index;
}