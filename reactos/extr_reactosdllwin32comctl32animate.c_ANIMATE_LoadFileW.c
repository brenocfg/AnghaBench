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
struct TYPE_3__ {int /*<<< orphan*/  hMMio; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MMIO_ALLOCBUF ; 
 int MMIO_DENYWRITE ; 
 int MMIO_READ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mmioOpenW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL ANIMATE_LoadFileW(ANIMATE_INFO *infoPtr, LPWSTR lpName)
{
    infoPtr->hMMio = mmioOpenW(lpName, 0, MMIO_ALLOCBUF | MMIO_READ | MMIO_DENYWRITE);

    if(!infoPtr->hMMio) return FALSE;
    return TRUE;
}