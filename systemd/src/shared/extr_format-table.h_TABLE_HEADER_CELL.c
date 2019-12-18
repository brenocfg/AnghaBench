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
 int /*<<< orphan*/ * SIZE_TO_PTR (size_t) ; 

__attribute__((used)) static inline TableCell* TABLE_HEADER_CELL(size_t i) {
        return SIZE_TO_PTR(i + 1);
}