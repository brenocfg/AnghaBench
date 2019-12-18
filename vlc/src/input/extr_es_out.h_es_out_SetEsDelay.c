#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  es_out_t ;
typedef  int /*<<< orphan*/  es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_SET_ES_DELAY ; 
 int /*<<< orphan*/  assert (int) ; 
 int es_out_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void es_out_SetEsDelay( es_out_t *p_out, es_out_id_t *es, vlc_tick_t i_delay )
{
    int i_ret = es_out_Control( p_out, ES_OUT_SET_ES_DELAY, es, i_delay );
    assert( !i_ret );
}