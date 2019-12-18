#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct target_file {char* target_name; char* source_name; struct target_file* next; } ;
struct target_dir_entry {char* case_name; struct target_dir_entry* next; struct target_dir_entry* child; struct target_file* head; } ;
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; } ;
struct TYPE_9__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_8__ {int level; char* orig_name; int /*<<< orphan*/ * first_record; int /*<<< orphan*/  joliet_size; int /*<<< orphan*/  size; int /*<<< orphan*/  date_and_time; } ;
typedef  TYPE_1__* PDIR_RECORD ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIRECTORY_TIMESTAMP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFileSizeEx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VERBOSE ; 
 int /*<<< orphan*/  compare_directory_order ; 
 int /*<<< orphan*/  convert_date_and_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__* end_source ; 
 int /*<<< orphan*/  error_exit (char*,char*,...) ; 
 int /*<<< orphan*/  get_cd_file_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* new_empty_dirrecord (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_filename_into_dirrecord (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*,...) ; 
 int /*<<< orphan*/ * sort_linked_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* source ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void
scan_specified_files(PDIR_RECORD d, struct target_dir_entry *dir)
{
    PDIR_RECORD new_d;
#ifdef _WIN32
    HANDLE open_file;
    LARGE_INTEGER file_size;
#else
    struct stat stbuf;
#endif
    struct target_file *file;
    struct target_dir_entry *child;

    d->first_record = NULL;

    for (file = dir->head; file; file = file->next)
    {
        if (strcmp(file->target_name, DIRECTORY_TIMESTAMP) == 0)
        {
#ifdef _WIN32
            if ((open_file = CreateFileA(file->source_name,
                                         GENERIC_READ,
                                         FILE_SHARE_READ,
                                         NULL,
                                         OPEN_EXISTING,
                                         FILE_ATTRIBUTE_NORMAL,
                                         NULL)) == INVALID_HANDLE_VALUE)
            {
                error_exit("Cannot open timestamp file '%s'\n", file->source_name);
            }

            if (!get_cd_file_time(open_file, &d->date_and_time))
            {
                error_exit("Cannot stat timestamp file '%s'\n", file->source_name);
            }
            CloseHandle(open_file);
#else
            if (stat(file->target_name, &stbuf) == -1)
            {
                error_exit("Cannot stat timestamp file '%s'\n", file->source_name);
            }
            convert_date_and_time(&d->date_and_time, &stbuf.st_ctime);
#endif
        }
        else
        {
            if (verbosity == VERBOSE)
            {
                printf("%d: file %s (from %s)\n",
                       d->level,
                       file->target_name,
                       file->source_name);
            }
            new_d = new_empty_dirrecord(d, FALSE);
            parse_filename_into_dirrecord(file->target_name, new_d, FALSE);
#ifdef _WIN32
            if ((open_file = CreateFileA(file->source_name,
                                         GENERIC_READ,
                                         FILE_SHARE_READ,
                                         NULL,
                                         OPEN_EXISTING,
                                         FILE_ATTRIBUTE_NORMAL,
                                         NULL)) == INVALID_HANDLE_VALUE)
            {
                error_exit("Cannot open file '%s'\n", file->source_name);
            }
            if (!get_cd_file_time(open_file, &new_d->date_and_time))
            {
                error_exit("Cannot stat file '%s'\n", file->source_name);
            }
            if (!GetFileSizeEx(open_file, &file_size))
            {
                error_exit("Cannot get file size of '%s'\n", file->source_name);
            }
            new_d->size = new_d->joliet_size = file_size.QuadPart;
            new_d->orig_name = file->source_name;
            CloseHandle(open_file);
#else
            if (stat(file->source_name, &stbuf) == -1)
            {
                error_exit("Cannot find '%s' (target '%s')\n",
                           file->source_name,
                           file->target_name);
            }
            convert_date_and_time(&new_d->date_and_time, &stbuf.st_mtime);
            new_d->size = new_d->joliet_size = stbuf.st_size;
            new_d->orig_name = file->source_name;
#endif
        }
    }

    for (child = dir->child; child; child = child->next)
    {
        if (verbosity == VERBOSE)
        {
            printf("%d: directory %s\n", d->level, child->case_name);
        }
        new_d = new_empty_dirrecord(d, TRUE);
        parse_filename_into_dirrecord(child->case_name, new_d, TRUE);
        scan_specified_files(new_d, child);
    }

    /* sort directory */
    d->first_record = sort_linked_list(d->first_record,
                                       0,
                                       compare_directory_order);
    source[0] = 0;
    end_source = source;
}