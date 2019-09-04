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

/* Variables and functions */
 int /*<<< orphan*/  IDirectDraw7_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectDrawSurface7_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdd7 ; 
 int /*<<< orphan*/  pdds7 ; 

__attribute__((used)) static void release_directdraw(void)
{
    IDirectDrawSurface7_Release(pdds7);
    IDirectDraw7_Release(pdd7);
}