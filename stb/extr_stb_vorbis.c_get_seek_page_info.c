#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8 ;
typedef  int /*<<< orphan*/  stb_vorbis ;
struct TYPE_3__ {char last_decoded_sample; scalar_t__ page_start; scalar_t__ page_end; } ;
typedef  TYPE_1__ ProbedPage ;

/* Variables and functions */
 int /*<<< orphan*/  getn (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  set_file_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ stb_vorbis_get_file_offset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_seek_page_info(stb_vorbis *f, ProbedPage *z)
{
   uint8 header[27], lacing[255];
   int i,len;

   // record where the page starts
   z->page_start = stb_vorbis_get_file_offset(f);

   // parse the header
   getn(f, header, 27);
   if (header[0] != 'O' || header[1] != 'g' || header[2] != 'g' || header[3] != 'S')
      return 0;
   getn(f, lacing, header[26]);

   // determine the length of the payload
   len = 0;
   for (i=0; i < header[26]; ++i)
      len += lacing[i];

   // this implies where the page ends
   z->page_end = z->page_start + 27 + header[26] + len;

   // read the last-decoded sample out of the data
   z->last_decoded_sample = header[6] + (header[7] << 8) + (header[8] << 16) + (header[9] << 24);

   // restore file state to where we were
   set_file_offset(f, z->page_start);
   return 1;
}