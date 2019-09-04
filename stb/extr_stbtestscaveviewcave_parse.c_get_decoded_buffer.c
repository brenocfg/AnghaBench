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
struct TYPE_6__ {int valid; int cx; int cz; TYPE_2__* fc; } ;
typedef  TYPE_1__ decoded_buffer ;
struct TYPE_7__ {struct TYPE_7__* pointer_to_free; } ;

/* Variables and functions */
 int MAX_DECODED_CHUNK_X ; 
 int MAX_DECODED_CHUNK_Z ; 
 TYPE_1__** decoded_buffers ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* get_decoded_fastchunk_uncached (int,int) ; 

decoded_buffer *get_decoded_buffer(int chunk_x, int chunk_z)
{
   decoded_buffer *db = &decoded_buffers[chunk_z&(MAX_DECODED_CHUNK_Z-1)][chunk_x&(MAX_DECODED_CHUNK_X-1)];
   if (db->valid) {
      if (db->cx == chunk_x && db->cz == chunk_z)
         return db;
      if (db->fc) {
         free(db->fc->pointer_to_free);
         free(db->fc);
      }
   }

   db->cx = chunk_x;
   db->cz = chunk_z;
   db->valid = 1;
   db->fc = 0;

   {
      db->fc = get_decoded_fastchunk_uncached(chunk_x, chunk_z);
      return db;
   }
}