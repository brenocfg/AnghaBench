#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_10__ {int current_loc_valid; unsigned int current_loc; int blocksize_1; int blocksize_0; scalar_t__ previous_length; } ;
typedef  TYPE_1__ stb_vorbis ;

/* Variables and functions */
 scalar_t__ IS_PUSH_MODE (TYPE_1__*) ; 
 int /*<<< orphan*/  VORBIS_invalid_api_mixing ; 
 int /*<<< orphan*/  VORBIS_seek_failed ; 
 int /*<<< orphan*/  assert (int) ; 
 int error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_start_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  peek_decode_initial (TYPE_1__*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  seek_to_sample_coarse (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  vorbis_pump_first_frame (TYPE_1__*) ; 

int stb_vorbis_seek_frame(stb_vorbis *f, unsigned int sample_number)
{
   uint32 max_frame_samples;

   if (IS_PUSH_MODE(f)) return error(f, VORBIS_invalid_api_mixing);

   // fast page-level search
   if (!seek_to_sample_coarse(f, sample_number))
      return 0;

   assert(f->current_loc_valid);
   assert(f->current_loc <= sample_number);

   // linear search for the relevant packet
   max_frame_samples = (f->blocksize_1*3 - f->blocksize_0) >> 2;
   while (f->current_loc < sample_number) {
      int left_start, left_end, right_start, right_end, mode, frame_samples;
      if (!peek_decode_initial(f, &left_start, &left_end, &right_start, &right_end, &mode))
         return error(f, VORBIS_seek_failed);
      // calculate the number of samples returned by the next frame
      frame_samples = right_start - left_start;
      if (f->current_loc + frame_samples > sample_number) {
         return 1; // the next frame will contain the sample
      } else if (f->current_loc + frame_samples + max_frame_samples > sample_number) {
         // there's a chance the frame after this could contain the sample
         vorbis_pump_first_frame(f);
      } else {
         // this frame is too early to be relevant
         f->current_loc += frame_samples;
         f->previous_length = 0;
         maybe_start_packet(f);
         flush_packet(f);
      }
   }
   // the next frame will start with the sample
   assert(f->current_loc == sample_number);
   return 1;
}