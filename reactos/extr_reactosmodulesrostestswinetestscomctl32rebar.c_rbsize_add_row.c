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
struct TYPE_3__ {int* cyRowHeights; size_t nRows; } ;
typedef  TYPE_1__ rbsize_result_t ;

/* Variables and functions */

__attribute__((used)) static void rbsize_add_row(rbsize_result_t *rbsr, int rowHeight) {
    rbsr->cyRowHeights[rbsr->nRows] = rowHeight;
    rbsr->nRows++;
}