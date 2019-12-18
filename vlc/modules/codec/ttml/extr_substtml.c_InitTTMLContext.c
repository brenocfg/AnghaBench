#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int i_value; void* unit; } ;
struct TYPE_9__ {int i_value; void* unit; } ;
struct TYPE_7__ {unsigned int i_cell_resolution_v; unsigned int i_cell_resolution_h; TYPE_4__ root_extent_v; TYPE_3__ root_extent_h; TYPE_2__* p_rootnode; } ;
typedef  TYPE_1__ ttml_context_t ;
struct TYPE_8__ {int /*<<< orphan*/  attr_dict; } ;
typedef  TYPE_2__ tt_node_t ;

/* Variables and functions */
 unsigned int TTML_DEFAULT_CELL_RESOLUTION_H ; 
 unsigned int TTML_DEFAULT_CELL_RESOLUTION_V ; 
 void* TTML_UNIT_PERCENT ; 
 char const* kVLCDictionaryNotFound ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ttml_read_coords (char const*,TYPE_3__*,TYPE_4__*) ; 
 char* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void InitTTMLContext( tt_node_t *p_rootnode, ttml_context_t *p_ctx )
{
    p_ctx->p_rootnode = p_rootnode;
    /* set defaults required for size/cells computation */
    p_ctx->root_extent_h.i_value = 100;
    p_ctx->root_extent_h.unit = TTML_UNIT_PERCENT;
    p_ctx->root_extent_v.i_value = 100;
    p_ctx->root_extent_v.unit = TTML_UNIT_PERCENT;
    p_ctx->i_cell_resolution_v = TTML_DEFAULT_CELL_RESOLUTION_V;
    p_ctx->i_cell_resolution_h = TTML_DEFAULT_CELL_RESOLUTION_H;
    /* and override them */
    const char *value = vlc_dictionary_value_for_key( &p_rootnode->attr_dict,
                                                      "tts:extent" );
    if( value != kVLCDictionaryNotFound )
    {
        ttml_read_coords( value, &p_ctx->root_extent_h,
                               &p_ctx->root_extent_v );
    }
    value = vlc_dictionary_value_for_key( &p_rootnode->attr_dict,
                                          "ttp:cellResolution" );
    if( value != kVLCDictionaryNotFound )
    {
        unsigned w, h;
        if( sscanf( value, "%u %u", &w, &h) == 2 && w && h )
        {
            p_ctx->i_cell_resolution_h = w;
            p_ctx->i_cell_resolution_v = h;
        }
    }
}