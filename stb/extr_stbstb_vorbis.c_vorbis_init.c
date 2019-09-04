#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int alloc_buffer_length_in_bytes; } ;
typedef  TYPE_1__ stb_vorbis_alloc ;
struct TYPE_7__ {int temp_offset; int page_crc_tests; int /*<<< orphan*/ * f; int /*<<< orphan*/  close_on_free; int /*<<< orphan*/ * codebooks; int /*<<< orphan*/ * stream; int /*<<< orphan*/  error; scalar_t__ eof; TYPE_1__ alloc; } ;
typedef  TYPE_2__ stb_vorbis ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  VORBIS__no_error ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vorbis_init(stb_vorbis *p, const stb_vorbis_alloc *z)
{
   memset(p, 0, sizeof(*p)); // NULL out all malloc'd pointers to start
   if (z) {
      p->alloc = *z;
      p->alloc.alloc_buffer_length_in_bytes = (p->alloc.alloc_buffer_length_in_bytes+3) & ~3;
      p->temp_offset = p->alloc.alloc_buffer_length_in_bytes;
   }
   p->eof = 0;
   p->error = VORBIS__no_error;
   p->stream = NULL;
   p->codebooks = NULL;
   p->page_crc_tests = -1;
   #ifndef STB_VORBIS_NO_STDIO
   p->close_on_free = FALSE;
   p->f = NULL;
   #endif
}