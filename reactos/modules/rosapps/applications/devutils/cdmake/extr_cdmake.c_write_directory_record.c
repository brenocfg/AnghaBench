#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ offset; } ;
struct TYPE_5__ {int year; char month; char day; char hour; char minute; char second; } ;
struct TYPE_6__ {char* joliet_name; char* name_on_cd; char* extension_on_cd; char flags; TYPE_1__ date_and_time; int /*<<< orphan*/  size; int /*<<< orphan*/  sector; int /*<<< orphan*/  joliet_size; int /*<<< orphan*/  joliet_sector; } ;
typedef  TYPE_2__* PDIR_RECORD ;
typedef  int DIR_RECORD_TYPE ;
typedef  char BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  DOT_DOT_RECORD 131 
#define  DOT_RECORD 130 
#define  FILE_RECORD 129 
 scalar_t__ SECTOR_SIZE ; 
#define  SUBDIRECTORY_RECORD 128 
 TYPE_4__ cd ; 
 int /*<<< orphan*/  fill_sector () ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  write_both_endian_dword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_both_endian_word (int) ; 
 int /*<<< orphan*/  write_byte (char) ; 
 int /*<<< orphan*/  write_string (char*) ; 
 int /*<<< orphan*/  write_string_as_big_endian_unicode (char*) ; 

__attribute__((used)) static void
write_directory_record(PDIR_RECORD d,
                       DIR_RECORD_TYPE DirType,
                       BOOL joliet)
{
    unsigned identifier_size;
    unsigned record_size;

    if (joliet)
    {
        if (DirType == DOT_RECORD || DirType == DOT_DOT_RECORD)
            identifier_size = 1;
        else
            identifier_size = strlen(d->joliet_name) * 2;
    }
    else
    {
        switch (DirType)
        {
            case DOT_RECORD:
            case DOT_DOT_RECORD:
                identifier_size = 1;
                break;
            case SUBDIRECTORY_RECORD:
                /*printf("Subdir: %s\n", d->name_on_cd);*/
                identifier_size = strlen(d->name_on_cd);
                break;
            case FILE_RECORD:
                /*printf("File: %s.%s -> %s.%s\n", d->name, d->extension, d->name_on_cd, d->extension_on_cd);*/
                identifier_size = strlen(d->name_on_cd) + 2;
                if (d->extension_on_cd[0] != 0)
                    identifier_size += 1 + strlen(d->extension_on_cd);
                break;
            default:
                identifier_size = 1;
                break;
        }
    }
    record_size = 33 + identifier_size;
    if ((identifier_size & 1) == 0)
        record_size++;
    if (cd.offset + record_size > SECTOR_SIZE)
        fill_sector();
    write_byte((BYTE)record_size);
    write_byte(0); // number of sectors in extended attribute record
    if (joliet)
    {
        write_both_endian_dword(d->joliet_sector);
        write_both_endian_dword(d->joliet_size);
    }
    else
    {
        write_both_endian_dword(d->sector);
        write_both_endian_dword(d->size);
    }
    write_byte((BYTE)(d->date_and_time.year - 1900));
    write_byte(d->date_and_time.month);
    write_byte(d->date_and_time.day);
    write_byte(d->date_and_time.hour);
    write_byte(d->date_and_time.minute);
    write_byte(d->date_and_time.second);
    write_byte(0);    // GMT offset
    write_byte(d->flags);
    write_byte(0);    // file unit size for an interleaved file
    write_byte(0);    // interleave gap size for an interleaved file
    write_both_endian_word(1); // volume sequence number
    write_byte((BYTE)identifier_size);
    switch (DirType)
    {
        case DOT_RECORD:
            write_byte(0);
            break;
        case DOT_DOT_RECORD:
            write_byte(1);
            break;
        case SUBDIRECTORY_RECORD:
            if (joliet)
                write_string_as_big_endian_unicode(d->joliet_name);
            else
                write_string(d->name_on_cd);
            break;
        case FILE_RECORD:
            if (joliet)
            {
                write_string_as_big_endian_unicode(d->joliet_name);
            }
            else
            {
                write_string(d->name_on_cd);
                if (d->extension_on_cd[0] != 0)
                {
                    write_byte('.');
                    write_string(d->extension_on_cd);
                }
                write_string(";1");
            }
            break;
    }
    if ((identifier_size & 1) == 0)
        write_byte(0);
}