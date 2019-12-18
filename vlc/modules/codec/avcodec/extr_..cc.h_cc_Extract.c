#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  enum cc_payload_type_e { ____Placeholder_cc_payload_type_e } cc_payload_type_e ;
struct TYPE_4__ {scalar_t__ i_payload_type; int i_payload_other_count; scalar_t__ i_data; int b_reorder; } ;
typedef  TYPE_1__ cc_data_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 scalar_t__ CC_MAX_DATA_SIZE ; 
 int CC_PAYLOAD_DVD ; 
 int CC_PAYLOAD_GA94 ; 
 scalar_t__ CC_PAYLOAD_NONE ; 
 int CC_PAYLOAD_RAW ; 
 int CC_PAYLOAD_REPLAYTV ; 
 int const CC_PKT_BYTE0 (int const) ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,int const*,int) ; 
 int bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cc_AppendData (TYPE_1__*,int const,int const*) ; 

__attribute__((used)) static inline void cc_Extract( cc_data_t *c, enum cc_payload_type_e i_payload_type,
                               bool b_top_field_first, const uint8_t *p_src, int i_src )
{
    if( c->i_payload_type != CC_PAYLOAD_NONE && c->i_payload_type != i_payload_type )
    {
        c->i_payload_other_count++;
        if( c->i_payload_other_count < 50 )
            return;
    }
    c->i_payload_type        = i_payload_type;
    c->i_payload_other_count = 0;

    if( i_payload_type == CC_PAYLOAD_RAW )
    {
        for( int i = 0; i + 2 < i_src; i += 3 )
        {
            if( c->i_data + 3 > CC_MAX_DATA_SIZE )
                break;

            const uint8_t *cc = &p_src[i];
            cc_AppendData( c, cc[0], &cc[1] );
        }
        c->b_reorder = true;
    }
    else if( i_payload_type == CC_PAYLOAD_GA94 )
    {
        /* cc_data()
         *          u1 reserved(1)
         *          u1 process_cc_data_flag
         *          u1 additional_data_flag
         *          u5 cc_count
         *          u8 reserved(1111 1111)
         *          for cc_count
         *              u5 marker bit(1111 1)
         *              u1 cc_valid
         *              u2 cc_type
         *              u8 cc_data_1
         *              u8 cc_data_2
         *          u8 marker bit(1111 1111)
         *          if additional_data_flag
         *              unknown
         */
        /* cc_type:
         *  0x00: field 1
         *  0x01: field 2
         */
        const uint8_t *cc = &p_src[0];
        const int i_count_cc = cc[0]&0x1f;
        int i;

        if( !(cc[0]&0x40) ) // process flag
            return;
        if( i_src < 1+1 + i_count_cc*3 + 1)  // broken packet
            return;
        if( i_count_cc <= 0 )   // no cc present
            return;
        if( cc[2+i_count_cc * 3] != 0xff )  // marker absent
            return;
        cc += 2;

        for( i = 0; i < i_count_cc; i++, cc += 3 )
        {
            if( c->i_data + 3 > CC_MAX_DATA_SIZE )
                break;

            cc_AppendData( c, cc[0], &cc[1] );
        }
        c->b_reorder = true;
    }
    else if( i_payload_type == CC_PAYLOAD_DVD )
    {
        /* user_data
         *          (u32 stripped earlier)
         *          u32 (0x43 0x43 0x01 0xf8)
         *          u1 caption_odd_field_first (CC1/CC2)
         *          u1 caption_filler
         *          u5 cc_block_count  (== cc_count / 2)
         *          u1 caption_extra_field_added (because odd cc_count)
         *          for cc_block_count * 2 + caption_extra_field_added
         *              u7 cc_filler_1
         *              u1 cc_field_is_odd
         *              u8 cc_data_1
         *              u8 cc_data_2
         */
        const int b_truncate = p_src[4] & 0x01;
        const int i_field_first = (p_src[4] & 0x80) ? 0 : 1;
        const int i_count_cc2 = (p_src[4] >> 1) & 0xf;
        const uint8_t *cc = &p_src[5];
        int i;

        if( i_src < 4+1+6*i_count_cc2 - ( b_truncate ? 3 : 0) )
            return;
        for( i = 0; i < i_count_cc2; i++ )
        {
            int j;
            for( j = 0; j < 2; j++, cc += 3 )
            {
                const int i_field = j == i_field_first ? 0 : 1;

                if( b_truncate && i == i_count_cc2 - 1 && j == 1 )
                    break;
                if( (cc[0] & 0xfe) != 0xfe )
                    continue;
                if( c->i_data + 3 > CC_MAX_DATA_SIZE )
                    continue;

                cc_AppendData( c, CC_PKT_BYTE0(i_field), &cc[1] );
            }
        }
        c->b_reorder = false;
    }
    else if( i_payload_type == CC_PAYLOAD_REPLAYTV )
    {
        const uint8_t *cc = &p_src[0];
        for( int i_cc_count = i_src >> 2; i_cc_count > 0;
             i_cc_count--, cc += 4 )
        {
            if( c->i_data + 3 > CC_MAX_DATA_SIZE )
                return;
            uint8_t i_field = (cc[0] & 0x02) >> 1;
            cc_AppendData( c, CC_PKT_BYTE0(i_field), &cc[2] );
        }
        c->b_reorder = false;
    }
    else /* CC_PAYLOAD_SCTE20 */
    {
        /* user_data(2)
         *          (u32 stripped earlier)
         *          u16 p_cc_scte20
         *          u5 cc_count
         *          for cc_count
         *              u2 cc_priority
         *              u2 cc_field_num
         *              u5 cc_line_offset
         *              u8 cc_data_1[1:8]
         *              u8 cc_data_2[1:8]
         *              u1 marker bit
         *          un additional_realtimevideodata
         *          un reserved
         */
        bs_t s;
        bs_init( &s, &p_src[2], i_src - 2 );
        const int i_cc_count = bs_read( &s, 5 );
        for( int i = 0; i < i_cc_count; i++ )
        {
            bs_skip( &s, 2 );
            const int i_field_idx = bs_read( &s, 2 );
            bs_skip( &s, 5 );
            uint8_t cc[2];
            for( int j = 0; j < 2; j++ )
            {
                cc[j] = 0;
                for( int k = 0; k < 8; k++ )
                    cc[j] |= bs_read( &s, 1 ) << k;
            }
            bs_skip( &s, 1 );

            if( i_field_idx == 0 )
                continue;
            if( c->i_data + 2*3 > CC_MAX_DATA_SIZE )
                continue;

            /* 1,2,3 -> 0,1,0. I.E. repeated field 3 is merged with field 1 */
            int i_field = ((i_field_idx - 1) & 1);
            if (!b_top_field_first)
                i_field ^= 1;

            cc_AppendData( c, CC_PKT_BYTE0(i_field), &cc[0] );
        }
        c->b_reorder = true;
    }
}