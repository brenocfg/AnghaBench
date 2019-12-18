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
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_5__ {int i_version; int i_width; int i_height; int b_windowed; } ;
struct TYPE_7__ {TYPE_1__ display; } ;
typedef  TYPE_3__ decoder_sys_t ;

/* Variables and functions */

__attribute__((used)) static void default_dds_init( decoder_t * p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    /* see notes on DDS at the top of the file */

    /* configure for SD res in case DDS is not present */
    p_sys->display.i_version = 0xff; /* an invalid version so it's always different */
    p_sys->display.i_width = 720;
    p_sys->display.i_height = 576;
    p_sys->display.b_windowed = false;
}