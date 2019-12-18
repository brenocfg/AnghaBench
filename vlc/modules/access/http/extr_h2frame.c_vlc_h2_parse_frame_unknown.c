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
typedef  scalar_t__ uint_fast32_t ;
struct vlc_h2_parser {int dummy; } ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_FRAME_SIZE_ERROR ; 
 size_t VLC_H2_MAX_FRAME ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 
 int vlc_h2_stream_error (struct vlc_h2_parser*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_h2_parse_frame_unknown(struct vlc_h2_parser *p,
                                      struct vlc_h2_frame *f, size_t len,
                                      uint_fast32_t id)
{
    free(f);

    if (len > VLC_H2_MAX_FRAME)
    {
        if (id == 0)
            return vlc_h2_parse_error(p, VLC_H2_FRAME_SIZE_ERROR);
        return vlc_h2_stream_error(p, id, VLC_H2_FRAME_SIZE_ERROR);
    }

    /* Ignore frames of unknown type as specified. */
    return 0;
}