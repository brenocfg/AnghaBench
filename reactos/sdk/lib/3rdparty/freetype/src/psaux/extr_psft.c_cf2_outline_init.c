#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cubeTo; int /*<<< orphan*/  lineTo; int /*<<< orphan*/  moveTo; int /*<<< orphan*/ * error; int /*<<< orphan*/  memory; } ;
struct TYPE_6__ {TYPE_1__ root; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_2__* CF2_Outline ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ZERO (TYPE_2__*) ; 
 int /*<<< orphan*/  cf2_builder_cubeTo ; 
 int /*<<< orphan*/  cf2_builder_lineTo ; 
 int /*<<< orphan*/  cf2_builder_moveTo ; 

__attribute__((used)) static void
  cf2_outline_init( CF2_Outline  outline,
                    FT_Memory    memory,
                    FT_Error*    error )
  {
    FT_ZERO( outline );

    outline->root.memory = memory;
    outline->root.error  = error;

    outline->root.moveTo = cf2_builder_moveTo;
    outline->root.lineTo = cf2_builder_lineTo;
    outline->root.cubeTo = cf2_builder_cubeTo;
  }