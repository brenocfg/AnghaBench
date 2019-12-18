#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_text; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_fontstyle; TYPE_1__ data; } ;
typedef  TYPE_2__ overlay_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 

int OverlayDestroy( overlay_t *p_ovl )
{
    free( p_ovl->data.p_text );
    text_style_Delete( p_ovl->p_fontstyle );

    return VLC_SUCCESS;
}