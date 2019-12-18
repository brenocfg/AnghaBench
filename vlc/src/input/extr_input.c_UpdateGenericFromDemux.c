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
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_4__ {TYPE_1__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p_demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_GET_SIGNAL ; 
 int /*<<< orphan*/  INPUT_UPDATE_META ; 
 int /*<<< orphan*/  InputUpdateMeta (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*,double*) ; 
 scalar_t__ demux_TestAndClearFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_SendEventSignal (int /*<<< orphan*/ *,double,double) ; 
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void UpdateGenericFromDemux( input_thread_t *p_input )
{
    demux_t *p_demux = input_priv(p_input)->master->p_demux;

    if( demux_TestAndClearFlags( p_demux, INPUT_UPDATE_META ) )
        InputUpdateMeta( p_input, p_demux );

    {
        double quality;
        double strength;

        if( !demux_Control( p_demux, DEMUX_GET_SIGNAL, &quality, &strength ) )
            input_SendEventSignal( p_input, quality, strength );
    }
}