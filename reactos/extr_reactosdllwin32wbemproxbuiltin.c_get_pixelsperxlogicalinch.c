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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT32 get_pixelsperxlogicalinch(void)
{
    HDC hdc = GetDC( NULL );
    UINT32 ret;

    if (!hdc) return 96;
    ret = GetDeviceCaps( hdc, LOGPIXELSX );
    ReleaseDC( NULL, hdc );
    return ret;
}