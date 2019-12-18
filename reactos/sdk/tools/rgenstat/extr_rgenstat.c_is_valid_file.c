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
typedef  int /*<<< orphan*/  ext ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int
is_valid_file(char *filename)
{
  char ext[MAX_PATH];
  int i;

  i = strlen(filename);
  while (i > 0 && filename[i] != '.')
    {
      i--;
    }
  if (i > 0)
    {
      memset(ext, 0, sizeof(ext));
      strncpy(&ext[0], &filename[i], strlen(&filename[i]));

      if ((strncmp(ext, ".c", 2) == 0) || (strncmp(ext, ".C", 2) == 0))
        {
          return 1;
        }
    }
  return 0;
}