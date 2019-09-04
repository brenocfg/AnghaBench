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
typedef  int WORD ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int number_of_subtables_with_offsets ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * subtables_with_offsets ; 

__attribute__((used)) static WORD find_subtable_with_offsets(WORD *subtable)
{
    WORD index;

    for(index = 0; index < number_of_subtables_with_offsets; index++) {
        if(memcmp(&subtables_with_offsets[index * 16], subtable, 16 * sizeof(WORD)) == 0) {
            return index;
        }
    }

    if(number_of_subtables_with_offsets >= 4096) {
        printf("Could not add new subtable with offsets, storage is full\n");
        return 0;
    }

    memcpy(&subtables_with_offsets[number_of_subtables_with_offsets * 16], subtable, 16 * sizeof(WORD));
    number_of_subtables_with_offsets++;

    return index;
}