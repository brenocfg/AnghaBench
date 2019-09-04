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
struct TYPE_3__ {scalar_t__ state; int request_cx; int request_cy; int /*<<< orphan*/  request_received; } ;
typedef  TYPE_1__ mesh_worker ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_SemPost (int /*<<< orphan*/ ) ; 
 scalar_t__ WSTATE_idle ; 
 scalar_t__ WSTATE_requested ; 
 TYPE_1__* mesh_data ; 
 int num_mesh_workers ; 
 int /*<<< orphan*/  num_meshes_started ; 

int request_chunk(int chunk_x, int chunk_y)
{
   int i;
   for (i=0; i < num_mesh_workers; ++i) {
      mesh_worker *mw = &mesh_data[i];
      if (mw->state == WSTATE_idle) {
         mw->request_cx = chunk_x;
         mw->request_cy = chunk_y;
         mw->state = WSTATE_requested;
         SDL_SemPost(mw->request_received);
         ++num_meshes_started;
         return 1;
      }
   }
   return 0;
}