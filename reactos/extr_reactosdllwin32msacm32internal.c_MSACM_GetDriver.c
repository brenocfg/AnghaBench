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
typedef  int /*<<< orphan*/  PWINE_ACMDRIVER ;
typedef  int /*<<< orphan*/  HACMOBJ ;
typedef  scalar_t__ HACMDRIVER ;

/* Variables and functions */
 int /*<<< orphan*/  MSACM_GetObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_ACMOBJ_DRIVER ; 

PWINE_ACMDRIVER MSACM_GetDriver(HACMDRIVER hDriver)
{
    return (PWINE_ACMDRIVER)MSACM_GetObj((HACMOBJ)hDriver, WINE_ACMOBJ_DRIVER);
}