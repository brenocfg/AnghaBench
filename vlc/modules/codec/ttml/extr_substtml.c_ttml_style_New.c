#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {double i_value; int /*<<< orphan*/  unit; } ;
struct TYPE_12__ {void* unit; } ;
struct TYPE_11__ {void* unit; } ;
struct TYPE_10__ {void* unit; } ;
struct TYPE_14__ {void* unit; } ;
struct TYPE_15__ {int /*<<< orphan*/  font_style; TYPE_4__ font_size; TYPE_3__ origin_v; TYPE_2__ origin_h; TYPE_1__ extent_v; TYPE_5__ extent_h; } ;
typedef  TYPE_6__ ttml_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  STYLE_NO_DEFAULTS ; 
 int /*<<< orphan*/  TTML_UNIT_CELL ; 
 void* TTML_UNIT_UNKNOWN ; 
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 int /*<<< orphan*/  text_style_Create (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ttml_style_t * ttml_style_New( )
{
    ttml_style_t *p_ttml_style = calloc( 1, sizeof( ttml_style_t ) );
    if( unlikely( !p_ttml_style ) )
        return NULL;

    p_ttml_style->extent_h.unit = TTML_UNIT_UNKNOWN;
    p_ttml_style->extent_v.unit = TTML_UNIT_UNKNOWN;
    p_ttml_style->origin_h.unit = TTML_UNIT_UNKNOWN;
    p_ttml_style->origin_v.unit = TTML_UNIT_UNKNOWN;
    p_ttml_style->font_size.i_value = 1.0;
    p_ttml_style->font_size.unit = TTML_UNIT_CELL;
    p_ttml_style->font_style = text_style_Create( STYLE_NO_DEFAULTS );
    if( unlikely( !p_ttml_style->font_style ) )
    {
        free( p_ttml_style );
        return NULL;
    }
    return p_ttml_style;
}