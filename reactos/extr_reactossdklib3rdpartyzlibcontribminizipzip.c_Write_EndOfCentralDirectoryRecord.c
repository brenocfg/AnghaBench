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
struct TYPE_3__ {int number_entry; int add_position_when_writing_offset; int /*<<< orphan*/  filestream; int /*<<< orphan*/  z_filefunc; } ;
typedef  TYPE_1__ zip64_internal ;
typedef  scalar_t__ uLong ;
typedef  int ZPOS64_T ;

/* Variables and functions */
 scalar_t__ ENDHEADERMAGIC ; 
 int ZIP_OK ; 
 int zip64local_putValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 

int Write_EndOfCentralDirectoryRecord(zip64_internal* zi, uLong size_centraldir, ZPOS64_T centraldir_pos_inzip)
{
  int err = ZIP_OK;

  /*signature*/
  err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)ENDHEADERMAGIC,4);

  if (err==ZIP_OK) /* number of this disk */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,2);

  if (err==ZIP_OK) /* number of the disk with the start of the central directory */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,2);

  if (err==ZIP_OK) /* total number of entries in the central dir on this disk */
  {
    {
      if(zi->number_entry >= 0xFFFF)
        err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0xffff,2); // use value in ZIP64 record
      else
        err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->number_entry,2);
    }
  }

  if (err==ZIP_OK) /* total number of entries in the central dir */
  {
    if(zi->number_entry >= 0xFFFF)
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0xffff,2); // use value in ZIP64 record
    else
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->number_entry,2);
  }

  if (err==ZIP_OK) /* size of the central directory */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_centraldir,4);

  if (err==ZIP_OK) /* offset of start of central directory with respect to the starting disk number */
  {
    ZPOS64_T pos = centraldir_pos_inzip - zi->add_position_when_writing_offset;
    if(pos >= 0xffffffff)
    {
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream, (uLong)0xffffffff,4);
    }
    else
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream, (uLong)(centraldir_pos_inzip - zi->add_position_when_writing_offset),4);
  }

   return err;
}