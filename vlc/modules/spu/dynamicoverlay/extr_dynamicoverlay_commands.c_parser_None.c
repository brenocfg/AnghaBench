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
typedef  char commandparams_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char*) ; 

__attribute__((used)) static int parser_None( char *psz_command, char *psz_end,
                        commandparams_t *p_params )
{
    VLC_UNUSED(psz_command);
    VLC_UNUSED(psz_end);
    VLC_UNUSED(p_params);
    return VLC_SUCCESS;
}