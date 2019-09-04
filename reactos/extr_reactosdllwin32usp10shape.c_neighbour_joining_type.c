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
struct TYPE_3__ {scalar_t__ fLinkAfter; scalar_t__ fLinkBefore; } ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int INT ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 scalar_t__ jtL ; 
 scalar_t__ jtR ; 
 scalar_t__ const jtT ; 
 scalar_t__ jtU ; 

__attribute__((used)) static CHAR neighbour_joining_type(int i, int delta, const CHAR* context_type, INT cchLen, SCRIPT_ANALYSIS *psa)
{
    if (i + delta < 0)
    {
        if (psa->fLinkBefore)
            return jtR;
        else
            return jtU;
    }
    if ( i+ delta >= cchLen)
    {
        if (psa->fLinkAfter)
            return jtL;
        else
            return jtU;
    }

    i += delta;

    if (context_type[i] == jtT)
        return neighbour_joining_type(i,delta,context_type,cchLen,psa);
    else
        return context_type[i];
}