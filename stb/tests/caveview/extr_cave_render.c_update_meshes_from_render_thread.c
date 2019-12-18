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
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  rm; } ;
typedef  TYPE_1__ mesh_worker ;

/* Variables and functions */
 scalar_t__ WSTATE_idle ; 
 scalar_t__ WSTATE_mesh_ready ; 
 TYPE_1__* mesh_data ; 
 int num_mesh_workers ; 
 int /*<<< orphan*/  num_meshes_uploaded ; 
 int /*<<< orphan*/  upload_mesh_data (int /*<<< orphan*/ *) ; 

void update_meshes_from_render_thread(void)
{
   int i;
   for (i=0; i < num_mesh_workers; ++i) {
      mesh_worker *mw = &mesh_data[i];
      if (mw->state == WSTATE_mesh_ready) {
         upload_mesh_data(&mw->rm);
         ++num_meshes_uploaded;
         mw->state = WSTATE_idle;
      }
   }
}