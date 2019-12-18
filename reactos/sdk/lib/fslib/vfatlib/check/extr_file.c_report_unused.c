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
struct TYPE_4__ {scalar_t__ type; scalar_t__ name; struct TYPE_4__* first; struct TYPE_4__* next; } ;
typedef  TYPE_1__ FDSC ;

/* Variables and functions */
 scalar_t__ fdt_drop ; 
 scalar_t__ fdt_none ; 
 char* file_name (unsigned char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void report_unused(FDSC * this)
{
    FDSC *next;

    while (this) {
	next = this->next;
	if (this->first)
	    report_unused(this->first);
	else if (this->type != fdt_none)
	    printf("Warning: did not %s file %s\n", this->type == fdt_drop ?
		   "drop" : "undelete", file_name((unsigned char *)this->name));
	free(this);
	this = next;
    }
}