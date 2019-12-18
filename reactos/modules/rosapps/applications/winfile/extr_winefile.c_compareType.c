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
struct TYPE_4__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int TO_DIR ; 
 int TO_FILE ; 
 int TypeOrderFromDirname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compareType(const WIN32_FIND_DATAW* fd1, const WIN32_FIND_DATAW* fd2)
{
	int order1 = fd1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY? TO_DIR: TO_FILE;
	int order2 = fd2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY? TO_DIR: TO_FILE;

	/* Handle "." and ".." as special case and move them at the very first beginning. */
	if (order1==TO_DIR && order2==TO_DIR) {
		order1 = TypeOrderFromDirname(fd1->cFileName);
		order2 = TypeOrderFromDirname(fd2->cFileName);
	}

	return order2==order1? 0: order1<order2? -1: 1;
}