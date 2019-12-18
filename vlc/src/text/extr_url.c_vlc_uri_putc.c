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
struct vlc_memstream {int dummy; } ;

/* Variables and functions */
 scalar_t__ isurisafe (int) ; 
 scalar_t__ isurisubdelim (int) ; 
 int /*<<< orphan*/ * strchr (char const*,int) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,unsigned char) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,int) ; 

__attribute__((used)) static void vlc_uri_putc(struct vlc_memstream *s, int c, const char *extras)
{
    if (isurisafe(c) || isurisubdelim(c) || (strchr(extras, c) != NULL))
        vlc_memstream_putc(s, c);
    else
        vlc_memstream_printf(s, "%%%02hhX", (unsigned char)c);
}