#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {char* str; } ;
struct TYPE_6__ {TYPE_1__ filename; } ;
typedef  TYPE_2__ iso9660_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_assert (int) ; 
 int iso9660_get_dir_len (TYPE_2__ const*) ; 
 char* strdup (char*) ; 

char *
iso9660_dir_to_name (const iso9660_dir_t *iso9660_dir)
{
  uint8_t len=iso9660_get_dir_len(iso9660_dir);

  if (!len) return NULL;

  cdio_assert (len >= sizeof (iso9660_dir_t));

  /* (iso9660_dir->file_flags & ISO_DIRECTORY) */

  if (iso9660_dir->filename.str[1] == '\0')
    return strdup(".");
  else if (iso9660_dir->filename.str[1] == '\1')
    return strdup("..");
  else {
    return strdup(&iso9660_dir->filename.str[1]);
  }
}