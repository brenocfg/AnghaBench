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
typedef  int GpDashStyle ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
#define  DashStyleCustom 133 
#define  DashStyleDash 132 
#define  DashStyleDashDot 131 
#define  DashStyleDashDotDot 130 
#define  DashStyleDot 129 
#define  DashStyleSolid 128 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  PS_DASH ; 
 int /*<<< orphan*/  PS_DASHDOT ; 
 int /*<<< orphan*/  PS_DASHDOTDOT ; 
 int /*<<< orphan*/  PS_DOT ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  PS_USERSTYLE ; 

__attribute__((used)) static DWORD gdip_to_gdi_dash(GpDashStyle dash)
{
    switch(dash){
        case DashStyleSolid:
            return PS_SOLID;
        case DashStyleDash:
            return PS_DASH;
        case DashStyleDot:
            return PS_DOT;
        case DashStyleDashDot:
            return PS_DASHDOT;
        case DashStyleDashDotDot:
            return PS_DASHDOTDOT;
        case DashStyleCustom:
            return PS_USERSTYLE;
        default:
            ERR("Not a member of GpDashStyle enumeration\n");
            return 0;
    }
}