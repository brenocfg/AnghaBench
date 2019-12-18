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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  es_format_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  Ogg_ExtractComments (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int XIPH_MAX_HEADER_COUNT ; 
 scalar_t__ xiph_SplitHeaders (unsigned int*,void const**,unsigned int*,unsigned int,void const*) ; 

__attribute__((used)) static void Ogg_ExtractXiphMeta( demux_t *p_demux, es_format_t *p_fmt,
                                 const void *p_headers, unsigned i_headers, unsigned i_skip )
{
    unsigned pi_size[XIPH_MAX_HEADER_COUNT];
    const void *pp_data[XIPH_MAX_HEADER_COUNT];
    unsigned i_count;

    if( xiph_SplitHeaders( pi_size, pp_data, &i_count, i_headers, p_headers ) )
        return;
    /* TODO how to handle multiple comments properly ? */
    if( i_count >= 2 && pi_size[1] > i_skip )
    {
        Ogg_ExtractComments( p_demux, p_fmt,
                             (const uint8_t *)pp_data[1] + i_skip,
                             pi_size[1] - i_skip );
    }
}