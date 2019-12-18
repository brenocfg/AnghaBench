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
struct window_mode_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  window_copy_copy_buffer (struct window_mode_entry*,char const*,char*,size_t) ; 
 char* window_copy_get_selection (struct window_mode_entry*,size_t*) ; 

__attribute__((used)) static void
window_copy_copy_selection(struct window_mode_entry *wme, const char *prefix)
{
	char	*buf;
	size_t	 len;

	buf = window_copy_get_selection(wme, &len);
	if (buf != NULL)
		window_copy_copy_buffer(wme, prefix, buf, len);
}