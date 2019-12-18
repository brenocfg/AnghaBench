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
struct vlc_wl_interface {int /*<<< orphan*/  globals; int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct vlc_wl_interface* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t const) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vlc_wl_interface *vlc_wl_interface_create(const char *iface)
{
    const size_t len = strlen(iface) + 1;
    struct vlc_wl_interface *vi = malloc(sizeof (*vi) + len);

    if (likely(vi != NULL))
    {
        memcpy(vi->interface, iface, len);
        wl_list_init(&vi->globals);
    }
    return vi;
}