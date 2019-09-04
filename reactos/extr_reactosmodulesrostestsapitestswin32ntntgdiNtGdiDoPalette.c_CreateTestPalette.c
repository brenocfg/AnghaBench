#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_15__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_14__ {int member_0; int member_1; int member_2; int /*<<< orphan*/  member_3; } ;
struct TYPE_13__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_12__ {TYPE_8__ member_3; TYPE_7__ member_2; TYPE_6__ member_1; TYPE_5__ member_0; } ;
struct TYPE_11__ {int member_0; int member_1; int member_2; int /*<<< orphan*/  member_3; } ;
struct TYPE_10__ {TYPE_3__ member_0; } ;
struct TYPE_9__ {int member_0; int member_1; TYPE_2__ member_2; } ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  int /*<<< orphan*/  LOGPALETTE ;
typedef  int /*<<< orphan*/  HPALETTE ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePalette (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PC_EXPLICIT ; 
 int PC_NOCOLLAPSE ; 
 int PC_RESERVED ; 

HPALETTE
CreateTestPalette()
{
    struct
    {
        LOGPALETTE logpal;
        PALETTEENTRY entry[5];
    } palstruct =
    { {0x300,5,
      { {1,2,3,0} }},
      { {22,33,44,PC_RESERVED},
        {11,55,77,PC_EXPLICIT},
        {00,77,66,PC_RESERVED | PC_NOCOLLAPSE},
        {12,34,56,78}} };

    return CreatePalette((LOGPALETTE*)&palstruct);
}