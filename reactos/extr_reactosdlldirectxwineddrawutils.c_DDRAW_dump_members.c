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
struct member_info {int val; int offset; int /*<<< orphan*/  (* func ) (char const*) ;int /*<<< orphan*/  name; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char const*) ; 

__attribute__((used)) static void DDRAW_dump_members(DWORD flags, const void *data, const struct member_info *mems, size_t num_mems)
{
    unsigned int i;

    for (i=0; i < num_mems; i++)
    {
        if (mems[i].val & flags)
        {
            TRACE(" - %s : ", mems[i].name);
            mems[i].func((const char *)data + mems[i].offset);
        }
    }
}