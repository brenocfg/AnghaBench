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
typedef  int /*<<< orphan*/  es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_GET_BUFFERING ; 
 int /*<<< orphan*/  assert (int) ; 
 int es_out_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline bool es_out_GetBuffering( es_out_t *p_out )
{
    bool b;
    int i_ret = es_out_Control( p_out, ES_OUT_GET_BUFFERING, &b );

    assert( !i_ret );
    return b;
}