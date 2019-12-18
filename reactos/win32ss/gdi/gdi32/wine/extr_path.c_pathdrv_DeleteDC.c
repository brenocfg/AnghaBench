#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct path_physdev {int dummy; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct path_physdev*) ; 
 int /*<<< orphan*/  TRUE ; 
 struct path_physdev* get_path_physdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL pathdrv_DeleteDC( PHYSDEV dev )
{
    struct path_physdev *physdev = get_path_physdev( dev );
    DPRINT("pathdrv_DeleteDC dev %p\n",dev);
    HeapFree( GetProcessHeap(), 0, physdev );
    return TRUE;
}