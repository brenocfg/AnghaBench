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
struct vlc_h2_parser {TYPE_1__* cbs; } ;
struct vlc_h2_frame {int dummy; } ;
struct TYPE_2__ {int (* stream_reset ) (void*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ GetDWBE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_H2_FRAME_SIZE_ERROR ; 
 int /*<<< orphan*/  VLC_H2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 int stub1 (void*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_h2_frame_payload (struct vlc_h2_frame*) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 
 void* vlc_h2_stream_lookup (struct vlc_h2_parser*,scalar_t__) ; 

__attribute__((used)) static int vlc_h2_parse_frame_rst_stream(struct vlc_h2_parser *p,
                                         struct vlc_h2_frame *f, size_t len,
                                         uint_fast32_t id)
{
    if (id == 0)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_PROTOCOL_ERROR);
    }

    if (len != 4)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_FRAME_SIZE_ERROR);
    }

    void *s = vlc_h2_stream_lookup(p, id);
    uint_fast32_t code = GetDWBE(vlc_h2_frame_payload(f));

    free(f);

    if (s == NULL)
        return 0;
    return p->cbs->stream_reset(s, code);
}