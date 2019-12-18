#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int file_type; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ icb_tag; int /*<<< orphan*/  permissions; } ;
typedef  TYPE_2__ udf_file_entry_t ;
typedef  int /*<<< orphan*/  udf_dirent_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int FE_PERM_G_EXEC ; 
 int FE_PERM_G_READ ; 
 int FE_PERM_G_WRITE ; 
 int FE_PERM_O_EXEC ; 
 int FE_PERM_O_READ ; 
 int FE_PERM_O_WRITE ; 
 int FE_PERM_U_EXEC ; 
 int FE_PERM_U_READ ; 
 int FE_PERM_U_WRITE ; 
#define  ICBTAG_FILE_TYPE_BLOCK 133 
#define  ICBTAG_FILE_TYPE_CHAR 132 
#define  ICBTAG_FILE_TYPE_DIRECTORY 131 
#define  ICBTAG_FILE_TYPE_REGULAR 130 
#define  ICBTAG_FILE_TYPE_SOCKET 129 
#define  ICBTAG_FILE_TYPE_SYMLINK 128 
 int ICBTAG_FLAG_SETGID ; 
 int ICBTAG_FLAG_SETUID ; 
 int ICBTAG_FLAG_STICKY ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  S_IFSOCK ; 
 int /*<<< orphan*/  S_IRGRP ; 
 int /*<<< orphan*/  S_IROTH ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  S_ISGID ; 
 int /*<<< orphan*/  S_ISUID ; 
 int /*<<< orphan*/  S_ISVTX ; 
 int /*<<< orphan*/  S_IWGRP ; 
 int /*<<< orphan*/  S_IWOTH ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  S_IXGRP ; 
 int /*<<< orphan*/  S_IXOTH ; 
 int /*<<< orphan*/  S_IXUSR ; 
 scalar_t__ udf_get_file_entry (int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int uint16_from_le (int /*<<< orphan*/ ) ; 
 int uint32_from_le (int /*<<< orphan*/ ) ; 

mode_t 
udf_get_posix_filemode(const udf_dirent_t *p_udf_dirent) 
{
  udf_file_entry_t udf_fe;
  mode_t mode = 0;

  if (udf_get_file_entry(p_udf_dirent, &udf_fe)) {
    uint32_t i_perms;
#ifdef S_ISUID
    uint16_t i_flags;

    i_flags = uint16_from_le(udf_fe.icb_tag.flags);
#endif
    i_perms = uint32_from_le(udf_fe.permissions);

    if (i_perms & FE_PERM_U_READ)  mode |= S_IRUSR;
    if (i_perms & FE_PERM_U_WRITE) mode |= S_IWUSR;
    if (i_perms & FE_PERM_U_EXEC)  mode |= S_IXUSR;
    
#ifdef S_IRGRP
    if (i_perms & FE_PERM_G_READ)  mode |= S_IRGRP;
    if (i_perms & FE_PERM_G_WRITE) mode |= S_IWGRP;
    if (i_perms & FE_PERM_G_EXEC)  mode |= S_IXGRP;
#endif
    
#ifdef S_IROTH
    if (i_perms & FE_PERM_O_READ)  mode |= S_IROTH;
    if (i_perms & FE_PERM_O_WRITE) mode |= S_IWOTH;
    if (i_perms & FE_PERM_O_EXEC)  mode |= S_IXOTH;
#endif

    switch (udf_fe.icb_tag.file_type) {
    case ICBTAG_FILE_TYPE_DIRECTORY: 
      mode |= S_IFDIR;
      break;
    case ICBTAG_FILE_TYPE_REGULAR:
      mode |= S_IFREG;
      break;
#ifdef S_IFLNK
    case ICBTAG_FILE_TYPE_SYMLINK:
      mode |= S_IFLNK;
      break;
#endif
    case ICBTAG_FILE_TYPE_CHAR:
      mode |= S_IFCHR;
      break;
#ifdef S_IFSOCK
    case ICBTAG_FILE_TYPE_SOCKET:
      mode |= S_IFSOCK;
      break;
#endif
    case ICBTAG_FILE_TYPE_BLOCK:
      mode |= S_IFBLK;
      break;
    default: ;
    };
  
#ifdef S_ISUID
    if (i_flags & ICBTAG_FLAG_SETUID) mode |= S_ISUID;
    if (i_flags & ICBTAG_FLAG_SETGID) mode |= S_ISGID;
    if (i_flags & ICBTAG_FLAG_STICKY) mode |= S_ISVTX;
#endif
  }
  
  return mode;
  
}