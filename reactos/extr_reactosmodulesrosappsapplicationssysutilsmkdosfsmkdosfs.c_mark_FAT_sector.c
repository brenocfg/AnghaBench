#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cluster_size; } ;

/* Variables and functions */
 int HARD_SECTOR_SIZE ; 
 TYPE_1__ bs ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  mark_FAT_cluster (int,unsigned int) ; 
 int sector_size ; 
 int start_data_sector ; 

__attribute__((used)) static void
mark_FAT_sector (int sector, unsigned int value)
{
  int cluster;

  cluster = (sector - start_data_sector) / (int) (bs.cluster_size) /
	    (sector_size/HARD_SECTOR_SIZE);
  if (cluster < 0)
    die ("Invalid cluster number in mark_FAT_sector: probably bug!");

  mark_FAT_cluster (cluster, value);
}