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
typedef  int /*<<< orphan*/  libvlc_renderer_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_renderer_item_flags (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  libvlc_renderer_item_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  libvlc_renderer_item_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_log (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
item_event(const libvlc_renderer_item_t *p_item, const char *psz_event)
{
    test_log("item %s: name: '%s', type: '%s', flags: 0x%X\n", psz_event,
             libvlc_renderer_item_name(p_item), libvlc_renderer_item_type(p_item),
             libvlc_renderer_item_flags(p_item));
}