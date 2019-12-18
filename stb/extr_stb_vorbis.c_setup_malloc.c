#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ alloc_buffer; } ;
struct TYPE_5__ {int setup_memory_required; int setup_offset; scalar_t__ temp_offset; TYPE_1__ alloc; } ;
typedef  TYPE_2__ vorb ;

/* Variables and functions */
 void* malloc (int) ; 

__attribute__((used)) static void *setup_malloc(vorb *f, int sz)
{
   sz = (sz+3) & ~3;
   f->setup_memory_required += sz;
   if (f->alloc.alloc_buffer) {
      void *p = (char *) f->alloc.alloc_buffer + f->setup_offset;
      if (f->setup_offset + sz > f->temp_offset) return NULL;
      f->setup_offset += sz;
      return p;
   }
   return sz ? malloc(sz) : NULL;
}