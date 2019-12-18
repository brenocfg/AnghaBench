#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  float Uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RENDERER ; 
 float SDL_GetPerformanceCounter () ; 
 scalar_t__ SDL_GetPerformanceFrequency () ; 
 int /*<<< orphan*/  chunk_locations ; 
 float chunk_server_activity ; 
 size_t chunk_server_pos ; 
 float* chunk_server_status ; 
 int chunk_storage_considered ; 
 int chunk_storage_rendered ; 
 int chunk_storage_total ; 
 int /*<<< orphan*/  chunks_considered ; 
 int /*<<< orphan*/  chunks_in_frustum ; 
 int /*<<< orphan*/  glGetString (int /*<<< orphan*/ ) ; 
 scalar_t__ is_synchronous_debug ; 
 int /*<<< orphan*/  num_meshes_started ; 
 int /*<<< orphan*/  num_meshes_uploaded ; 
 int /*<<< orphan*/  num_threads_active ; 
 int pos_y ; 
 int /*<<< orphan*/  print (char*,...) ; 
 int quads_considered ; 
 int quads_rendered ; 
 int render_time ; 
 int /*<<< orphan*/  stb_easy_font_spacing (double) ; 
 double* text_color ; 
 int view_dist_in_chunks ; 

void draw_stats(void)
{
   int i;

   static Uint64 last_frame_time;
   Uint64 cur_time = SDL_GetPerformanceCounter();
   float chunk_server=0;
   float frame_time = (cur_time - last_frame_time) / (float) SDL_GetPerformanceFrequency();
   last_frame_time = cur_time;

   chunk_server_status[chunk_server_pos] = chunk_server_activity;
   chunk_server_pos = (chunk_server_pos+1) %32;

   for (i=0; i < 32; ++i)
      chunk_server += chunk_server_status[i] / 32.0f;

   stb_easy_font_spacing(-0.75);
   pos_y = 10;
   text_color[0] = text_color[1] = text_color[2] = 1.0f;
   print("Frame time: %6.2fms, CPU frame render time: %5.2fms", frame_time*1000, render_time*1000);
   print("Tris: %4.1fM drawn of %4.1fM in range", 2*quads_rendered/1000000.0f, 2*quads_considered/1000000.0f);
   print("Vbuf storage: %dMB in frustum of %dMB in range of %dMB in cache", chunk_storage_rendered>>20, chunk_storage_considered>>20, chunk_storage_total>>20);
   print("Num mesh builds started this frame: %d; num uploaded this frame: %d\n", num_meshes_started, num_meshes_uploaded);
   print("QChunks: %3d in frustum of %3d valid of %3d in range", chunks_in_frustum, chunks_considered, chunk_locations);
   print("Mesh worker threads active: %d", num_threads_active);
   print("View distance: %d blocks", view_dist_in_chunks*16);
   print("%s", glGetString(GL_RENDERER));

   if (is_synchronous_debug) {
      text_color[0] = 1.0;
      text_color[1] = 0.5;
      text_color[2] = 0.5;
      print("SLOWNESS: Synchronous debug output is enabled!");
   }
}