#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_9__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_8__ {int server_depth; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  TYPE_2__ PixelColour ;

/* Variables and functions */
 int /*<<< orphan*/  MAKECOLOUR (TYPE_2__) ; 
 int /*<<< orphan*/  SPLITCOLOUR15 (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  SPLITCOLOUR16 (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  SPLITCOLOUR24 (int /*<<< orphan*/ ,TYPE_2__) ; 

__attribute__((used)) static uint32
translate_colour(RDPCLIENT * This, uint32 colour)
{
	PixelColour pc;
	switch (This->server_depth)
	{
		case 15:
			SPLITCOLOUR15(colour, pc);
			break;
		case 16:
			SPLITCOLOUR16(colour, pc);
			break;
		case 24:
			SPLITCOLOUR24(colour, pc);
			break;
		default:
			/* Avoid warning */
			pc.red = 0;
			pc.green = 0;
			pc.blue = 0;
			break;
	}
	return MAKECOLOUR(pc);
}