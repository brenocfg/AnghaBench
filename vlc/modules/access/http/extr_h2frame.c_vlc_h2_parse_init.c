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
struct vlc_h2_parser_cbs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * decoder; scalar_t__ len; int /*<<< orphan*/ * buf; scalar_t__ sid; } ;
struct vlc_h2_parser {int rcwd_size; TYPE_1__ headers; int /*<<< orphan*/  parser; struct vlc_h2_parser_cbs const* cbs; void* opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_MAX_HEADER_TABLE ; 
 int /*<<< orphan*/  free (struct vlc_h2_parser*) ; 
 int /*<<< orphan*/ * hpack_decode_init (int /*<<< orphan*/ ) ; 
 struct vlc_h2_parser* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_parse_preface ; 

struct vlc_h2_parser *vlc_h2_parse_init(void *ctx,
                                        const struct vlc_h2_parser_cbs *cbs)
{
    struct vlc_h2_parser *p = malloc(sizeof (*p));
    if (unlikely(p == NULL))
        return NULL;

    p->opaque = ctx;
    p->cbs = cbs;
    p->parser = vlc_h2_parse_preface;
    p->headers.sid = 0;
    p->headers.buf = NULL;
    p->headers.len = 0;
    p->headers.decoder = hpack_decode_init(VLC_H2_MAX_HEADER_TABLE);
    if (unlikely(p->headers.decoder == NULL))
    {
        free(p);
        return NULL;
    }
    p->rcwd_size = 65535; /* initial per-connection value */
    return p;
}