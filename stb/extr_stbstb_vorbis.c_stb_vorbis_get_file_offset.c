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
struct TYPE_4__ {scalar_t__ f_start; int /*<<< orphan*/  f; scalar_t__ stream_start; scalar_t__ stream; scalar_t__ push_mode; } ;
typedef  TYPE_1__ stb_vorbis ;

/* Variables and functions */
 scalar_t__ USE_MEMORY (TYPE_1__*) ; 
 scalar_t__ ftell (int /*<<< orphan*/ ) ; 

unsigned int stb_vorbis_get_file_offset(stb_vorbis *f)
{
   #ifndef STB_VORBIS_NO_PUSHDATA_API
   if (f->push_mode) return 0;
   #endif
   if (USE_MEMORY(f)) return (unsigned int) (f->stream - f->stream_start);
   #ifndef STB_VORBIS_NO_STDIO
   return (unsigned int) (ftell(f->f) - f->f_start);
   #endif
}