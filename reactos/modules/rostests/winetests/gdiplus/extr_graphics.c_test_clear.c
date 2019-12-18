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
typedef  int /*<<< orphan*/  GpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  GdipGraphicsClear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_clear(void)
{
    GpStatus status;

    status = GdipGraphicsClear(NULL, 0xdeadbeef);
    expect(InvalidParameter, status);
}