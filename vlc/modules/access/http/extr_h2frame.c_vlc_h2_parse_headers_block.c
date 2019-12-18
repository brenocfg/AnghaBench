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
typedef  int /*<<< orphan*/  uint_fast32_t ;
struct TYPE_2__ {scalar_t__ sid; } ;
struct vlc_h2_parser {TYPE_1__ headers; } ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ VLC_H2_FRAME_CONTINUATION ; 
 int /*<<< orphan*/  VLC_H2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 scalar_t__ vlc_h2_frame_type (struct vlc_h2_frame*) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 
 int vlc_h2_parse_frame_continuation (struct vlc_h2_parser*,struct vlc_h2_frame*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_h2_parse_headers_block(struct vlc_h2_parser *p,
                                      struct vlc_h2_frame *f, size_t len,
                                      uint_fast32_t id)
{
    assert(p->headers.sid != 0);

    /* After a HEADER, PUSH_PROMISE of CONTINUATION frame without the
     * END_HEADERS flag, must come a CONTINUATION frame. */
    if (vlc_h2_frame_type(f) != VLC_H2_FRAME_CONTINUATION)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_PROTOCOL_ERROR);
    }

    return vlc_h2_parse_frame_continuation(p, f, len, id);
}