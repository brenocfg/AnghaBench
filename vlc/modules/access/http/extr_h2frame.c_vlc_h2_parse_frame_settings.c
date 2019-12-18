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
struct vlc_h2_parser {int /*<<< orphan*/  opaque; TYPE_1__* cbs; } ;
struct vlc_h2_frame {int dummy; } ;
struct TYPE_2__ {int (* settings_done ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setting ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GetDWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GetWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VLC_H2_FRAME_SIZE_ERROR ; 
 size_t VLC_H2_MAX_FRAME ; 
 int /*<<< orphan*/  VLC_H2_PROTOCOL_ERROR ; 
 int VLC_H2_SETTINGS_ACK ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int vlc_h2_frame_flags (struct vlc_h2_frame*) ; 
 int /*<<< orphan*/ * vlc_h2_frame_payload (struct vlc_h2_frame*) ; 
 int vlc_h2_parse_error (struct vlc_h2_parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_h2_parse_frame_settings(struct vlc_h2_parser *p,
                                       struct vlc_h2_frame *f, size_t len,
                                       uint_fast32_t id)
{
    const uint8_t *ptr = vlc_h2_frame_payload(f);

    if (id != 0)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_PROTOCOL_ERROR);
    }

    if (len % 6 || len > VLC_H2_MAX_FRAME)
    {
        free(f);
        return vlc_h2_parse_error(p, VLC_H2_FRAME_SIZE_ERROR);
    }

    if (vlc_h2_frame_flags(f) & VLC_H2_SETTINGS_ACK)
    {
        free(f);
        if (len != 0)
            return vlc_h2_parse_error(p, VLC_H2_FRAME_SIZE_ERROR);
        /* Ignore ACKs for now as we never change settings. */
        return 0;
    }

    for (const uint8_t *end = ptr + len; ptr < end; ptr += 6)
        p->cbs->setting(p->opaque, GetWBE(ptr), GetDWBE(ptr + 2));

    free(f);
    return p->cbs->settings_done(p->opaque);
}