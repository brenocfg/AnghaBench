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
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  G_N_ELEMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_keys ; 
 int /*<<< orphan*/  g_parse_debug_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seafile_debug_set_flags (int /*<<< orphan*/ ) ; 

void
seafile_debug_set_flags_string (const gchar *flags_string)
{
    guint nkeys = G_N_ELEMENTS (debug_keys);

    if (flags_string)
        seafile_debug_set_flags (
            g_parse_debug_string (flags_string, debug_keys, nkeys));
}