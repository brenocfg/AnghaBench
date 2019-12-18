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
struct TYPE_4__ {int /*<<< orphan*/  p_extra; int /*<<< orphan*/  i_extra; } ;
typedef  TYPE_1__ es_format_t ;

/* Variables and functions */
 int XIPH_MAX_HEADER_COUNT ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,int) ; 
 scalar_t__ xiph_SplitHeaders (unsigned int*,void const**,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool Ogg_IsOpusFormatCompatible( const es_format_t *p_new,
                                        const es_format_t *p_old )
{
    unsigned pi_new_size[XIPH_MAX_HEADER_COUNT];
    const void *pp_new_data[XIPH_MAX_HEADER_COUNT];
    unsigned i_new_count;

    if( xiph_SplitHeaders(pi_new_size, pp_new_data, &i_new_count, p_new->i_extra, p_new->p_extra ) )
        i_new_count = 0;

    unsigned pi_old_size[XIPH_MAX_HEADER_COUNT];
    const void *pp_old_data[XIPH_MAX_HEADER_COUNT];
    unsigned i_old_count;

    if( xiph_SplitHeaders(pi_old_size, pp_old_data, &i_old_count, p_old->i_extra, p_old->p_extra ) )
        i_old_count = 0;
    bool b_match = false;
    if( i_new_count == i_old_count && i_new_count > 0 )
    {
        static const unsigned char default_map[2] = { 0, 1 };
        const unsigned char *p_old_head;
        unsigned char *p_new_head;
        const unsigned char *p_old_map;
        const unsigned char *p_new_map;
        int i_old_channel_count;
        int i_new_channel_count;
        int i_old_stream_count;
        int i_new_stream_count;
        int i_old_coupled_count;
        int i_new_coupled_count;
        p_old_head = pp_old_data[0];
        i_old_channel_count = i_old_stream_count = i_old_coupled_count = 0;
        p_old_map = default_map;
        if( pi_old_size[0] >= 19 && p_old_head[8] <= 15 )
        {
            i_old_channel_count = p_old_head[9];
            switch( p_old_head[18] )
            {
                case 0:
                    i_old_stream_count = 1;
                    i_old_coupled_count = i_old_channel_count - 1;
                    break;
                case 1:
                    if( pi_old_size[0] >= 21U + i_old_channel_count )
                    {
                        i_old_stream_count = p_old_head[19];
                        i_old_coupled_count = p_old_head[20];
                        p_old_map = p_old_head + 21;
                    }
                    break;
            }
        }
        p_new_head = (unsigned char *)pp_new_data[0];
        i_new_channel_count = i_new_stream_count = i_new_coupled_count = 0;
        p_new_map = default_map;
        if( pi_new_size[0] >= 19 && p_new_head[8] <= 15 )
        {
            i_new_channel_count = p_new_head[9];
            switch( p_new_head[18] )
            {
                case 0:
                    i_new_stream_count = 1;
                    i_new_coupled_count = i_new_channel_count - 1;
                    break;
                case 1:
                    if( pi_new_size[0] >= 21U + i_new_channel_count )
                    {
                        i_new_stream_count = p_new_head[19];
                        i_new_coupled_count = p_new_head[20];
                        p_new_map = p_new_head+21;
                    }
                    break;
            }
        }
        b_match = i_old_channel_count == i_new_channel_count &&
                  i_old_stream_count == i_new_stream_count &&
                  i_old_coupled_count == i_new_coupled_count &&
                  memcmp(p_old_map, p_new_map,
                      i_new_channel_count*sizeof(*p_new_map)) == 0;
    }

    return b_match;
}