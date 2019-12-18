#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_11__ {unsigned int page_start; unsigned int page_end; int last_decoded_sample; } ;
struct TYPE_12__ {int total_samples; int stream_len; int first_audio_page_offset; TYPE_1__ p_last; void* error; } ;
typedef  TYPE_2__ stb_vorbis ;

/* Variables and functions */
 scalar_t__ IS_PUSH_MODE (TYPE_2__*) ; 
 int SAMPLE_unknown ; 
 void* VORBIS_cant_find_last_page ; 
 int /*<<< orphan*/  VORBIS_invalid_api_mixing ; 
 unsigned int error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int get32 (TYPE_2__*) ; 
 int /*<<< orphan*/  getn (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  set_file_offset (TYPE_2__*,unsigned int) ; 
 unsigned int stb_vorbis_get_file_offset (TYPE_2__*) ; 
 int /*<<< orphan*/  vorbis_find_page (TYPE_2__*,unsigned int*,unsigned int*) ; 

unsigned int stb_vorbis_stream_length_in_samples(stb_vorbis *f)
{
   unsigned int restore_offset, previous_safe;
   unsigned int end, last_page_loc;

   if (IS_PUSH_MODE(f)) return error(f, VORBIS_invalid_api_mixing);
   if (!f->total_samples) {
      unsigned int last;
      uint32 lo,hi;
      char header[6];

      // first, store the current decode position so we can restore it
      restore_offset = stb_vorbis_get_file_offset(f);

      // now we want to seek back 64K from the end (the last page must
      // be at most a little less than 64K, but let's allow a little slop)
      if (f->stream_len >= 65536 && f->stream_len-65536 >= f->first_audio_page_offset)
         previous_safe = f->stream_len - 65536;
      else
         previous_safe = f->first_audio_page_offset;

      set_file_offset(f, previous_safe);
      // previous_safe is now our candidate 'earliest known place that seeking
      // to will lead to the final page'

      if (!vorbis_find_page(f, &end, &last)) {
         // if we can't find a page, we're hosed!
         f->error = VORBIS_cant_find_last_page;
         f->total_samples = 0xffffffff;
         goto done;
      }

      // check if there are more pages
      last_page_loc = stb_vorbis_get_file_offset(f);

      // stop when the last_page flag is set, not when we reach eof;
      // this allows us to stop short of a 'file_section' end without
      // explicitly checking the length of the section
      while (!last) {
         set_file_offset(f, end);
         if (!vorbis_find_page(f, &end, &last)) {
            // the last page we found didn't have the 'last page' flag
            // set. whoops!
            break;
         }
         previous_safe = last_page_loc+1;
         last_page_loc = stb_vorbis_get_file_offset(f);
      }

      set_file_offset(f, last_page_loc);

      // parse the header
      getn(f, (unsigned char *)header, 6);
      // extract the absolute granule position
      lo = get32(f);
      hi = get32(f);
      if (lo == 0xffffffff && hi == 0xffffffff) {
         f->error = VORBIS_cant_find_last_page;
         f->total_samples = SAMPLE_unknown;
         goto done;
      }
      if (hi)
         lo = 0xfffffffe; // saturate
      f->total_samples = lo;

      f->p_last.page_start = last_page_loc;
      f->p_last.page_end   = end;
      f->p_last.last_decoded_sample = lo;

     done:
      set_file_offset(f, restore_offset);
   }
   return f->total_samples == SAMPLE_unknown ? 0 : f->total_samples;
}