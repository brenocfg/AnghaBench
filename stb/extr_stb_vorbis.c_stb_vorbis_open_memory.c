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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  stb_vorbis_alloc ;
struct TYPE_9__ {int stream_len; int error; int /*<<< orphan*/  push_mode; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * stream_start; int /*<<< orphan*/ * stream_end; } ;
typedef  TYPE_1__ stb_vorbis ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int VORBIS__no_error ; 
 scalar_t__ start_decoder (TYPE_1__*) ; 
 TYPE_1__* vorbis_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  vorbis_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/  vorbis_init (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vorbis_pump_first_frame (TYPE_1__*) ; 

stb_vorbis * stb_vorbis_open_memory(const unsigned char *data, int len, int *error, const stb_vorbis_alloc *alloc)
{
   stb_vorbis *f, p;
   if (data == NULL) return NULL;
   vorbis_init(&p, alloc);
   p.stream = (uint8 *) data;
   p.stream_end = (uint8 *) data + len;
   p.stream_start = (uint8 *) p.stream;
   p.stream_len = len;
   p.push_mode = FALSE;
   if (start_decoder(&p)) {
      f = vorbis_alloc(&p);
      if (f) {
         *f = p;
         vorbis_pump_first_frame(f);
         if (error) *error = VORBIS__no_error;
         return f;
      }
   }
   if (error) *error = p.error;
   vorbis_deinit(&p);
   return NULL;
}