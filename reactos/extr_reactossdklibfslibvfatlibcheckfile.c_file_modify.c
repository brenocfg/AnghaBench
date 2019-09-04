#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; char* name; struct TYPE_6__* next; } ;
typedef  TYPE_1__ FDSC ;

/* Variables and functions */
 unsigned char DELETED_FLAG ; 
 int /*<<< orphan*/  die (char*) ; 
#define  fdt_drop 129 
#define  fdt_undelete 128 
 TYPE_1__** file_find (TYPE_1__**,char*) ; 
 char* file_name (unsigned char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void file_modify(FDSC ** curr, char *fixed)
{
    FDSC **this, *next;

    if (!(this = file_find(curr, fixed)))
	die("Internal error: file_find failed");
    switch ((*this)->type) {
    case fdt_drop:
	printf("Dropping %s\n", file_name((unsigned char *)fixed));
	*(unsigned char *)fixed = DELETED_FLAG;
	break;
    case fdt_undelete:
	*fixed = *(*this)->name;
	printf("Undeleting %s\n", file_name((unsigned char *)fixed));
	break;
    default:
	die("Internal error: file_modify");
    }
    next = (*this)->next;
    free(*this);
    *this = next;
}