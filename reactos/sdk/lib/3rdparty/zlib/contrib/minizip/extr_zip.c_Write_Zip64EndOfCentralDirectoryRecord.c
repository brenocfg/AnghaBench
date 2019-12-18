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
typedef  int uLong ;
typedef  int ZPOS64_T ;

/* Variables and functions */
 scalar_t__ ZIP64ENDHEADERMAGIC ; 
 int ZIP_OK ; 
 int zip64local_putValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int Write_Zip64EndOfCentralDirectoryRecord(zip64_internal* zi, uLong size_centraldir, ZPOS64_T centraldir_pos_inzip)
{
  int err = ZIP_OK;

  uLong Zip64DataSize = 44;

  err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)ZIP64ENDHEADERMAGIC,4);

  if (err==ZIP_OK) /* size of this 'zip64 end of central directory' */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(ZPOS64_T)Zip64DataSize,8); // why ZPOS64_T of this ?

  if (err==ZIP_OK) /* version made by */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)45,2);

  if (err==ZIP_OK) /* version needed */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)45,2);

  if (err==ZIP_OK) /* number of this disk */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4);

  if (err==ZIP_OK) /* number of the disk with the start of the central directory */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4);

  if (err==ZIP_OK) /* total number of entries in the central dir on this disk */
    err = zip64local_putValue(&zi->z_filefunc, zi->filestream, zi->number_entry, 8);

  if (err==ZIP_OK) /* total number of entries in the central dir */
    err = zip64local_putValue(&zi->z_filefunc, zi->filestream, zi->number_entry, 8);

  if (err==ZIP_OK) /* size of the central directory */
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(ZPOS64_T)size_centraldir,8);

  if (err==ZIP_OK) /* offset of start of central directory with respect to the starting disk number */
  {
    ZPOS64_T pos = centraldir_pos_inzip - zi->add_position_when_writing_offset;
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream, (ZPOS64_T)pos,8);
  }
  return err;
}