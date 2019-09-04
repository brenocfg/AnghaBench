#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  filestream; int /*<<< orphan*/  z_filefunc; } ;
typedef  TYPE_1__ zip64_internal ;
typedef  int /*<<< orphan*/  uLong ;
typedef  scalar_t__ uInt ;

/* Variables and functions */
 int ZIP_ERRNO ; 
 int ZIP_OK ; 
 scalar_t__ ZWRITE64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int zip64local_putValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int Write_GlobalComment(zip64_internal* zi, const char* global_comment)
{
  int err = ZIP_OK;
  uInt size_global_comment = 0;

  if(global_comment != NULL)
    size_global_comment = (uInt)strlen(global_comment);

  err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_global_comment,2);

  if (err == ZIP_OK && size_global_comment > 0)
  {
    if (ZWRITE64(zi->z_filefunc,zi->filestream, global_comment, size_global_comment) != size_global_comment)
      err = ZIP_ERRNO;
  }
  return err;
}