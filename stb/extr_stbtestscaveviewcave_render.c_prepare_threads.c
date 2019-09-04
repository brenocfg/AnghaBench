#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* chunk_server_done_processing; void* request_received; } ;
typedef  TYPE_1__ mesh_worker ;

/* Variables and functions */
 int MAX_MESH_WORKERS ; 
 void* SDL_CreateSemaphore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CreateThread (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int SDL_GetCPUCount () ; 
 TYPE_1__* mesh_data ; 
 int /*<<< orphan*/  mesh_worker_handler ; 
 int num_mesh_workers ; 

void prepare_threads(void)
{
   int i;
   int num_proc = SDL_GetCPUCount();

   if (num_proc > 6)
      num_mesh_workers = num_proc/2;
   else if (num_proc > 4)
      num_mesh_workers = 4;
   else 
      num_mesh_workers = num_proc-1;

// @TODO
//   Thread usage is probably pretty terrible; need to make a
//   separate queue of needed chunks, instead of just generating
//   one request per thread per frame, and a separate queue of
//   results. (E.g. If it takes 1.5 frames to build mesh, thread
//   is idle for 0.5 frames.) To fake this for now, I've just
//   doubled the number of threads to let those serve as a 'queue',
//   but that's dumb.

   num_mesh_workers *= 2; // try to get better thread usage

   if (num_mesh_workers > MAX_MESH_WORKERS)
      num_mesh_workers = MAX_MESH_WORKERS;

   for (i=0; i < num_mesh_workers; ++i) {
      mesh_worker *data = &mesh_data[i];
      data->request_received = SDL_CreateSemaphore(0);
      data->chunk_server_done_processing = SDL_CreateSemaphore(0);
      SDL_CreateThread(mesh_worker_handler, "mesh worker", data);
   }
}