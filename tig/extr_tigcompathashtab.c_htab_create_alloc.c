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
typedef  int /*<<< orphan*/  htab_t ;
typedef  int /*<<< orphan*/  htab_hash ;
typedef  int /*<<< orphan*/  htab_free ;
typedef  int /*<<< orphan*/  htab_eq ;
typedef  int /*<<< orphan*/  htab_del ;
typedef  int /*<<< orphan*/  htab_alloc ;

/* Variables and functions */
 int /*<<< orphan*/  htab_create_typed_alloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

htab_t
htab_create_alloc (size_t size, htab_hash hash_f, htab_eq eq_f,
                   htab_del del_f, htab_alloc alloc_f, htab_free free_f)
{
  return htab_create_typed_alloc (size, hash_f, eq_f, del_f, alloc_f, alloc_f,
				  free_f);
}