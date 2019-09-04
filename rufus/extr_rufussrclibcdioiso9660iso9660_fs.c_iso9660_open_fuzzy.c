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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  iso9660_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_EXTENSION_NONE ; 
 int /*<<< orphan*/ * iso9660_open_fuzzy_ext (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

iso9660_t *
iso9660_open_fuzzy (const char *psz_path, uint16_t i_fuzz /*, mode*/)
{
  return iso9660_open_fuzzy_ext(psz_path, ISO_EXTENSION_NONE, i_fuzz);
}