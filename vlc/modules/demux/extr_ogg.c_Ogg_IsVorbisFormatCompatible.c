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
 scalar_t__ memcmp (void const*,void const*,unsigned int) ; 
 scalar_t__ xiph_SplitHeaders (unsigned int*,void const**,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool Ogg_IsVorbisFormatCompatible( const es_format_t *p_new, const es_format_t *p_old )
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

    bool b_match = i_new_count == i_old_count;
    for( unsigned i = 0; i < i_new_count && b_match; i++ )
    {
        /* Ignore vorbis comment */
        if( i == 1 )
            continue;
        if( pi_new_size[i] != pi_old_size[i] ||
            memcmp( pp_new_data[i], pp_old_data[i], pi_new_size[i] ) )
            b_match = false;
    }

    return b_match;
}