#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_face; int /*<<< orphan*/  i_index; int /*<<< orphan*/  psz_fontfile; } ;
typedef  TYPE_1__ vlc_font_t ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_default_style; } ;
typedef  TYPE_3__ filter_sys_t ;
typedef  int /*<<< orphan*/  FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  LoadFace (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

FT_Face GetFace( filter_t *p_filter, vlc_font_t *p_font )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if( p_font->p_face )
        return p_font->p_face;

    p_font->p_face = LoadFace( p_filter, p_font->psz_fontfile, p_font->i_index,
                               p_sys->p_default_style );

    return p_font->p_face;
}