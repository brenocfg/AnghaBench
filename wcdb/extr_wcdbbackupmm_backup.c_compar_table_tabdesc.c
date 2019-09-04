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
struct TYPE_2__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ mm_backup_tabdesc ;

/* Variables and functions */
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compar_table_tabdesc(const void *key, const void *value)
{
    return strcmp((const char *) key,
                  ((const mm_backup_tabdesc *) value)->table);
}