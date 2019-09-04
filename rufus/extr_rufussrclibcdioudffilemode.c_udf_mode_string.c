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
typedef  int mode_t ;

/* Variables and functions */
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 char ftypelet (int) ; 
 int /*<<< orphan*/  setst (int,char*) ; 

char *
udf_mode_string (mode_t i_mode, char *psz_str)
{
  psz_str[ 0] = ftypelet (i_mode);
  psz_str[ 1] = i_mode & S_IRUSR ? 'r' : '-';
  psz_str[ 2] = i_mode & S_IWUSR ? 'w' : '-';
  psz_str[ 3] = i_mode & S_IXUSR ? 'x' : '-';
  psz_str[ 4] = i_mode & S_IRGRP ? 'r' : '-';
  psz_str[ 5] = i_mode & S_IWGRP ? 'w' : '-';
  psz_str[ 6] = i_mode & S_IXGRP ? 'x' : '-';
  psz_str[ 7] = i_mode & S_IROTH ? 'r' : '-';
  psz_str[ 8] = i_mode & S_IWOTH ? 'w' : '-';
  psz_str[ 9] = i_mode & S_IXOTH ? 'x' : '-';
  psz_str[10] = '\0';
  setst (i_mode, psz_str);
  return psz_str;
}