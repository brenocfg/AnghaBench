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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_4__ {void* len; int /*<<< orphan*/ * str; } ;
struct TYPE_5__ {TYPE_1__ filename; int /*<<< orphan*/  volume_sequence_number; void* file_flags; int /*<<< orphan*/  recording_time; void* size; void* extent; void* length; } ;
typedef  TYPE_2__ iso9660_dir_t ;

/* Variables and functions */
 int ISO_BLOCKSIZE ; 
 scalar_t__ MAX_ISOPATHNAME ; 
 int _cdio_ceil2block (int,int) ; 
 unsigned int _cdio_ofs_add (unsigned int,int,int) ; 
 int /*<<< orphan*/  cdio_assert (int) ; 
 int /*<<< orphan*/  from_711 (void*) ; 
 int from_733 (void*) ; 
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/  const*,struct tm*) ; 
 int /*<<< orphan*/  iso9660_set_dtime (struct tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 
 void* to_711 (int) ; 
 int /*<<< orphan*/  to_723 (int) ; 
 void* to_733 (int) ; 

void
iso9660_dir_add_entry_su(void *dir,
                         const char filename[],
                         uint32_t extent,
                         uint32_t size,
                         uint8_t file_flags,
                         const void *su_data,
                         unsigned int su_size,
                         const time_t *entry_time)
{
  iso9660_dir_t *idr = dir;
  uint8_t *dir8 = dir;
  unsigned int offset = 0;
  uint32_t dsize = from_733(idr->size);
  int length, su_offset;
  struct tm temp_tm;
  cdio_assert (sizeof(iso9660_dir_t) == 33);

  if (!dsize && !idr->length)
    dsize = ISO_BLOCKSIZE; /* for when dir lacks '.' entry */

  cdio_assert (dsize > 0 && !(dsize % ISO_BLOCKSIZE));
  cdio_assert (dir != NULL);
  cdio_assert (extent > 17);
  cdio_assert (filename != NULL);
  cdio_assert (strlen(filename) <= MAX_ISOPATHNAME);

  length = sizeof(iso9660_dir_t);
  length += strlen(filename);
  length = _cdio_ceil2block (length, 2); /* pad to word boundary */
  su_offset = length;
  length += su_size;
  length = _cdio_ceil2block (length, 2); /* pad to word boundary again */

  /* find the last entry's end */
  {
    unsigned int ofs_last_rec = 0;

    offset = 0;
    while (offset < dsize)
      {
        if (!dir8[offset])
          {
            offset++;
            continue;
          }

        offset += dir8[offset];
        ofs_last_rec = offset;
      }

    cdio_assert (offset == dsize);

    offset = ofs_last_rec;
  }

  /* be sure we don't cross sectors boundaries */
  offset = _cdio_ofs_add (offset, length, ISO_BLOCKSIZE);
  offset -= length;

  cdio_assert (offset + length <= dsize);

  idr = (iso9660_dir_t *) &dir8[offset];

  cdio_assert (offset+length < dsize);

  memset(idr, 0, length);

  idr->length = to_711(length);
  idr->extent = to_733(extent);
  idr->size = to_733(size);

  gmtime_r(entry_time, &temp_tm);
  iso9660_set_dtime (&temp_tm, &(idr->recording_time));

  idr->file_flags = to_711(file_flags);

  idr->volume_sequence_number = to_723(1);

  idr->filename.len = to_711(strlen(filename)
                             ? strlen(filename) : 1); /* working hack! */

  memcpy(&idr->filename.str[1], filename, from_711(idr->filename.len));
  if (su_size > 0 && su_data)
    memcpy(&dir8[offset] + su_offset, su_data, su_size);
}