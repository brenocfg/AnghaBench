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
struct TYPE_5__ {int /*<<< orphan*/  memory; } ;
struct TYPE_6__ {TYPE_1__ root; int /*<<< orphan*/  faces_list; } ;
typedef  int /*<<< orphan*/  FT_List_Destructor ;
typedef  TYPE_2__* FT_Driver ;

/* Variables and functions */
 int /*<<< orphan*/  FT_List_Finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ destroy_face ; 

__attribute__((used)) static void
  Destroy_Driver( FT_Driver  driver )
  {
    FT_List_Finalize( &driver->faces_list,
                      (FT_List_Destructor)destroy_face,
                      driver->root.memory,
                      driver );
  }