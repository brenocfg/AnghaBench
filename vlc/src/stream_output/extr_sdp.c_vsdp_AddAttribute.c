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
typedef  int /*<<< orphan*/  va_list ;
struct vlc_memstream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,char const*) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char*) ; 
 int /*<<< orphan*/  vlc_memstream_vprintf (struct vlc_memstream*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vsdp_AddAttribute(struct vlc_memstream *restrict stream,
                              const char *name, const char *fmt, va_list ap)
{
    if (fmt == NULL)
    {
        vlc_memstream_printf(stream, "a=%s\r\n", name);
        return;
    }
    vlc_memstream_printf(stream, "a=%s:", name);
    vlc_memstream_vprintf(stream, fmt, ap);
    vlc_memstream_puts(stream, "\r\n");
}