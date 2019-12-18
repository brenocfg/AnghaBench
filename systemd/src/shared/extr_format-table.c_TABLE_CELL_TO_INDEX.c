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
typedef  int /*<<< orphan*/  TableCell ;

/* Variables and functions */
 size_t PTR_TO_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t TABLE_CELL_TO_INDEX(TableCell *cell) {
        size_t i;

        assert(cell);

        i = PTR_TO_SIZE(cell);
        assert(i > 0);

        return i-1;
}