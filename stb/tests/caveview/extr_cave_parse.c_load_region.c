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
struct TYPE_5__ {int x; int z; int /*<<< orphan*/ ** sector_data; } ;
typedef  TYPE_1__ region ;

/* Variables and functions */
 int NUM_CHUNKS_PER_REGION ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * last_region ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open_file (int,int) ; 
 int /*<<< orphan*/  read_uint32_be (int /*<<< orphan*/ *) ; 

__attribute__((used)) static region *load_region(int reg_x, int reg_z)
{
   region *r;
   int x,z;

   open_file(reg_x, reg_z);

   r = malloc(sizeof(*r));

   if (last_region == NULL) {
      memset(r, 0, sizeof(*r));
   } else {
      fseek(last_region, 0, SEEK_SET);
      for (z=0; z < NUM_CHUNKS_PER_REGION; ++z)
         for (x=0; x < NUM_CHUNKS_PER_REGION; ++x)
            r->sector_data[z][x] = read_uint32_be(last_region);
   }
   r->x = reg_x;
   r->z = reg_z;

   return r;
}