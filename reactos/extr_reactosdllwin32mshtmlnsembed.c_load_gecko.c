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
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MESSAGE (char*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  cs_load_gecko ; 
 int /*<<< orphan*/  init_xpcom (int /*<<< orphan*/ *) ; 
 scalar_t__ install_wine_gecko () ; 
 scalar_t__ load_wine_gecko (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pCompMgr ; 

BOOL load_gecko(void)
{
    PRUnichar gre_path[MAX_PATH];
    BOOL ret = FALSE;

    static DWORD loading_thread;

    TRACE("()\n");

    /* load_gecko may be called recursively */
    if(loading_thread == GetCurrentThreadId())
        return pCompMgr != NULL;

    EnterCriticalSection(&cs_load_gecko);

    if(!loading_thread) {
        loading_thread = GetCurrentThreadId();

#ifdef __REACTOS__
        if(load_wine_gecko(gre_path))
#else
        if(load_wine_gecko(gre_path)
           || (install_wine_gecko() && load_wine_gecko(gre_path)))
#endif
            ret = init_xpcom(gre_path);
        else
           MESSAGE("Could not load wine-gecko. HTML rendering will be disabled.\n");
    }else {
        ret = pCompMgr != NULL;
    }

    LeaveCriticalSection(&cs_load_gecko);

    return ret;
}