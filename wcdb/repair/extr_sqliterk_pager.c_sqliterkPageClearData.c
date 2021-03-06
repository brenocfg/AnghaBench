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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ sqliterk_page ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkOSFree (int /*<<< orphan*/ *) ; 

int sqliterkPageClearData(sqliterk_page *page)
{
    if (!page) {
        return SQLITERK_MISUSE;
    }
    if (page->data) {
        sqliterkOSFree(page->data);
        page->data = NULL;
    }
    return SQLITERK_OK;
}