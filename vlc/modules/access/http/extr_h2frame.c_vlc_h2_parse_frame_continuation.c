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
typedef  scalar_t__ uint_fast32_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ sid; } ;
struct vlc_h2_parser {TYPE_1__ headers; } ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int VLC_H2_CONTINUATION_END_HEADERS ; 
 int /*<<< orphan*/  VLC_H2_FRAME_SIZE_ERROR ; 
 size_t VLC_H2_MAX_FRAME ; 
 int /*<<< orphan*/  VLC_H2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 int vlc_h2_frame_flags (struct vlc_h2_frame*) ; 
 int /*<<< orphan*/ * vlc_h2_frame_payload (struct vlc_h2_frame*) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 
 int vlc_h2_parse_headers_append (struct vlc_h2_parser*,int /*<<< orphan*/  const*,size_t) ; 
 int vlc_h2_parse_headers_end (struct vlc_h2_parser*) ; 

__attribute__((used)) static int vlc_h2_parse_frame_continuation(struct vlc_h2_parser *p,
                                           struct vlc_h2_frame *f, size_t len,
                                           uint_fast32_t id)
{
    const uint8_t *ptr = vlc_h2_frame_payload(f);

    /* Stream ID must match with the previous frame. */
    if (id == 0 || id != p->headers.sid)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_PROTOCOL_ERROR);
    }

    if (len > VLC_H2_MAX_FRAME)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_FRAME_SIZE_ERROR);
    }

    int ret = vlc_h2_parse_headers_append(p, ptr, len);

    if (ret == 0 && (vlc_h2_frame_flags(f) & VLC_H2_CONTINUATION_END_HEADERS))
        ret = vlc_h2_parse_headers_end(p);

    free(f);
    return 0;
}