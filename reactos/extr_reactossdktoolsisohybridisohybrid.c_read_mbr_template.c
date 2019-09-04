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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t MBRSIZE ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 

void
read_mbr_template(char *path, uint8_t *mbr)
{
    FILE *fp;
    size_t ret;

    fp = fopen(path, "rb");
    if (fp == NULL)
        err(1, "could not open MBR template file `%s'", path);
    clearerr(fp);
    ret = fread(mbr, 1, MBRSIZE, fp);
    if (ferror(fp) || ret != MBRSIZE)
        err(1, "error while reading MBR template file `%s'", path);
    fclose(fp);
}