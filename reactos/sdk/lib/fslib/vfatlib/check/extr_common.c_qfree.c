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
struct TYPE_4__ {struct TYPE_4__* data; void* next; } ;
typedef  TYPE_1__ LINK ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vffree (TYPE_1__*) ; 

void qfree(void **root)
{
    LINK *this;

    while (*root) {
	this = (LINK *) * root;
	*root = this->next;
#ifndef __REACTOS__
	free(this->data);
	free(this);
#else
	vffree(this->data);
	vffree(this);
#endif
    }
}