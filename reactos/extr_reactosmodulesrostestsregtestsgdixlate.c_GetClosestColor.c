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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ COLORREF ;

/* Variables and functions */
 scalar_t__ BMF_1BPP ; 
 int /*<<< orphan*/  iXlateFromRGB (scalar_t__,scalar_t__) ; 
 scalar_t__ iXlateToRGB (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
ULONG
GetClosestColor(ULONG iFormat, COLORREF crColor, COLORREF crBackColor)
{
    if (iFormat == BMF_1BPP)
        return crBackColor;
    return iXlateToRGB(iFormat, iXlateFromRGB(iFormat, crColor));
}