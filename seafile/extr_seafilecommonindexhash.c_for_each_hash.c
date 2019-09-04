#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hash_table_entry {void* ptr; } ;
struct hash_table {unsigned int size; struct hash_table_entry* array; } ;

/* Variables and functions */

int for_each_hash(const struct hash_table *table, int (*fn)(void *, void *), void *data)
{
    int sum = 0;
    unsigned int i;
    unsigned int size = table->size;
    struct hash_table_entry *array = table->array;

    for (i = 0; i < size; i++) {
	    void *ptr = array->ptr;
	    array++;
	    if (ptr) {
		    int val = fn(ptr, data);
		    if (val < 0)
			    return val;
		    sum += val;
	    }
    }
    return sum;
}