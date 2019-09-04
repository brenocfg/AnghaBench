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
struct TYPE_5__ {int length; TYPE_1__* item; } ;
struct TYPE_4__ {size_t* pcls; } ;
typedef  TYPE_2__ IsolatedRun ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/ * debug_type ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iso_dump_types(const char* header, IsolatedRun *iso_run)
{
    int i, len = 0;
    TRACE("%s:",header);
    TRACE("[ ");
    for (i = 0; i < iso_run->length && len < 200; i++)
    {
        TRACE(" %s",debug_type[*iso_run->item[i].pcls]);
        len += strlen(debug_type[*iso_run->item[i].pcls])+1;
    }
    if (i != iso_run->length)
        TRACE("...");
    TRACE(" ]\n");
}