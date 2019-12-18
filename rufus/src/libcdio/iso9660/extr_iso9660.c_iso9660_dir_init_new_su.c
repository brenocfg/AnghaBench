#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int ISO_BLOCKSIZE ; 
 int /*<<< orphan*/  ISO_DIRECTORY ; 
 int /*<<< orphan*/  cdio_assert (int) ; 
 int /*<<< orphan*/  iso9660_dir_add_entry_su (void*,char*,int,int,int /*<<< orphan*/ ,void const*,unsigned int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void
iso9660_dir_init_new_su (void *dir,
                         uint32_t self,
                         uint32_t ssize,
                         const void *ssu_data,
                         unsigned int ssu_size,
                         uint32_t parent,
                         uint32_t psize,
                         const void *psu_data,
                         unsigned int psu_size,
                         const time_t *dir_time)
{
  cdio_assert (ssize > 0 && !(ssize % ISO_BLOCKSIZE));
  cdio_assert (psize > 0 && !(psize % ISO_BLOCKSIZE));
  cdio_assert (dir != NULL);

  memset (dir, 0, ssize);

  /* "\0" -- working hack due to padding  */
  iso9660_dir_add_entry_su (dir, "\0", self, ssize, ISO_DIRECTORY, ssu_data,
                            ssu_size, dir_time);

  iso9660_dir_add_entry_su (dir, "\1", parent, psize, ISO_DIRECTORY, psu_data,
                            psu_size, dir_time);
}