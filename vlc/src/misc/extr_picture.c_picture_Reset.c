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
struct TYPE_4__ {int b_force; int b_still; int b_progressive; int i_nb_fields; int b_top_field_first; int /*<<< orphan*/  date; } ;
typedef  TYPE_1__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  PictureDestroyContext (TYPE_1__*) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 

void picture_Reset( picture_t *p_picture )
{
    /* */
    p_picture->date = VLC_TICK_INVALID;
    p_picture->b_force = false;
    p_picture->b_still = false;
    p_picture->b_progressive = false;
    p_picture->i_nb_fields = 2;
    p_picture->b_top_field_first = false;
    PictureDestroyContext( p_picture );
}