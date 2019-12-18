#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_11__ {int /*<<< orphan*/  pf_render_ordered; int /*<<< orphan*/  settings; } ;
struct TYPE_13__ {TYPE_2__ context; TYPE_1__* chroma; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_14__ {char* psz_mode; int /*<<< orphan*/  pf_render_ordered; int /*<<< orphan*/  settings; int /*<<< orphan*/  b_high_bit_depth; int /*<<< orphan*/  can_pack; } ;
struct TYPE_10__ {int pixel_size; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_7__*) ; 
 TYPE_7__* filter_mode ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void SetFilterMethod( filter_t *p_filter, const char *mode, bool pack )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if ( mode == NULL || !strcmp( mode, "auto" ) )
        mode = "x";

    for ( size_t i = 0; i < ARRAY_SIZE(filter_mode); i++ )
    {
        if( !strcmp( mode, filter_mode[i].psz_mode ) )
        {
            if ( pack && !filter_mode[i].can_pack )
            {
                msg_Err( p_filter, "unknown or incompatible deinterlace mode \"%s\""
                        " for packed format", mode );
                SetFilterMethod( p_filter, "blend", pack );
                return;
            }
            if( p_sys->chroma->pixel_size > 1 && !filter_mode[i].b_high_bit_depth )
            {
                msg_Err( p_filter, "unknown or incompatible deinterlace mode \"%s\""
                        " for high depth format", mode );
                SetFilterMethod( p_filter, "blend", pack );
                return;
            }

            msg_Dbg( p_filter, "using %s deinterlace method", mode );
            p_sys->context.settings = filter_mode[i].settings;
            p_sys->context.pf_render_ordered = filter_mode[i].pf_render_ordered;
            return;
        }
    }

    msg_Err( p_filter, "unknown deinterlace mode \"%s\"", mode );
}