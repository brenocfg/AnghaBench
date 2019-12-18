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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 scalar_t__ TimeGet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int OutputTimeGet( audio_output_t *aout, vlc_tick_t *delay )
{
    aout_sys_t *sys = aout->sys;
    return (TimeGet( &sys->s, delay ) == DS_OK) ? 0 : -1;
}