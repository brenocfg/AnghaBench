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
typedef  size_t UINT ;
struct TYPE_4__ {int /*<<< orphan*/  EntryNumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  DoEntry (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 size_t _countof (TYPE_1__*) ; 
 TYPE_1__* s_Entries ; 

__attribute__((used)) static void Test_PathFindOnPathW(void)
{
    UINT i;

    for (i = 0; i < _countof(s_Entries); ++i)
    {
        DoEntry(s_Entries[i].EntryNumber, &s_Entries[i], NULL);
    }
}