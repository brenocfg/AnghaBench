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
typedef  struct vlc_http_msg const vlc_http_msg ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg const*) ; 
 char* vlc_http_msg_format (struct vlc_http_msg const*,size_t*,int) ; 
 scalar_t__ vlc_http_msg_get_status (struct vlc_http_msg const*) ; 
 scalar_t__ vlc_http_msg_h2_frame (struct vlc_http_msg const*,int,int) ; 
 struct vlc_http_msg const* vlc_http_msg_headers (char*) ; 
 int /*<<< orphan*/ * vlc_http_msg_read (struct vlc_http_msg const*) ; 

__attribute__((used)) static void check_msg(struct vlc_http_msg *in,
                      void (*cb)(const struct vlc_http_msg *))
{
    struct vlc_http_msg *out;
    char *m1;
    size_t len;

    cb(in);

    m1 = vlc_http_msg_format(in, &len, false);
    assert(m1 != NULL);
    assert(strlen(m1) == len);
    out = vlc_http_msg_headers(m1);
    fprintf(stderr, "%s", m1);
    free(m1);
    /* XXX: request parsing not implemented/needed yet */
    if (vlc_http_msg_get_status(in) >= 0)
    {
        assert(out != NULL);
        cb(out);
        vlc_http_msg_destroy(out);
    }

    out = (struct vlc_http_msg *)vlc_http_msg_h2_frame(in, 1, true);
    assert(out != NULL);
    cb(out);
    assert(vlc_http_msg_read(out) == NULL);
    vlc_http_msg_destroy(out);

    cb(in);
    vlc_http_msg_destroy(in);
}