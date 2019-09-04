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
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_INVALID ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  META_SETBKCOLOR ; 
 scalar_t__ MFDRV_MetaParam2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

COLORREF MFDRV_SetBkColor( PHYSDEV dev, COLORREF color )
{
    return MFDRV_MetaParam2(dev, META_SETBKCOLOR, HIWORD(color), LOWORD(color)) ? color : CLR_INVALID;
}