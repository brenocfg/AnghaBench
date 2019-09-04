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
typedef  size_t WORD ;

/* Variables and functions */
 scalar_t__ memcmp (size_t*,size_t*,int) ; 
 size_t number_of_subtables_with_diffs ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t** subtables_with_diffs ; 

__attribute__((used)) static WORD find_subtable_with_diffs(WORD *table, WORD *subtable)
{
    WORD index;

    for(index = 0; index < number_of_subtables_with_diffs; index++) {
        if(memcmp(subtables_with_diffs[index], subtable, 16 * sizeof(WORD)) == 0) {
            return index;
        }
    }

    if(number_of_subtables_with_diffs >= 4096) {
        printf("Could not add new subtable with diffs, storage is full\n");
        return 0;
    }

    subtables_with_diffs[number_of_subtables_with_diffs] = subtable;
    number_of_subtables_with_diffs++;

    return index;
}