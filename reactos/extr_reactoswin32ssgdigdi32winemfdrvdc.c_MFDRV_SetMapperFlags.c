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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GDI_ERROR ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  META_SETMAPPERFLAGS ; 
 scalar_t__ MFDRV_MetaParam2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DWORD MFDRV_SetMapperFlags( PHYSDEV dev, DWORD flags )
{
    return MFDRV_MetaParam2( dev, META_SETMAPPERFLAGS, HIWORD(flags), LOWORD(flags) ) ? flags : GDI_ERROR;
}