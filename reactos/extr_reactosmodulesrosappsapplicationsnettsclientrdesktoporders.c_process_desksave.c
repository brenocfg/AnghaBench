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
typedef  int uint32 ;
struct TYPE_3__ {int left; int top; int right; int bottom; scalar_t__ action; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  TYPE_1__ DESKSAVE_ORDER ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rdp_in_coord (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_desktop_restore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ui_desktop_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void
process_desksave(RDPCLIENT * This, STREAM s, DESKSAVE_ORDER * os, uint32 present, BOOL delta)
{
	int width, height;

	if (present & 0x01)
		in_uint32_le(s, os->offset);

	if (present & 0x02)
		rdp_in_coord(s, &os->left, delta);

	if (present & 0x04)
		rdp_in_coord(s, &os->top, delta);

	if (present & 0x08)
		rdp_in_coord(s, &os->right, delta);

	if (present & 0x10)
		rdp_in_coord(s, &os->bottom, delta);

	if (present & 0x20)
		in_uint8(s, os->action);

	DEBUG(("DESKSAVE(l=%d,t=%d,r=%d,b=%d,off=%d,op=%d)\n",
	       os->left, os->top, os->right, os->bottom, os->offset, os->action));

	width = os->right - os->left + 1;
	height = os->bottom - os->top + 1;

	if (os->action == 0)
		ui_desktop_save(This, os->offset, os->left, os->top, width, height);
	else
		ui_desktop_restore(This, os->offset, os->left, os->top, width, height);
}