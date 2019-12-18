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
typedef  int uint8 ;
struct TYPE_4__ {int next_seg; int* stream; int segment_count; int* segments; int* stream_end; scalar_t__ previous_length; } ;
typedef  TYPE_1__ stb_vorbis ;

/* Variables and functions */
 int FALSE ; 
 int PAGEFLAG_continued_packet ; 
 int TRUE ; 
 int /*<<< orphan*/  VORBIS_invalid_stream ; 
 int /*<<< orphan*/  VORBIS_need_more_data ; 
 int error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_page_header ; 

__attribute__((used)) static int is_whole_packet_present(stb_vorbis *f, int end_page)
{
   // make sure that we have the packet available before continuing...
   // this requires a full ogg parse, but we know we can fetch from f->stream

   // instead of coding this out explicitly, we could save the current read state,
   // read the next packet with get8() until end-of-packet, check f->eof, then
   // reset the state? but that would be slower, esp. since we'd have over 256 bytes
   // of state to restore (primarily the page segment table)

   int s = f->next_seg, first = TRUE;
   uint8 *p = f->stream;

   if (s != -1) { // if we're not starting the packet with a 'continue on next page' flag
      for (; s < f->segment_count; ++s) {
         p += f->segments[s];
         if (f->segments[s] < 255)               // stop at first short segment
            break;
      }
      // either this continues, or it ends it...
      if (end_page)
         if (s < f->segment_count-1)             return error(f, VORBIS_invalid_stream);
      if (s == f->segment_count)
         s = -1; // set 'crosses page' flag
      if (p > f->stream_end)                     return error(f, VORBIS_need_more_data);
      first = FALSE;
   }
   for (; s == -1;) {
      uint8 *q; 
      int n;

      // check that we have the page header ready
      if (p + 26 >= f->stream_end)               return error(f, VORBIS_need_more_data);
      // validate the page
      if (memcmp(p, ogg_page_header, 4))         return error(f, VORBIS_invalid_stream);
      if (p[4] != 0)                             return error(f, VORBIS_invalid_stream);
      if (first) { // the first segment must NOT have 'continued_packet', later ones MUST
         if (f->previous_length)
            if ((p[5] & PAGEFLAG_continued_packet))  return error(f, VORBIS_invalid_stream);
         // if no previous length, we're resynching, so we can come in on a continued-packet,
         // which we'll just drop
      } else {
         if (!(p[5] & PAGEFLAG_continued_packet)) return error(f, VORBIS_invalid_stream);
      }
      n = p[26]; // segment counts
      q = p+27;  // q points to segment table
      p = q + n; // advance past header
      // make sure we've read the segment table
      if (p > f->stream_end)                     return error(f, VORBIS_need_more_data);
      for (s=0; s < n; ++s) {
         p += q[s];
         if (q[s] < 255)
            break;
      }
      if (end_page)
         if (s < n-1)                            return error(f, VORBIS_invalid_stream);
      if (s == n)
         s = -1; // set 'crosses page' flag
      if (p > f->stream_end)                     return error(f, VORBIS_need_more_data);
      first = FALSE;
   }
   return TRUE;
}