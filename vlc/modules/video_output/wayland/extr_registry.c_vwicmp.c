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
struct vlc_wl_interface {int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vwicmp(const void *a, const void *b)
{
    const struct vlc_wl_interface *ia = a;
    const struct vlc_wl_interface *ib = b;

    return strcmp(ia->interface, ib->interface);
}