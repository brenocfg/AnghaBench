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
struct libfat_filesystem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct libfat_filesystem*) ; 
 int /*<<< orphan*/  libfat_flush (struct libfat_filesystem*) ; 

void libfat_close(struct libfat_filesystem *fs)
{
    libfat_flush(fs);
    free(fs);
}