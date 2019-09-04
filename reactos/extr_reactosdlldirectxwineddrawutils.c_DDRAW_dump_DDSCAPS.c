#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dwCaps; } ;
struct TYPE_6__ {scalar_t__ dwCaps4; } ;
struct TYPE_7__ {TYPE_1__ u1; scalar_t__ dwCaps3; scalar_t__ dwCaps2; int /*<<< orphan*/  dwCaps; } ;
typedef  TYPE_2__ DDSCAPS2 ;
typedef  TYPE_3__ DDSCAPS ;

/* Variables and functions */
 int /*<<< orphan*/  DDRAW_dump_DDSCAPS2 (TYPE_2__*) ; 

__attribute__((used)) static void
DDRAW_dump_DDSCAPS(const DDSCAPS *in)
{
    DDSCAPS2 in_bis;

    in_bis.dwCaps = in->dwCaps;
    in_bis.dwCaps2 = 0;
    in_bis.dwCaps3 = 0;
    in_bis.u1.dwCaps4 = 0;

    DDRAW_dump_DDSCAPS2(&in_bis);
}