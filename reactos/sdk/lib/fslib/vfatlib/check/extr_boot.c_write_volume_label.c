#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_mon; int tm_year; scalar_t__ tm_mday; } ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ start; scalar_t__ starthi; void* date; void* adate; void* cdate; void* time; void* ctime; scalar_t__ ctime_ms; int /*<<< orphan*/  attr; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  DOS_FS ;
typedef  TYPE_1__ DIR_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_VOLUME ; 
 scalar_t__ alloc_rootdir_entry (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_volume_de (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fs_write (scalar_t__,int,TYPE_1__*) ; 
 void* htole16 (unsigned short) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_volume_label(DOS_FS * fs, char *label)
{
    time_t now = time(NULL);
    struct tm *mtime = localtime(&now);
    off_t offset;
    int created;
    DIR_ENT de;

    created = 0;
    offset = find_volume_de(fs, &de);
    if (offset == 0) {
	created = 1;
	offset = alloc_rootdir_entry(fs, &de, label, 0);
    }
    memcpy(de.name, label, 11);
    de.time = htole16((unsigned short)((mtime->tm_sec >> 1) +
				       (mtime->tm_min << 5) +
				       (mtime->tm_hour << 11)));
    de.date = htole16((unsigned short)(mtime->tm_mday +
				       ((mtime->tm_mon + 1) << 5) +
				       ((mtime->tm_year - 80) << 9)));
    if (created) {
	de.attr = ATTR_VOLUME;
	de.ctime_ms = 0;
	de.ctime = de.time;
	de.cdate = de.date;
	de.adate = de.date;
	de.starthi = 0;
	de.start = 0;
	de.size = 0;
    }

    fs_write(offset, sizeof(DIR_ENT), &de);
}