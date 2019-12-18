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
typedef  int /*<<< orphan*/  htab_trav ;
typedef  int /*<<< orphan*/  htab_t ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 int htab_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_expand (int /*<<< orphan*/ ) ; 
 size_t htab_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_traverse_noresize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
htab_traverse (htab_t htab, htab_trav callback, PTR info)
{
  size_t size = htab_size (htab);
  if (htab_elements (htab) * 8 < size && size > 32)
    htab_expand (htab);

  htab_traverse_noresize (htab, callback, info);
}