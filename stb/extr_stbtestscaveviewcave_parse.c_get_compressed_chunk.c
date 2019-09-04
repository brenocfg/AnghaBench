#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_7__ {int** sector_data; } ;
typedef  TYPE_1__ region ;
struct TYPE_8__ {int x; int z; int len; int refcount; void* data; } ;
typedef  TYPE_2__ compressed_chunk ;

/* Variables and functions */
 int NUM_CACHED_X ; 
 int NUM_CACHED_Z ; 
 int NUM_CHUNKS_PER_REGION ; 
 int NUM_CHUNKS_PER_REGION_LOG2 ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__*** cached_chunk ; 
 int /*<<< orphan*/  deref_compressed_chunk (TYPE_2__*) ; 
 int /*<<< orphan*/  fread (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_region (int,int) ; 
 int /*<<< orphan*/  last_region ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  open_file (int,int) ; 

__attribute__((used)) static compressed_chunk *get_compressed_chunk(int chunk_x, int chunk_z)
{
   int slot_x = chunk_x & (NUM_CACHED_X-1);
   int slot_z = chunk_z & (NUM_CACHED_Z-1);
   compressed_chunk *cc = cached_chunk[slot_z][slot_x];

   if (cc && cc->x == chunk_x && cc->z == chunk_z)
      return cc;
   else {
      int reg_x = chunk_x >> NUM_CHUNKS_PER_REGION_LOG2;
      int reg_z = chunk_z >> NUM_CHUNKS_PER_REGION_LOG2;
      region *r = get_region(reg_x, reg_z);
      if (cc) {
         deref_compressed_chunk(cc);
         cached_chunk[slot_z][slot_x] = NULL;
      }
      cc = malloc(sizeof(*cc));
      cc->x = chunk_x;
      cc->z = chunk_z;
      {
         int subchunk_x = chunk_x & (NUM_CHUNKS_PER_REGION-1);
         int subchunk_z = chunk_z & (NUM_CHUNKS_PER_REGION-1);
         uint32 code = r->sector_data[subchunk_z][subchunk_x];

         if (code & 255) {
            open_file(reg_x, reg_z);
            fseek(last_region, (code>>8)*4096, SEEK_SET);
            cc->len = (code&255)*4096;
            cc->data = malloc(cc->len);
            fread(cc->data, 1, cc->len, last_region);
         } else {
            cc->len = 0;
            cc->data = 0;
         }
      }
      cc->refcount = 1;
      cached_chunk[slot_z][slot_x] = cc;
      return cc;
   }
}