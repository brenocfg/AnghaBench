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
struct ar_archive_rar_filters {int /*<<< orphan*/  vm; int /*<<< orphan*/  progs; int /*<<< orphan*/  stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rar_delete_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rar_delete_program (int /*<<< orphan*/ ) ; 

void rar_clear_filters(struct ar_archive_rar_filters *filters)
{
    rar_delete_filter(filters->stack);
    rar_delete_program(filters->progs);
    free(filters->vm);
}