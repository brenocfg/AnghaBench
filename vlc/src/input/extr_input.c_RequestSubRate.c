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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_5__ {float slave_subs_rate; TYPE_1__* master; } ;
typedef  TYPE_2__ input_thread_private_t ;
struct TYPE_4__ {float f_fps; } ;

/* Variables and functions */
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RequestSubRate( input_thread_t *p_input, float f_slave_fps )
{
    input_thread_private_t *priv = input_priv(p_input);
    const float f_fps = input_priv(p_input)->master->f_fps;
    if( f_fps > 1.f && f_slave_fps > 1.f )
        priv->slave_subs_rate = f_fps / f_slave_fps;
    else if ( priv->slave_subs_rate != 0 )
        priv->slave_subs_rate = 1.f;
}