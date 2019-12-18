#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* emh; scalar_t__ on_disk; } ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  TYPE_1__ ENHMETAFILEOBJ ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UnmapViewOfFile (TYPE_1__*) ; 
 TYPE_1__* free_gdi_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL EMF_Delete_HENHMETAFILE( HENHMETAFILE hmf )
{
    ENHMETAFILEOBJ *metaObj = free_gdi_handle( hmf );

    if(!metaObj) return FALSE;

    if(metaObj->on_disk)
        UnmapViewOfFile( metaObj->emh );
    else
        HeapFree( GetProcessHeap(), 0, metaObj->emh );
    return HeapFree( GetProcessHeap(), 0, metaObj );
}