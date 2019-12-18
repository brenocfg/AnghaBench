#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int /*<<< orphan*/ * colmap; scalar_t__ compatible_arch; } ;
struct TYPE_5__ {TYPE_1__ xwin; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  BOUT24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOUT24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
translate8to24(RDPCLIENT * This, const uint8 * data, uint8 * out, uint8 * end)
{
	uint32 value;

	if (This->xwin.compatible_arch)
	{
		while (out < end)
		{
			value = This->xwin.colmap[*(data++)];
			BOUT24(out, value);
		}
	}
	else
	{
		while (out < end)
		{
			value = This->xwin.colmap[*(data++)];
			LOUT24(out, value);
		}
	}
}