#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ParseTypedefData {int err_idx; int /*<<< orphan*/  ptr; TYPE_1__* errors; } ;
struct TYPE_2__ {unsigned int line; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void stabs_pts_push(struct ParseTypedefData* ptd, unsigned line)
{
    assert(ptd->err_idx < sizeof(ptd->errors) / sizeof(ptd->errors[0]));
    ptd->errors[ptd->err_idx].line = line;
    ptd->errors[ptd->err_idx].ptr = ptd->ptr;
    ptd->err_idx++;
}