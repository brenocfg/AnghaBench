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
typedef  size_t WORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/ * debug_type ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dump_types(const char* header, WORD *types, int start, int end)
{
    int i, len = 0;
    TRACE("%s:",header);
    for (i = start; i < end && len < 200; i++)
    {
        TRACE(" %s",debug_type[types[i]]);
        len += strlen(debug_type[types[i]])+1;
    }
    if (i != end)
        TRACE("...");
    TRACE("\n");
}