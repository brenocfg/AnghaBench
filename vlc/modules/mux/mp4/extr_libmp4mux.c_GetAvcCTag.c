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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  h264_sequence_parameter_set_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int const PROFILE_H264_HIGH ; 
 int const PROFILE_H264_HIGH_10 ; 
 int const PROFILE_H264_HIGH_422 ; 
 int const PROFILE_H264_HIGH_444 ; 
 int const PROFILE_H264_HIGH_444_PREDICTIVE ; 
 int const PROFILE_H264_MAIN ; 
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,size_t,int const*) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int /*<<< orphan*/  h264_AnnexB_get_spspps (int const*,size_t,int const**,size_t*,int const**,size_t*,int const**,size_t*) ; 
 int /*<<< orphan*/ * h264_decode_sps (int const*,size_t,int) ; 
 scalar_t__ h264_get_chroma_luma (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  h264_release_sps (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bo_t *GetAvcCTag(const uint8_t *p_extra, size_t i_extra)
{
    bo_t    *avcC = box_new("avcC");/* FIXME use better value */
    if(!avcC)
        return NULL;
    const uint8_t *p_sps, *p_pps, *p_ext;
    size_t i_sps_size, i_pps_size, i_ext_size;

    if(! h264_AnnexB_get_spspps(p_extra, i_extra,
                        &p_sps, &i_sps_size,
                        &p_pps, &i_pps_size,
                        &p_ext, &i_ext_size ) )
    {
        p_sps = p_pps = p_ext = NULL;
        i_sps_size = i_pps_size = i_ext_size = 0;
    }

    bo_add_8(avcC, 1);      /* configuration version */
    bo_add_8(avcC, i_sps_size > 3 ? p_sps[1] : PROFILE_H264_MAIN);
    bo_add_8(avcC, i_sps_size > 3 ? p_sps[2] : 64);
    bo_add_8(avcC, i_sps_size > 3 ? p_sps[3] : 30);       /* level, 5.1 */
    bo_add_8(avcC, 0xff);   /* 0b11111100 | lengthsize = 0x11 */

    bo_add_8(avcC, 0xe0 | (i_sps_size > 0 ? 1 : 0));   /* 0b11100000 | sps_count */
    if (i_sps_size > 0) {
        bo_add_16be(avcC, i_sps_size);
        bo_add_mem(avcC, i_sps_size, p_sps);
    }

    bo_add_8(avcC, (i_pps_size > 0 ? 1 : 0));   /* pps_count */
    if (i_pps_size > 0) {
        bo_add_16be(avcC, i_pps_size);
        bo_add_mem(avcC, i_pps_size, p_pps);
    }

    if( i_sps_size > 3 &&
       (p_sps[1] == PROFILE_H264_HIGH ||
        p_sps[1] == PROFILE_H264_HIGH_10 ||
        p_sps[1] == PROFILE_H264_HIGH_422 ||
        p_sps[1] == PROFILE_H264_HIGH_444 ||
        p_sps[1] == PROFILE_H264_HIGH_444_PREDICTIVE) )
    {
        h264_sequence_parameter_set_t *p_spsdata = h264_decode_sps( p_sps, i_sps_size, true );
        if( p_spsdata )
        {
            uint8_t data[3];
            if( h264_get_chroma_luma( p_spsdata, &data[0], &data[1], &data[2]) )
            {
                bo_add_8(avcC, 0xFC | data[0]);
                bo_add_8(avcC, 0xF8 | (data[1] - 8));
                bo_add_8(avcC, 0xF8 | (data[2] - 8));
                bo_add_8(avcC, (i_ext_size > 0 ? 1 : 0));
                if (i_ext_size > 0) {
                    bo_add_16be(avcC, i_ext_size);
                    bo_add_mem(avcC, i_ext_size, p_ext);
                }
            }
            h264_release_sps( p_spsdata );
        }
    }

    return avcC;
}