#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int i_flags; int i_timestamp_resolution; int i_timestamp_length; int i_degradation_priority_length; int i_AU_seqnum_length; int i_packet_seqnum_length; void* i_startcomposition_timestamp; void* i_startdecoding_timestamp; void* i_compositionunit_duration; void* i_accessunit_duration; void* i_timescale; void* i_instant_bitrate_length; void* i_AU_length; void* i_OCR_length; void* i_OCR_resolution; } ;
typedef  TYPE_1__ sl_config_descriptor_t ;
struct TYPE_6__ {TYPE_1__* sl_descr; } ;
typedef  TYPE_2__ od_read_params_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 void* ODGetBytes (unsigned int*,int const**,int) ; 
#define  SL_Predefined_Custom 130 
#define  SL_Predefined_MP4 129 
#define  SL_Predefined_NULL 128 
 int USE_DURATION_FLAG ; 
 int USE_TIMESTAMPS_FLAG ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,int const*,unsigned int) ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  od_debug (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static bool OD_SLDesc_Read( vlc_object_t *p_object, unsigned i_data, const uint8_t *p_data,
                             od_read_params_t params )
{
    sl_config_descriptor_t *sl_descr = params.sl_descr;

    uint8_t i_predefined = ODGetBytes( &i_data, &p_data, 1 );
    switch( i_predefined )
    {
    case SL_Predefined_Custom:
        if( i_data < 15 )
            return false;
        sl_descr->i_flags = ODGetBytes( &i_data, &p_data, 1 );
        sl_descr->i_timestamp_resolution = ODGetBytes( &i_data, &p_data, 4 );
        sl_descr->i_OCR_resolution = ODGetBytes( &i_data, &p_data, 4 );
        sl_descr->i_timestamp_length = ODGetBytes( &i_data, &p_data, 1 );
        sl_descr->i_OCR_length = ODGetBytes( &i_data, &p_data, 1 );
        sl_descr->i_AU_length = ODGetBytes( &i_data, &p_data, 1 );
        sl_descr->i_instant_bitrate_length = ODGetBytes( &i_data, &p_data, 1 );
        uint16_t i16 = ODGetBytes( &i_data, &p_data, 2 );
        sl_descr->i_degradation_priority_length = i16 >> 12;
        sl_descr->i_AU_seqnum_length = (i16 >> 7) & 0x1f;
        sl_descr->i_packet_seqnum_length = (i16 >> 2) & 0x1f;
        break;
    case SL_Predefined_NULL:
        memset( sl_descr, 0, sizeof(*sl_descr) );
        sl_descr->i_timestamp_resolution = 1000;
        sl_descr->i_timestamp_length = 32;
        break;
    case SL_Predefined_MP4:
        memset( sl_descr, 0, sizeof(*sl_descr) );
        sl_descr->i_flags = USE_TIMESTAMPS_FLAG;
        break;
    default:
        /* reserved */
        return false;
    }

    if( sl_descr->i_flags & USE_DURATION_FLAG )
    {
        if( i_data < 8 )
            return false;
        sl_descr->i_timescale = ODGetBytes( &i_data, &p_data, 4 );
        sl_descr->i_accessunit_duration = ODGetBytes( &i_data, &p_data, 2 );
        sl_descr->i_compositionunit_duration = ODGetBytes( &i_data, &p_data, 2 );
    }

    if( (sl_descr->i_flags & USE_TIMESTAMPS_FLAG) == 0 )
    {
        bs_t s;
        bs_init( &s, p_data, i_data );
        sl_descr->i_startdecoding_timestamp = bs_read( &s, sl_descr->i_timestamp_length );
        sl_descr->i_startcomposition_timestamp = bs_read( &s, sl_descr->i_timestamp_length );
    }

    od_debug( p_object, "   * read sl desc predefined: 0x%x", i_predefined );
    return true;
}