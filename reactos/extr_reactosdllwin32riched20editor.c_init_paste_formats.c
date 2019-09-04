#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cfFormat; } ;
struct paste_format {scalar_t__ name; TYPE_1__ fmt; } ;

/* Variables and functions */
 scalar_t__ RegisterClipboardFormatW (scalar_t__) ; 
 struct paste_format* paste_formats ; 

__attribute__((used)) static void init_paste_formats(void)
{
    struct paste_format *format;
    static int done;

    if (!done)
    {
        for (format = paste_formats; format->fmt.cfFormat; format++)
        {
            if (format->name)
                format->fmt.cfFormat = RegisterClipboardFormatW( format->name );
        }
        done = 1;
    }
}