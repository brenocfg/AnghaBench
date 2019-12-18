#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i_id; } ;
typedef  TYPE_1__ commandparams_t ;
typedef  int /*<<< orphan*/  buffer_t ;

/* Variables and functions */
 int BufferPrintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int unparse_GenImage( const commandparams_t *p_results,
                             buffer_t *p_output )
{
    int ret = BufferPrintf( p_output, " %d", p_results->i_id );
    if( ret != VLC_SUCCESS )
        return ret;

    return VLC_SUCCESS;
}