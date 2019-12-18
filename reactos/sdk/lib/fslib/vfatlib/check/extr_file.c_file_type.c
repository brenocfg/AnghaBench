#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  FD_TYPE ;
typedef  TYPE_1__ FDSC ;

/* Variables and functions */
 int /*<<< orphan*/  fdt_none ; 
 TYPE_1__** file_find (TYPE_1__**,char*) ; 

FD_TYPE file_type(FDSC ** curr, char *fixed)
{
    FDSC **this;

    if ((this = file_find(curr, fixed)))
	return (*this)->type;
    return fdt_none;
}