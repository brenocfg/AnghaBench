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
typedef  int /*<<< orphan*/  iso_extension_mask_t ;
typedef  int /*<<< orphan*/  iso9660_t ;

/* Variables and functions */
 int /*<<< orphan*/ * iso9660_open_ext_private (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

iso9660_t *
iso9660_open_ext (const char *psz_path,
		  iso_extension_mask_t iso_extension_mask)
{
  return iso9660_open_ext_private(psz_path, iso_extension_mask, 0, false);
}