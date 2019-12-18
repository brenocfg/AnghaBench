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
typedef  int uint8_t ;
struct vlc_a52_bitstream_info {int i_fscod; int i_bsid; int i_bsmod; int i_acmod; int i_lfeon; int i_frmsizcod; } ;
struct TYPE_3__ {int i_extra; int /*<<< orphan*/  p_extra; } ;
typedef  TYPE_1__ mux_extradata_builder_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 size_t VLC_A52_MIN_HEADER_SIZE ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  bs_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bs_write_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  malloc (int) ; 
 scalar_t__ vlc_a52_ParseAc3BitstreamInfo (struct vlc_a52_bitstream_info*,int const*,size_t) ; 

__attribute__((used)) static void ac3_extradata_builder_Feed(mux_extradata_builder_t *m,
                                       const uint8_t *p_data, size_t i_data)
{
    if(m->i_extra || i_data < VLC_A52_MIN_HEADER_SIZE ||
       p_data[0] != 0x0B || p_data[1] != 0x77)
        return;

    struct vlc_a52_bitstream_info bsi;
    if(vlc_a52_ParseAc3BitstreamInfo(&bsi, &p_data[4], /* start code + CRC */
                                     VLC_A52_MIN_HEADER_SIZE - 4 ) != VLC_SUCCESS)
        return;

    m->p_extra = malloc(3);
    if(!m->p_extra)
        return;
    m->i_extra = 3;

    bs_t s;
    bs_write_init(&s, m->p_extra, m->i_extra);
    bs_write(&s, 2, bsi.i_fscod);
    bs_write(&s, 5, bsi.i_bsid);
    bs_write(&s, 3, bsi.i_bsmod);
    bs_write(&s, 3, bsi.i_acmod);
    bs_write(&s, 1, bsi.i_lfeon);
    bs_write(&s, 5, bsi.i_frmsizcod >> 1); // bit_rate_code
    bs_write(&s, 5, 0); // reserved
}