#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int size; int /*<<< orphan*/ * table; scalar_t__ filled; } ;
typedef  TYPE_1__ htab_table ;
typedef  int /*<<< orphan*/  htab_entry ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  isprime (int) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

BOOL htab_create(uint32_t nel, htab_table* htab)
{
	if (htab == NULL) {
		return FALSE;
	}
	if (htab->table != NULL) {
		uprintf("warning: htab_create() was called with a non empty table");
		return FALSE;
	}

	// Change nel to the first prime number not smaller as nel.
	nel |= 1;
	while(!isprime(nel))
		nel += 2;

	htab->size = nel;
	htab->filled = 0;

	// allocate memory and zero out.
	htab->table = (htab_entry*)calloc(htab->size + 1, sizeof(htab_entry));
	if (htab->table == NULL) {
		uprintf("could not allocate space for hash table\n");
		return FALSE;
	}

	return TRUE;
}