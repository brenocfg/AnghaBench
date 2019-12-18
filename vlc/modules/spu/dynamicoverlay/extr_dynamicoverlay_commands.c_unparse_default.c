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
typedef  int /*<<< orphan*/  commandparams_t ;
typedef  int /*<<< orphan*/  const buffer_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int unparse_default( const commandparams_t *p_results,
                            buffer_t *p_output )
{
    VLC_UNUSED(p_results);
    VLC_UNUSED(p_output);
    return VLC_SUCCESS;
}