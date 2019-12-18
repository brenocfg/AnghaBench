#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int first_audio_page_offset; } ;
typedef  TYPE_1__ stb_vorbis ;

/* Variables and functions */
 int /*<<< orphan*/  set_file_offset (TYPE_1__*,unsigned int) ; 
 unsigned int stb_vorbis_get_file_offset (TYPE_1__*) ; 
 scalar_t__ vorbis_find_page (TYPE_1__*,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int go_to_page_before(stb_vorbis *f, unsigned int limit_offset)
{
   unsigned int previous_safe, end;

   // now we want to seek back 64K from the limit
   if (limit_offset >= 65536 && limit_offset-65536 >= f->first_audio_page_offset)
      previous_safe = limit_offset - 65536;
   else
      previous_safe = f->first_audio_page_offset;

   set_file_offset(f, previous_safe);

   while (vorbis_find_page(f, &end, NULL)) {
      if (end >= limit_offset && stb_vorbis_get_file_offset(f) < limit_offset)
         return 1;
      set_file_offset(f, end);
   }

   return 0;
}