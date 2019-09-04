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
typedef  int GpLineJoin ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
#define  LineJoinBevel 131 
#define  LineJoinMiter 130 
#define  LineJoinMiterClipped 129 
#define  LineJoinRound 128 
 int /*<<< orphan*/  PS_JOIN_BEVEL ; 
 int /*<<< orphan*/  PS_JOIN_MITER ; 
 int /*<<< orphan*/  PS_JOIN_ROUND ; 

__attribute__((used)) static DWORD gdip_to_gdi_join(GpLineJoin join)
{
    switch(join){
        case LineJoinRound:
            return PS_JOIN_ROUND;
        case LineJoinBevel:
            return PS_JOIN_BEVEL;
        case LineJoinMiter:
        case LineJoinMiterClipped:
            return PS_JOIN_MITER;
        default:
            ERR("Not a member of GpLineJoin enumeration\n");
            return 0;
    }
}