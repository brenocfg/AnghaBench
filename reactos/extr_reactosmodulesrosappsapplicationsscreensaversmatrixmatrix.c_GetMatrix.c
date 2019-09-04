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
typedef  int /*<<< orphan*/  MATRIX ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_USERDATA ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MATRIX *GetMatrix(HWND hwnd)
{
	return (MATRIX *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
}