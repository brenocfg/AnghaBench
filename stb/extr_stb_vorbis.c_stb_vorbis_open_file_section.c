#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  stb_vorbis_alloc ;
struct TYPE_9__ {unsigned int stream_len; int close_on_free; int error; scalar_t__ f_start; int /*<<< orphan*/ * f; } ;
typedef  TYPE_1__ stb_vorbis ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ start_decoder (TYPE_1__*) ; 
 TYPE_1__* vorbis_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  vorbis_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/  vorbis_init (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vorbis_pump_first_frame (TYPE_1__*) ; 

stb_vorbis * stb_vorbis_open_file_section(FILE *file, int close_on_free, int *error, const stb_vorbis_alloc *alloc, unsigned int length)
{
   stb_vorbis *f, p;
   vorbis_init(&p, alloc);
   p.f = file;
   p.f_start = (uint32) ftell(file);
   p.stream_len   = length;
   p.close_on_free = close_on_free;
   if (start_decoder(&p)) {
      f = vorbis_alloc(&p);
      if (f) {
         *f = p;
         vorbis_pump_first_frame(f);
         return f;
      }
   }
   if (error) *error = p.error;
   vorbis_deinit(&p);
   return NULL;
}