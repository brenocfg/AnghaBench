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
struct TYPE_5__ {int temp_offset; TYPE_1__ alloc; } ;
typedef  TYPE_2__ vorb ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void setup_temp_free(vorb *f, void *p, int sz)
{
   if (f->alloc.alloc_buffer) {
      f->temp_offset += (sz+3)&~3;
      return;
   }
   free(p);
}