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
struct TYPE_6__ {int flags; scalar_t__ wExtra; } ;
typedef  TYPE_1__ WND ;
typedef  int /*<<< orphan*/  MDICLIENTINFO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_MDIWND ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* WIN_GetPtr (int /*<<< orphan*/ ) ; 
 int WIN_ISMDICLIENT ; 
 int /*<<< orphan*/  WIN_ReleasePtr (TYPE_1__*) ; 
 TYPE_1__* WND_DESKTOP ; 
 TYPE_1__* WND_OTHER_PROCESS ; 

__attribute__((used)) static MDICLIENTINFO *get_client_info( HWND client )
{
#ifdef __REACTOS__
    return (MDICLIENTINFO *)GetWindowLongPtr(client, GWLP_MDIWND);
#else
    MDICLIENTINFO *ret = NULL;
    WND *win = WIN_GetPtr( client );
    if (win)
    {
        if (win == WND_OTHER_PROCESS || win == WND_DESKTOP)
        {
            if (IsWindow(client)) WARN( "client %p belongs to other process\n", client );
            return NULL;
        }
        if (win->flags & WIN_ISMDICLIENT)
            ret = (MDICLIENTINFO *)win->wExtra;
        else
            WARN( "%p is not an MDI client\n", client );
        WIN_ReleasePtr( win );
    }
    return ret;
#endif
}