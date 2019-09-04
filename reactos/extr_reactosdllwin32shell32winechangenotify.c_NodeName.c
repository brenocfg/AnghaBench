#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {TYPE_1__* apidl; } ;
struct TYPE_4__ {int /*<<< orphan*/  pidl; } ;
typedef  TYPE_2__ NOTIFICATIONLIST ;

/* Variables and functions */
 int MAX_PATH ; 
 scalar_t__ SHGetPathFromIDListW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 char* wine_dbg_sprintf (char*,...) ; 

__attribute__((used)) static const char * NodeName(const NOTIFICATIONLIST *item)
{
    const char *str;
    WCHAR path[MAX_PATH];

    if(SHGetPathFromIDListW(item->apidl[0].pidl, path ))
        str = wine_dbg_sprintf("%s", debugstr_w(path));
    else
        str = wine_dbg_sprintf("<not a disk file>" );
    return str;
}