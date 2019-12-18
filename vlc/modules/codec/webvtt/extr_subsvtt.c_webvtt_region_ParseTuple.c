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
struct TYPE_3__ {int b_scroll_up; int /*<<< orphan*/  i_lines_max_scroll; int /*<<< orphan*/  viewport_anchor_y; int /*<<< orphan*/  viewport_anchor_x; int /*<<< orphan*/  anchor_y; int /*<<< orphan*/  anchor_x; int /*<<< orphan*/  f_width; int /*<<< orphan*/  psz_id; } ;
typedef  TYPE_1__ webvtt_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  WEBVTT_REGION_LINES_COUNT ; 
 int /*<<< orphan*/  __MIN (int,int /*<<< orphan*/ ) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_percent (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_percent_tuple (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static void webvtt_region_ParseTuple( webvtt_region_t *p_region,
                                      const char *psz_key, const char *psz_value )
{
    if( !strcmp( psz_key, "id" ) )
    {
        free( p_region->psz_id );
        p_region->psz_id = strdup( psz_value );
    }
    else if( !strcmp( psz_key, "width" ) )
    {
        parse_percent( psz_value, &p_region->f_width );
    }
    else if( !strcmp( psz_key, "regionanchor" ) )
    {
        parse_percent_tuple( psz_value, &p_region->anchor_x,
                                        &p_region->anchor_y );
    }
    else if( !strcmp( psz_key, "viewportanchor" ) )
    {
        parse_percent_tuple( psz_value, &p_region->viewport_anchor_x,
                                        &p_region->viewport_anchor_y );
    }
    else if( !strcmp( psz_key, "lines" ) )
    {
        int i = atoi( psz_value );
        if( i > 0 )
            p_region->i_lines_max_scroll = __MIN(i, WEBVTT_REGION_LINES_COUNT);
    }
    else if( !strcmp( psz_key, "scroll" ) )
    {
        p_region->b_scroll_up = !strcmp( psz_value, "up" );
    }
}