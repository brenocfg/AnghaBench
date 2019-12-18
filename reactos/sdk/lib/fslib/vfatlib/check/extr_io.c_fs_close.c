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
struct TYPE_4__ {struct TYPE_4__* data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ CHANGE ;

/* Variables and functions */
 TYPE_1__* changes ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 scalar_t__ did_change ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  fs_flush () ; 
 int /*<<< orphan*/  pdie (char*) ; 

int fs_close(int write)
{
    CHANGE *next;
    int changed;

    changed = ! !changes;
    if (write)
	fs_flush();
    else
	while (changes) {
	    next = changes->next;
	    free(changes->data);
	    free(changes);
	    changes = next;
	}
    if (close(fd) < 0)
	pdie("closing filesystem");
    return changed || did_change;
}