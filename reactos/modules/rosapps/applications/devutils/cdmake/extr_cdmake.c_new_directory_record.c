#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; scalar_t__ d_type; } ;
struct TYPE_8__ {TYPE_1__* next_in_memory; } ;
struct TYPE_7__ {struct TYPE_7__* first_record; struct TYPE_7__* next_in_directory; int /*<<< orphan*/  joliet_size; int /*<<< orphan*/  size; int /*<<< orphan*/  flags; int /*<<< orphan*/  date_and_time; struct TYPE_7__* parent; struct TYPE_7__* next_in_memory; } ;
typedef  TYPE_1__* PDIR_RECORD ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  HIDDEN_FLAG ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  convert_date_and_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_exit (char*) ; 
 int /*<<< orphan*/  parse_filename_into_dirrecord (char*,TYPE_1__*,int) ; 
 TYPE_2__ root ; 

PDIR_RECORD
new_directory_record(struct dirent *entry,
                     struct stat *stbuf,
                     PDIR_RECORD parent)
{
    PDIR_RECORD d;

    d = calloc(1, sizeof(*d));
    if (d == NULL)
        error_exit("Insufficient memory");
    d->next_in_memory = root.next_in_memory;
    root.next_in_memory = d;

    /* I need the parent set before calling parse_filename_into_dirrecord(),
    because that functions checks for duplicate file names*/
    d->parent = parent;
#ifdef HAVE_D_TYPE
    parse_filename_into_dirrecord(entry->d_name, d, entry->d_type == DT_DIR);
#else
    parse_filename_into_dirrecord(entry->d_name, d, S_ISDIR(stbuf->st_mode));
#endif

    convert_date_and_time(&d->date_and_time, &stbuf->st_mtime);
    d->flags |= entry->d_name[0] == '.' ? HIDDEN_FLAG : 0;
    d->size = d->joliet_size = stbuf->st_size;
    d->next_in_directory = parent->first_record;
    parent->first_record = d;
    return d;
}