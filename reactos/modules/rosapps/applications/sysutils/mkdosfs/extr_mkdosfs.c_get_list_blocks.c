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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SECTORS_PER_BLOCK ; 
 int badblocks ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,unsigned long*) ; 
 int /*<<< orphan*/  mark_sector_bad (unsigned long) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 

__attribute__((used)) static void
get_list_blocks (char *filename)
{
  int i;
  FILE *listfile;
  unsigned long blockno;

  listfile = fopen (filename, "r");
  if (listfile == (FILE *) NULL)
    die ("Can't open file of bad blocks");

  while (!feof (listfile))
    {
      fscanf (listfile, "%ld\n", &blockno);
      for (i = 0; i < SECTORS_PER_BLOCK; i++)	/* Mark all of the sectors in the block as bad */
	mark_sector_bad (blockno * SECTORS_PER_BLOCK + i);
      badblocks++;
    }
  fclose (listfile);

  if (badblocks)
    printf ("%d bad block%s\n", badblocks,
	    (badblocks > 1) ? "s" : "");
}