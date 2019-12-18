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
typedef  int posix_mode_t ;

/* Variables and functions */
 int ISO_ROCK_IRGRP ; 
 int ISO_ROCK_IROTH ; 
 int ISO_ROCK_IRUSR ; 
 int ISO_ROCK_ISGID ; 
 int ISO_ROCK_ISUID ; 
 int ISO_ROCK_IWGRP ; 
 int ISO_ROCK_IWOTH ; 
 int ISO_ROCK_IWUSR ; 
 int ISO_ROCK_IXGRP ; 
 int ISO_ROCK_IXOTH ; 
 int ISO_ROCK_IXUSR ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 char* _getbuf () ; 

const char *
iso9660_get_rock_attr_str(posix_mode_t st_mode)
{
  char *result = _getbuf();

  if (S_ISBLK(st_mode))
    result[ 0] = 'b';
  else if (S_ISDIR(st_mode))
    result[ 0] = 'd';
  else if (S_ISCHR(st_mode))
    result[ 0] = 'c';
  else if (S_ISLNK(st_mode))
    result[ 0] = 'l';
  else if (S_ISFIFO(st_mode))
    result[ 0] = 'p';
  else if (S_ISSOCK(st_mode))
    result[ 0] = 's';
  /* May eventually fill in others.. */
  else
    result[ 0] = '-';

  result[ 1] = (st_mode & ISO_ROCK_IRUSR) ? 'r' : '-';
  result[ 2] = (st_mode & ISO_ROCK_IWUSR) ? 'w' : '-';

  if (st_mode & ISO_ROCK_ISUID)
    result[ 3] = (st_mode & ISO_ROCK_IXUSR) ? 's' : 'S';
  else
    result[ 3] = (st_mode & ISO_ROCK_IXUSR) ? 'x' : '-';

  result[ 4] = (st_mode & ISO_ROCK_IRGRP) ? 'r' : '-';
  result[ 5] = (st_mode & ISO_ROCK_IWGRP) ? 'w' : '-';

  if (st_mode & ISO_ROCK_ISGID)
    result[ 6] = (st_mode & ISO_ROCK_IXGRP) ? 's' : 'S';
  else
    result[ 6] = (st_mode & ISO_ROCK_IXGRP) ? 'x' : '-';

  result[ 7] = (st_mode & ISO_ROCK_IROTH) ? 'r' : '-';
  result[ 8] = (st_mode & ISO_ROCK_IWOTH) ? 'w' : '-';
  result[ 9] = (st_mode & ISO_ROCK_IXOTH) ? 'x' : '-';

  result[11] = '\0';

  return result;
}