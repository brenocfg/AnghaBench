#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dwError; int /*<<< orphan*/  dwResult; } ;
typedef  TYPE_1__ INTERNET_ASYNC_RESULT ;
typedef  int DWORD ;

/* Variables and functions */
#define  INTERNET_STATUS_REQUEST_COMPLETE 128 
 char const* wine_dbg_sprintf (char*,void*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *debugstr_status_info(DWORD status, void *info)
{
    switch(status) {
    case INTERNET_STATUS_REQUEST_COMPLETE: {
        INTERNET_ASYNC_RESULT *iar = info;
        return wine_dbg_sprintf("{%s, %d}", wine_dbgstr_longlong(iar->dwResult), iar->dwError);
    }
    default:
        return wine_dbg_sprintf("%p", info);
    }
}