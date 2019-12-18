#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* psz_protocol; char* psz_path; char* psz_option; char* psz_fragment; int /*<<< orphan*/  i_port; int /*<<< orphan*/ * psz_host; int /*<<< orphan*/ * psz_password; int /*<<< orphan*/ * psz_username; } ;
typedef  TYPE_1__ vlc_url_t ;
struct vlc_memstream {char* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ *,char) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char const*,char*,...) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,char) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char*) ; 
 int /*<<< orphan*/  vlc_memstream_write (struct vlc_memstream*,char*,int) ; 
 char* vlc_uri_encode (int /*<<< orphan*/ *) ; 

char *vlc_uri_compose(const vlc_url_t *uri)
{
    struct vlc_memstream stream;
    char *enc;

    vlc_memstream_open(&stream);

    if (uri->psz_protocol != NULL)
        vlc_memstream_printf(&stream, "%s:", uri->psz_protocol);

    if (uri->psz_host != NULL)
    {
        vlc_memstream_write(&stream, "//", 2);

        if (uri->psz_username != NULL)
        {
            enc = vlc_uri_encode(uri->psz_username);
            if (enc == NULL)
                goto error;

            vlc_memstream_puts(&stream, enc);
            free(enc);

            if (uri->psz_password != NULL)
            {
                enc = vlc_uri_encode(uri->psz_password);
                if (unlikely(enc == NULL))
                    goto error;

                vlc_memstream_printf(&stream, ":%s", enc);
                free(enc);
            }
            vlc_memstream_putc(&stream, '@');
        }

        const char *fmt;

        if (strchr(uri->psz_host, ':') != NULL)
            fmt = (uri->i_port != 0) ? "[%s]:%d" : "[%s]";
        else
            fmt = (uri->i_port != 0) ? "%s:%d" : "%s";
        /* No IDNA decoding here. Seems unnecessary, dangerous even. */
        vlc_memstream_printf(&stream, fmt, uri->psz_host, uri->i_port);
    }

    if (uri->psz_path != NULL)
        vlc_memstream_puts(&stream, uri->psz_path);
    if (uri->psz_option != NULL)
        vlc_memstream_printf(&stream, "?%s", uri->psz_option);
    if (uri->psz_fragment != NULL)
        vlc_memstream_printf(&stream, "#%s", uri->psz_fragment);

    if (vlc_memstream_close(&stream))
        return NULL;
    return stream.ptr;

error:
    if (vlc_memstream_close(&stream) == 0)
        free(stream.ptr);
    return NULL;
}