#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ Address; scalar_t__ SourceLine; } ;
typedef  TYPE_1__* PROSSYM_ENTRY ;

/* Variables and functions */

__attribute__((used)) static int
CompareSymEntry(const PROSSYM_ENTRY SymEntry1, const PROSSYM_ENTRY SymEntry2)
{
    if (SymEntry1->Address < SymEntry2->Address)
    {
        return -1;
    }

    if (SymEntry2->Address < SymEntry1->Address)
    {
        return +1;
    }

    if (SymEntry2->SourceLine == 0)
    {
        return -1;
    }

    if (SymEntry1->SourceLine == 0)
    {
        return +1;
    }

    return 0;
}