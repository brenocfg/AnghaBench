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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  first; scalar_t__ name; } ;
typedef  TYPE_1__ FDSC ;

/* Variables and functions */
 unsigned char DELETED_FLAG ; 
 scalar_t__ MSDOS_NAME ; 
 int /*<<< orphan*/  strncmp (scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static FDSC **file_find(FDSC ** dir, char *fixed)
{
    if (!dir || !*dir)
	return NULL;
    if (*(unsigned char *)fixed == DELETED_FLAG) {
	while (*dir) {
	    if (!strncmp((*dir)->name + 1, fixed + 1, MSDOS_NAME - 1)
		&& !(*dir)->first)
		return dir;
	    dir = &(*dir)->next;
	}
	return NULL;
    }
    while (*dir) {
	if (!strncmp((*dir)->name, fixed, MSDOS_NAME) && !(*dir)->first)
	    return dir;
	dir = &(*dir)->next;
    }
    return NULL;
}