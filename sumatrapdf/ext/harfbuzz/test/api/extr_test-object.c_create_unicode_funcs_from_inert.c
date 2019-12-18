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

/* Variables and functions */
 void* hb_unicode_funcs_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unicode_funcs_get_empty () ; 

__attribute__((used)) static void *
create_unicode_funcs_from_inert (void)
{
  return hb_unicode_funcs_create (hb_unicode_funcs_get_empty ());
}