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
typedef  int /*<<< orphan*/  subpicture_updater_t ;
struct TYPE_4__ {int b_subtitle; } ;
typedef  TYPE_1__ subpicture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 TYPE_1__* subpicture_New (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static subpicture_t *spu_new_buffer( decoder_t *p_dec,
                                     const subpicture_updater_t *p_upd )
{
    VLC_UNUSED( p_dec );
    subpicture_t *p_subpicture = subpicture_New( p_upd );
    if( likely(p_subpicture != NULL) )
        p_subpicture->b_subtitle = true;
    return p_subpicture;
}