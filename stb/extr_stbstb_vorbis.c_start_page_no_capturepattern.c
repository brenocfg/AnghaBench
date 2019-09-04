#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int last_decoded_sample; scalar_t__ page_start; scalar_t__ page_end; } ;
struct TYPE_8__ {unsigned int last_page; int segment_count; int* segments; int end_seg_with_known_loc; unsigned int known_loc_for_packet; scalar_t__ next_seg; TYPE_2__ p_first; scalar_t__ first_audio_page_offset; scalar_t__ first_decode; scalar_t__ page_flag; } ;
typedef  TYPE_1__ vorb ;
typedef  unsigned int uint32 ;
typedef  TYPE_2__ ProbedPage ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  VORBIS_invalid_stream_structure_version ; 
 int /*<<< orphan*/  VORBIS_unexpected_eof ; 
 int error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int get32 (TYPE_1__*) ; 
 scalar_t__ get8 (TYPE_1__*) ; 
 int /*<<< orphan*/  getn (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int start_page_no_capturepattern(vorb *f)
{
   uint32 loc0,loc1,n;
   // stream structure version
   if (0 != get8(f)) return error(f, VORBIS_invalid_stream_structure_version);
   // header flag
   f->page_flag = get8(f);
   // absolute granule position
   loc0 = get32(f); 
   loc1 = get32(f);
   // @TODO: validate loc0,loc1 as valid positions?
   // stream serial number -- vorbis doesn't interleave, so discard
   get32(f);
   //if (f->serial != get32(f)) return error(f, VORBIS_incorrect_stream_serial_number);
   // page sequence number
   n = get32(f);
   f->last_page = n;
   // CRC32
   get32(f);
   // page_segments
   f->segment_count = get8(f);
   if (!getn(f, f->segments, f->segment_count))
      return error(f, VORBIS_unexpected_eof);
   // assume we _don't_ know any the sample position of any segments
   f->end_seg_with_known_loc = -2;
   if (loc0 != ~0U || loc1 != ~0U) {
      int i;
      // determine which packet is the last one that will complete
      for (i=f->segment_count-1; i >= 0; --i)
         if (f->segments[i] < 255)
            break;
      // 'i' is now the index of the _last_ segment of a packet that ends
      if (i >= 0) {
         f->end_seg_with_known_loc = i;
         f->known_loc_for_packet   = loc0;
      }
   }
   if (f->first_decode) {
      int i,len;
      ProbedPage p;
      len = 0;
      for (i=0; i < f->segment_count; ++i)
         len += f->segments[i];
      len += 27 + f->segment_count;
      p.page_start = f->first_audio_page_offset;
      p.page_end = p.page_start + len;
      p.last_decoded_sample = loc0;
      f->p_first = p;
   }
   f->next_seg = 0;
   return TRUE;
}