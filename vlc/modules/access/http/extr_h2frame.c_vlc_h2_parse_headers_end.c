#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sid; scalar_t__ eos; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  decoder; } ;
struct vlc_h2_parser {TYPE_2__ headers; int /*<<< orphan*/  parser; TYPE_1__* cbs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stream_end ) (void*) ;int /*<<< orphan*/  (* stream_headers ) (void*,int,char const***) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_COMPRESSION_ERROR ; 
 int VLC_H2_MAX_HEADERS ; 
 int /*<<< orphan*/  VLC_H2_REFUSED_STREAM ; 
 int /*<<< orphan*/  free (char*) ; 
 int hpack_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char***,int) ; 
 int /*<<< orphan*/  stub1 (void*,int,char const***) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_parse_generic ; 
 int vlc_h2_stream_error (struct vlc_h2_parser*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* vlc_h2_stream_lookup (struct vlc_h2_parser*,scalar_t__) ; 

__attribute__((used)) static int vlc_h2_parse_headers_end(struct vlc_h2_parser *p)
{
    char *headers[VLC_H2_MAX_HEADERS][2];

    /* TODO: limit total decompressed size of the headers list */
    int n = hpack_decode(p->headers.decoder, p->headers.buf, p->headers.len,
                         headers, VLC_H2_MAX_HEADERS);
    if (n > VLC_H2_MAX_HEADERS)
    {
        for (unsigned i = 0; i < VLC_H2_MAX_HEADERS; i++)
        {
            free(headers[i][0]);
            free(headers[i][1]);
        }
        n = -1;
    }
    if (n < 0)
        return vlc_h2_parse_error(p, VLC_H2_COMPRESSION_ERROR);

    void *s = vlc_h2_stream_lookup(p, p->headers.sid);
    int val = 0;

    if (s != NULL)
    {
        const char *ch[n ? n : 1][2];

        for (int i = 0; i < n; i++)
            ch[i][0] = headers[i][0], ch[i][1] = headers[i][1];

        p->cbs->stream_headers(s, n, ch);

        if (p->headers.eos)
            p->cbs->stream_end(s);
    }
    else
        /* NOTE: The specification implies that the error should be sent for
         * the first header frame. But we actually want to receive the whole
         * fragmented headers block, to preserve the HPACK decoder state.
         * So we send the error at the last header frame instead. */
        val = vlc_h2_stream_error(p, p->headers.sid, VLC_H2_REFUSED_STREAM);

    for (int i = 0; i < n; i++)
    {
        free(headers[i][0]);
        free(headers[i][1]);
    }

    p->parser = vlc_h2_parse_generic;
    p->headers.sid = 0;
    return val;
}