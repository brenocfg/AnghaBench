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
typedef  size_t UINT ;
typedef  size_t DWORD ;
typedef  scalar_t__ DPID ;

/* Variables and functions */
 scalar_t__ DPID_SYSMSG ; 

__attribute__((used)) static char dpid2char(DPID* dpid, DWORD dpidSize, DPID idPlayer)
{
    UINT i;
    if ( idPlayer == DPID_SYSMSG )
        return 'S';
    for (i=0; i<dpidSize; i++)
    {
        if ( idPlayer == dpid[i] )
            return (char)(i+48);
    }
    return '?';
}