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
typedef  TYPE_1__* htab_t ;
typedef  int /*<<< orphan*/  htab_hash ;
typedef  int /*<<< orphan*/  htab_free_with_arg ;
typedef  int /*<<< orphan*/  htab_eq ;
typedef  int /*<<< orphan*/  htab_del ;
typedef  int /*<<< orphan*/  htab_alloc_with_arg ;
struct TYPE_3__ {int /*<<< orphan*/  free_with_arg_f; int /*<<< orphan*/  alloc_with_arg_f; int /*<<< orphan*/  alloc_arg; int /*<<< orphan*/  del_f; int /*<<< orphan*/  eq_f; int /*<<< orphan*/  hash_f; } ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */

void
htab_set_functions_ex (htab_t htab, htab_hash hash_f, htab_eq eq_f,
                       htab_del del_f, PTR alloc_arg,
                       htab_alloc_with_arg alloc_f, htab_free_with_arg free_f)
{
  htab->hash_f = hash_f;
  htab->eq_f = eq_f;
  htab->del_f = del_f;
  htab->alloc_arg = alloc_arg;
  htab->alloc_with_arg_f = alloc_f;
  htab->free_with_arg_f = free_f;
}