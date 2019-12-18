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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PHYSDEV ;

/* Variables and functions */
 int /*<<< orphan*/  GDI_ERROR ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  META_SETTEXTALIGN ; 
 scalar_t__ MFDRV_MetaParam2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT MFDRV_SetTextAlign( PHYSDEV dev, UINT align )
{
    return MFDRV_MetaParam2( dev, META_SETTEXTALIGN, HIWORD(align), LOWORD(align)) ? align : GDI_ERROR;
}