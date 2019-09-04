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
struct TYPE_4__ {struct TYPE_4__* first; int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ FDSC ;

/* Variables and functions */
 int /*<<< orphan*/  MSDOS_NAME ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

FDSC **file_cd(FDSC ** curr, char *fixed)
{
    FDSC **walk;

    if (!curr || !*curr)
	return NULL;
    for (walk = curr; *walk; walk = &(*walk)->next)
	if (!strncmp((*walk)->name, fixed, MSDOS_NAME) && (*walk)->first)
	    return &(*walk)->first;
    return NULL;
}