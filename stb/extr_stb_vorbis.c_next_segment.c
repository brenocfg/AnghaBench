#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int last_seg; int next_seg; int last_seg_which; int segment_count; int page_flag; int* segments; int bytes_in_seg; } ;
typedef  TYPE_1__ vorb ;

/* Variables and functions */
 int PAGEFLAG_continued_packet ; 
 int TRUE ; 
 int /*<<< orphan*/  VORBIS_continued_packet_flag_invalid ; 
 int /*<<< orphan*/  assert (int) ; 
 int error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_page (TYPE_1__*) ; 

__attribute__((used)) static int next_segment(vorb *f)
{
   int len;
   if (f->last_seg) return 0;
   if (f->next_seg == -1) {
      f->last_seg_which = f->segment_count-1; // in case start_page fails
      if (!start_page(f)) { f->last_seg = 1; return 0; }
      if (!(f->page_flag & PAGEFLAG_continued_packet)) return error(f, VORBIS_continued_packet_flag_invalid);
   }
   len = f->segments[f->next_seg++];
   if (len < 255) {
      f->last_seg = TRUE;
      f->last_seg_which = f->next_seg-1;
   }
   if (f->next_seg >= f->segment_count)
      f->next_seg = -1;
   assert(f->bytes_in_seg == 0);
   f->bytes_in_seg = len;
   return len;
}