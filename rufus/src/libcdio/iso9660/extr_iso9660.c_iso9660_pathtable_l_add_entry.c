#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  name; int /*<<< orphan*/  extent; int /*<<< orphan*/  name_len; } ;
typedef  TYPE_1__ iso_path_table_t ;

/* Variables and functions */
 scalar_t__ ISO_BLOCKSIZE ; 
 int /*<<< orphan*/  cdio_assert (int) ; 
 scalar_t__ from_721 (int /*<<< orphan*/ ) ; 
 scalar_t__ iso9660_pathtable_get_size (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pathtable_get_entry (void*,unsigned int) ; 
 int /*<<< orphan*/  pathtable_get_size_and_entries (void*,int /*<<< orphan*/ *,unsigned int*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  to_711 (size_t) ; 
 int /*<<< orphan*/  to_721 (scalar_t__) ; 
 int /*<<< orphan*/  to_731 (int /*<<< orphan*/ ) ; 

uint16_t
iso9660_pathtable_l_add_entry (void *pt,
                               const char name[],
                               uint32_t extent,
                               uint16_t parent)
{
  iso_path_table_t *ipt =
    (iso_path_table_t *)((char *)pt + iso9660_pathtable_get_size (pt));
  size_t name_len = strlen (name) ? strlen (name) : 1;
  unsigned int entrynum = 0;

  cdio_assert (iso9660_pathtable_get_size (pt) < ISO_BLOCKSIZE); /*fixme */

  memset (ipt, 0, sizeof (iso_path_table_t) + name_len); /* paranoia */

  ipt->name_len = to_711 (name_len);
  ipt->extent = to_731 (extent);
  ipt->parent = to_721 (parent);
  memcpy (ipt->name, name, name_len);

  pathtable_get_size_and_entries (pt, NULL, &entrynum);

  if (entrynum > 1)
    {
      const iso_path_table_t *ipt2
        = pathtable_get_entry (pt, entrynum - 2);

      cdio_assert (ipt2 != NULL);

      cdio_assert (from_721 (ipt2->parent) <= parent);
    }

  return entrynum;
}