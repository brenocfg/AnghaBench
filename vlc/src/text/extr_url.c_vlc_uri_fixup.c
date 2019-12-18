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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ isurialnum (char const) ; 
 scalar_t__ isurihex (char const) ; 
 int /*<<< orphan*/ * memchr (char*,char const,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_memstream_write (struct vlc_memstream*,char const*,int) ; 
 int /*<<< orphan*/  vlc_uri_putc (struct vlc_memstream*,int /*<<< orphan*/ ,char const*) ; 

char *vlc_uri_fixup(const char *str)
{
    assert(str != NULL);

    /* If percent sign is consistently followed by two hexadecimal digits,
     * then URL encoding must be assumed.
     * Otherwise, the percent sign itself must be URL-encoded.
     */
    bool encode_percent = false;

    for (const char *p = str; *p != '\0'; p++)
        if (p[0] == '%' && !(isurihex(p[1]) && isurihex(p[2])))
        {
            encode_percent = true;
            break;
        }

    struct vlc_memstream stream;
    vlc_memstream_open(&stream);

    /* Handle URI scheme */
    const char *p = str;
    bool absolute = false;
    bool encode_brackets = true;

    while (isurialnum(*p) || memchr("+-.", *p, 3) != NULL)
        vlc_memstream_putc(&stream, *(p++));

    if (p > str && *p == ':')
    {   /* There is an URI scheme, assume an absolute URI. */
        vlc_memstream_putc(&stream, *(p++));
        absolute = true;
        encode_brackets = false;
    }

    /* Handle URI authority */
    if ((absolute || p == str) && strncmp(p, "//", 2) == 0)
    {
        vlc_memstream_write(&stream, p, 2);
        p += 2;
        encode_brackets = true;

        while (memchr("/?#", *p, 4) == NULL)
            vlc_uri_putc(&stream, *(p++), &"%:[]@"[encode_percent]);
    }

    /* Handle URI path and what follows */
    const char *extras = encode_brackets ? "%/?#@" : "%:/?#[]@";

    while (*p != '\0')
        vlc_uri_putc(&stream, *(p++), extras + encode_percent);

    return vlc_memstream_close(&stream) ? NULL : stream.ptr;
}