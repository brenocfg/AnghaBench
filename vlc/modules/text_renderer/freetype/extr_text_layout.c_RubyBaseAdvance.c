#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_character_count; TYPE_2__* p_character; } ;
typedef  TYPE_3__ line_desc_t ;
struct TYPE_5__ {scalar_t__ xMin; scalar_t__ xMax; } ;
struct TYPE_6__ {scalar_t__ p_ruby; TYPE_1__ bbox; } ;

/* Variables and functions */

__attribute__((used)) static int RubyBaseAdvance( const line_desc_t *p_line, int i_start, int *pi_count )
{
    int i_total = 0;
    *pi_count = 0;
    for( int i = i_start; i < p_line->i_character_count; i++ )
    {
        if( p_line->p_character[i].p_ruby != p_line->p_character[i_start].p_ruby )
            break;
        (*pi_count)++;
        i_total += (p_line->p_character[i].bbox.xMax - p_line->p_character[i].bbox.xMin);
    }
    return i_total;
}