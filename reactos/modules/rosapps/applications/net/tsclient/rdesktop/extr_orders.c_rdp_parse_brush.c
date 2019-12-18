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
struct TYPE_3__ {int /*<<< orphan*/ * pattern; int /*<<< orphan*/  style; int /*<<< orphan*/  yorigin; int /*<<< orphan*/  xorigin; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ BRUSH ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
rdp_parse_brush(STREAM s, BRUSH * brush, uint32 present)
{
	if (present & 1)
		in_uint8(s, brush->xorigin);

	if (present & 2)
		in_uint8(s, brush->yorigin);

	if (present & 4)
		in_uint8(s, brush->style);

	if (present & 8)
		in_uint8(s, brush->pattern[0]);

	if (present & 16)
		in_uint8a(s, &brush->pattern[1], 7);

	return s_check(s);
}