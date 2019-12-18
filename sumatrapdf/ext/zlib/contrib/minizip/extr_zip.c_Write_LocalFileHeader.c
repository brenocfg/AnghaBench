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
struct TYPE_4__ {int /*<<< orphan*/  pos_zip64extrainfo; scalar_t__ zip64; scalar_t__ dosDate; scalar_t__ method; scalar_t__ flag; } ;
struct TYPE_5__ {int /*<<< orphan*/  filestream; int /*<<< orphan*/  z_filefunc; TYPE_1__ ci; } ;
typedef  TYPE_2__ zip64_internal ;
typedef  short uLong ;
typedef  scalar_t__ uInt ;
typedef  short ZPOS64_T ;

/* Variables and functions */
 scalar_t__ LOCALHEADERMAGIC ; 
 int ZIP_ERRNO ; 
 int ZIP_OK ; 
 int /*<<< orphan*/  ZTELL64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZWRITE64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int zip64local_putValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,short,int) ; 

int Write_LocalFileHeader(zip64_internal* zi, const char* filename, uInt size_extrafield_local, const void* extrafield_local)
{
  /* write the local header */
  int err;
  uInt size_filename = (uInt)strlen(filename);
  uInt size_extrafield = size_extrafield_local;

  err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)LOCALHEADERMAGIC, 4);

  if (err==ZIP_OK)
  {
    if(zi->ci.zip64)
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)45,2);/* version needed to extract */
    else
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)20,2);/* version needed to extract */
  }

  if (err==ZIP_OK)
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->ci.flag,2);

  if (err==ZIP_OK)
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->ci.method,2);

  if (err==ZIP_OK)
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)zi->ci.dosDate,4);

  // CRC / Compressed size / Uncompressed size will be filled in later and rewritten later
  if (err==ZIP_OK)
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4); /* crc 32, unknown */
  if (err==ZIP_OK)
  {
    if(zi->ci.zip64)
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0xFFFFFFFF,4); /* compressed size, unknown */
    else
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4); /* compressed size, unknown */
  }
  if (err==ZIP_OK)
  {
    if(zi->ci.zip64)
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0xFFFFFFFF,4); /* uncompressed size, unknown */
    else
      err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)0,4); /* uncompressed size, unknown */
  }

  if (err==ZIP_OK)
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_filename,2);

  if(zi->ci.zip64)
  {
    size_extrafield += 20;
  }

  if (err==ZIP_OK)
    err = zip64local_putValue(&zi->z_filefunc,zi->filestream,(uLong)size_extrafield,2);

  if ((err==ZIP_OK) && (size_filename > 0))
  {
    if (ZWRITE64(zi->z_filefunc,zi->filestream,filename,size_filename)!=size_filename)
      err = ZIP_ERRNO;
  }

  if ((err==ZIP_OK) && (size_extrafield_local > 0))
  {
    if (ZWRITE64(zi->z_filefunc, zi->filestream, extrafield_local, size_extrafield_local) != size_extrafield_local)
      err = ZIP_ERRNO;
  }


  if ((err==ZIP_OK) && (zi->ci.zip64))
  {
      // write the Zip64 extended info
      short HeaderID = 1;
      short DataSize = 16;
      ZPOS64_T CompressedSize = 0;
      ZPOS64_T UncompressedSize = 0;

      // Remember position of Zip64 extended info for the local file header. (needed when we update size after done with file)
      zi->ci.pos_zip64extrainfo = ZTELL64(zi->z_filefunc,zi->filestream);

      err = zip64local_putValue(&zi->z_filefunc, zi->filestream, (short)HeaderID,2);
      err = zip64local_putValue(&zi->z_filefunc, zi->filestream, (short)DataSize,2);

      err = zip64local_putValue(&zi->z_filefunc, zi->filestream, (ZPOS64_T)UncompressedSize,8);
      err = zip64local_putValue(&zi->z_filefunc, zi->filestream, (ZPOS64_T)CompressedSize,8);
  }

  return err;
}