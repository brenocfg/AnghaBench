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
typedef  int uint32 ;
struct TYPE_4__ {scalar_t__ xserver_be; } ;
struct TYPE_5__ {TYPE_1__ xwin; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  PixelColour ;

/* Variables and functions */
 int /*<<< orphan*/  BOUT24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LOUT24 (int /*<<< orphan*/ *,int) ; 
 int MAKECOLOUR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLITCOLOUR24 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
translate24to24(RDPCLIENT * This, const uint8 * data, uint8 * out, uint8 * end)
{
	uint32 pixel;
	uint32 value;
	PixelColour pc;

	if (This->xwin.xserver_be)
	{
		while (out < end)
		{
			pixel = *(data++) << 16;
			pixel |= *(data++) << 8;
			pixel |= *(data++);
			SPLITCOLOUR24(pixel, pc);
			value = MAKECOLOUR(pc);
			BOUT24(out, value);
		}
	}
	else
	{
		while (out < end)
		{
			pixel = *(data++) << 16;
			pixel |= *(data++) << 8;
			pixel |= *(data++);
			SPLITCOLOUR24(pixel, pc);
			value = MAKECOLOUR(pc);
			LOUT24(out, value);
		}
	}
}