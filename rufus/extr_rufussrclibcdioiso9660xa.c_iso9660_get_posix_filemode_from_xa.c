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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  posix_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  S_IXUSR ; 
 int XA_ATTR_DIRECTORY ; 
 int XA_PERM_RUSR ; 
 int XA_PERM_XUSR ; 

posix_mode_t 
iso9660_get_posix_filemode_from_xa(uint16_t i_perms) 
{
  posix_mode_t mode = 0;
  
  if (i_perms & XA_PERM_RUSR)  mode |= S_IRUSR;
  if (i_perms & XA_PERM_XUSR)  mode |= S_IXUSR;
  
#ifdef S_IRGRP
  if (i_perms & XA_PERM_RGRP)  mode |= S_IRGRP;
#endif
#ifdef S_IXGRP
  if (i_perms & XA_PERM_XGRP)  mode |= S_IXGRP;
#endif
  
#ifdef S_IROTH
  if (i_perms & XA_PERM_ROTH)  mode |= S_IROTH;
#endif
#ifdef S_IXOTH
  if (i_perms & XA_PERM_XOTH)  mode |= S_IXOTH;
#endif
  
  if (i_perms & XA_ATTR_DIRECTORY)  mode |= S_IFDIR;
  
  return mode;
}