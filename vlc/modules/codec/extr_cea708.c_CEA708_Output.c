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
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_dec; int /*<<< orphan*/  i_clock; } ;
typedef  TYPE_1__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CEA708_BuildSubtitle (TYPE_1__*) ; 
 int /*<<< orphan*/  Debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decoder_QueueSub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CEA708_Output( cea708_t *p_cea708 )
{
    Debug(printf("@%ld ms\n", MS_FROM_VLC_TICK(p_cea708->i_clock)));
    subpicture_t *p_spu = CEA708_BuildSubtitle( p_cea708 );
    if( p_spu )
        decoder_QueueSub( p_cea708->p_dec, p_spu );
}