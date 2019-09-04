#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pageno; } ;
typedef  TYPE_1__ sqliterk_page ;

/* Variables and functions */
 int sqliterkPagenoHeaderOffset (int /*<<< orphan*/ ) ; 

int sqliterkPageHeaderOffset(sqliterk_page *page)
{
    if (!page) {
        return 0;
    }
    return sqliterkPagenoHeaderOffset(page->pageno);
}