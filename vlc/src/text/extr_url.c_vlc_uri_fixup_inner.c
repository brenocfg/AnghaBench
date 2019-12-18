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
struct vlc_memstream {char* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isurihex (char const) ; 
 scalar_t__ isurisafe (unsigned char) ; 
 scalar_t__ isurisubdelim (unsigned char) ; 
 int /*<<< orphan*/ * strchr (char const*,unsigned char) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,unsigned char) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,unsigned char) ; 

__attribute__((used)) static char *vlc_uri_fixup_inner(const char *str, const char *extras)
{
    assert(str && extras);

    bool encode_percent = false;
    for (size_t i = 0; str[i] != '\0'; i++)
        if (str[i] == '%' && !(isurihex(str[i+1]) && isurihex(str[i+2])))
        {
            encode_percent = true;
            break;
        }

    struct vlc_memstream stream;

    vlc_memstream_open(&stream);

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        unsigned char c = str[i];

        if (isurisafe(c) || isurisubdelim(c) || (strchr(extras, c) != NULL)
         || (c == '%' && !encode_percent))
            vlc_memstream_putc(&stream, c);
        else
            vlc_memstream_printf(&stream, "%%%02hhX", c);
    }

    if (vlc_memstream_close(&stream))
        return NULL;
    return stream.ptr;
}