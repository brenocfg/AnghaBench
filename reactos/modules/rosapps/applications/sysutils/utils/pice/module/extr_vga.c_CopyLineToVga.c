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
typedef  size_t USHORT ;
typedef  int /*<<< orphan*/ * PUSHORT ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 size_t GLOBAL_SCREEN_WIDTH ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PICE_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pScreenBufferVga ; 

void CopyLineToVga(USHORT dest,USHORT src)
{
    PUSHORT p = (PUSHORT)pScreenBufferVga;

    ENTER_FUNC();

	PICE_memcpy(&p[dest*GLOBAL_SCREEN_WIDTH],&p[src*GLOBAL_SCREEN_WIDTH],GLOBAL_SCREEN_WIDTH*sizeof(USHORT));

    LEAVE_FUNC();
}