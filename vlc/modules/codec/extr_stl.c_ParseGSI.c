#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_9__ {char* p_extra; scalar_t__ i_extra; } ;
struct TYPE_10__ {TYPE_1__ fmt_in; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_11__ {int i_fps; int cct; } ;
typedef  TYPE_3__ decoder_sys_t ;

/* Variables and functions */
 int CCT_BEGIN ; 
 int CCT_END ; 
 scalar_t__ GSI_BLOCK_SIZE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ParseGSI(decoder_t *dec, decoder_sys_t *p_sys)
{
    uint8_t *header = dec->fmt_in.p_extra;
    if (!header) {
        msg_Err(dec, "NULL EBU header (GSI block)\n");
        return VLC_EGENERIC;
    }

    if (GSI_BLOCK_SIZE != dec->fmt_in.i_extra) {
        msg_Err(dec, "EBU header is not in expected size (%d)\n", dec->fmt_in.i_extra);
        return VLC_EGENERIC;
    }

    char dfc_fps_str[] = { header[6], header[7], '\0' };
    int fps = strtol(dfc_fps_str, NULL, 10);
    if (1 > fps || 60 < fps) {
        msg_Warn(dec, "EBU header contains unsupported DFC fps ('%s'); falling back to 25\n", dfc_fps_str);
        fps = 25;
    }

    int cct = (header[12] << 8) | header[13];
    if (CCT_BEGIN > cct || CCT_END < cct) {
        msg_Err(dec, "EBU header contains illegal CCT (0x%x)\n", cct);
        return VLC_EGENERIC;
    }

    msg_Dbg(dec, "DFC fps=%d, CCT=0x%x", fps, cct);
    p_sys->i_fps = fps;
    p_sys->cct = cct;

    return VLC_SUCCESS;
}