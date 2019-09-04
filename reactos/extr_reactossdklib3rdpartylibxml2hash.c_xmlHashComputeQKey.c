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
typedef  TYPE_1__* xmlHashTablePtr ;
typedef  int xmlChar ;
struct TYPE_3__ {unsigned long size; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long
xmlHashComputeQKey(xmlHashTablePtr table,
		   const xmlChar *prefix, const xmlChar *name,
		   const xmlChar *prefix2, const xmlChar *name2,
		   const xmlChar *prefix3, const xmlChar *name3) {
    unsigned long value = 0L;
    char ch;

#ifdef HASH_RANDOMIZATION
    value = table->random_seed;
#endif
    if (prefix != NULL)
	value += 30 * (*prefix);
    else
	value += 30 * (*name);

    if (prefix != NULL) {
	while ((ch = *prefix++) != 0) {
	    value = value ^ ((value << 5) + (value >> 3) + (unsigned long)ch);
	}
	value = value ^ ((value << 5) + (value >> 3) + (unsigned long)':');
    }
    if (name != NULL) {
	while ((ch = *name++) != 0) {
	    value = value ^ ((value << 5) + (value >> 3) + (unsigned long)ch);
	}
    }
    value = value ^ ((value << 5) + (value >> 3));
    if (prefix2 != NULL) {
	while ((ch = *prefix2++) != 0) {
	    value = value ^ ((value << 5) + (value >> 3) + (unsigned long)ch);
	}
	value = value ^ ((value << 5) + (value >> 3) + (unsigned long)':');
    }
    if (name2 != NULL) {
	while ((ch = *name2++) != 0) {
	    value = value ^ ((value << 5) + (value >> 3) + (unsigned long)ch);
	}
    }
    value = value ^ ((value << 5) + (value >> 3));
    if (prefix3 != NULL) {
	while ((ch = *prefix3++) != 0) {
	    value = value ^ ((value << 5) + (value >> 3) + (unsigned long)ch);
	}
	value = value ^ ((value << 5) + (value >> 3) + (unsigned long)':');
    }
    if (name3 != NULL) {
	while ((ch = *name3++) != 0) {
	    value = value ^ ((value << 5) + (value >> 3) + (unsigned long)ch);
	}
    }
    return (value % table->size);
}