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
struct TYPE_2__ {int size; int allocated; scalar_t__* data; } ;
struct sltg_typelib {TYPE_1__ name_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  chat (char*,char const*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__* xrealloc (scalar_t__*,int) ; 

__attribute__((used)) static int add_name(struct sltg_typelib *sltg, const char *name)
{
    int name_offset = sltg->name_table.size;
    int new_size = sltg->name_table.size + strlen(name) + 1 + 8;
    int aligned_size;

    chat("add_name: %s\n", name);

    aligned_size = (new_size + 0x1f) & ~0x1f;
    if (aligned_size - new_size < 4)
        new_size = aligned_size;
    else
        new_size = (new_size + 1) & ~1;

    if (new_size > sltg->name_table.allocated)
    {
        sltg->name_table.allocated = max(sltg->name_table.allocated * 2, new_size);
        sltg->name_table.data = xrealloc(sltg->name_table.data, sltg->name_table.allocated);
    }

    memset(sltg->name_table.data + sltg->name_table.size, 0xff, 8);
    strcpy(sltg->name_table.data + sltg->name_table.size + 8, name);
    sltg->name_table.size = new_size;
    sltg->name_table.data[sltg->name_table.size - 1] = 0; /* clear alignment */

    return name_offset;
}