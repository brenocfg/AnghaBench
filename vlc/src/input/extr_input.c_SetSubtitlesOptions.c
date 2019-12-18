#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {TYPE_1__* master; } ;
struct TYPE_3__ {float f_fps; } ;

/* Variables and functions */
 int /*<<< orphan*/  RequestSubRate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_InheritFloat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetFloat (int /*<<< orphan*/ *,char*,float const) ; 

__attribute__((used)) static void SetSubtitlesOptions( input_thread_t *p_input )
{
    /* Get fps and set it if not already set */
    const float f_fps = input_priv(p_input)->master->f_fps;
    if( f_fps > 1.f )
    {
        var_SetFloat( p_input, "sub-original-fps", f_fps );
        RequestSubRate( p_input, var_InheritFloat( p_input, "sub-fps" ) );
    }
}