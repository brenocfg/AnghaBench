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
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OLEFontImpl_csHFONTLIST ; 
 scalar_t__ olefont_hdc ; 

__attribute__((used)) static HDC get_dc(void)
{
    HDC hdc;
    EnterCriticalSection(&OLEFontImpl_csHFONTLIST);
    if(!olefont_hdc)
        olefont_hdc = CreateCompatibleDC(NULL);
    hdc = olefont_hdc;
    LeaveCriticalSection(&OLEFontImpl_csHFONTLIST);
    return hdc;
}