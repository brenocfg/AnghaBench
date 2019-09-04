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
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  fbuf; int /*<<< orphan*/  vbuf; int /*<<< orphan*/  fbuf_tex; } ;
typedef  TYPE_1__ chunk_mesh ;

/* Variables and functions */
 scalar_t__ STATE_invalid ; 
 scalar_t__ STATE_valid ; 
 TYPE_1__** cached_chunk_mesh ; 
 int /*<<< orphan*/  glDeleteBuffersARB (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 

void free_chunk(int slot_x, int slot_y)
{
   chunk_mesh *cm = &cached_chunk_mesh[slot_y][slot_x];
   if (cm->state == STATE_valid) {
      glDeleteTextures(1, &cm->fbuf_tex);
      glDeleteBuffersARB(1, &cm->vbuf);
      glDeleteBuffersARB(1, &cm->fbuf);
      cached_chunk_mesh[slot_y][slot_x].state = STATE_invalid;
   }
}