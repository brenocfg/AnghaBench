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
struct TYPE_4__ {char* name_on_cd; char* name; scalar_t__* extension; char* extension_on_cd; scalar_t__* joliet_name; scalar_t__ flags; } ;
typedef  TYPE_1__* PDIR_RECORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DIRECTORY_FLAG ; 
 scalar_t__ MAX_EXTENSION_LENGTH ; 
 scalar_t__ cdname_exists (TYPE_1__*) ; 
 void* check_for_punctuation (char const,char const*) ; 
 int /*<<< orphan*/  error_exit (char*,...) ; 
 scalar_t__ joliet ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void parse_filename_into_dirrecord(const char* filename, PDIR_RECORD d, BOOL dir)
{
    const char *s = filename;
    char *t = d->name_on_cd;
    char *n = d->name;
    int joliet_length;
    int filename_counter;
    filename_counter = 1;
    while (*s != 0)
    {
        if (*s == '.')
        {
            s++;
            break;
        }

        if ((size_t)(t-d->name_on_cd) < sizeof(d->name_on_cd)-1)
            *t++ = check_for_punctuation(*s, filename);
        else if (!joliet)
            error_exit("'%s' is not ISO-9660, aborting...", filename);

        if ((size_t)(n-d->name) < sizeof(d->name)-1)
            *n++ = *s;
        else if (!joliet)
            error_exit("'%s' is not ISO-9660, aborting...", filename);
        s++;
    }
    // Check for extension length
    if (!joliet && strlen(s) > MAX_EXTENSION_LENGTH)
    {
        error_exit("'%s' has too long extension, aborting...", filename);
    }
    *t = 0;
    strcpy(d->extension, s);
    t = d->extension_on_cd;
    while (*s != 0)
    {
        if ((size_t)(t-d->extension_on_cd) < sizeof(d->extension_on_cd)-1)
            *t++ = check_for_punctuation(*s, filename);
        else if (!joliet)
            error_exit("'%s' is not ISO-9660, aborting...", filename);
        s++;
    }
    *t = 0;
    *n = 0;

    if (dir)
    {
        if (d->extension[0] != 0)
        {
            if (!joliet)
                error_exit("Directory with extension '%s'", filename);
        }
        d->flags = DIRECTORY_FLAG;
    } else
    {
        d->flags = 0;
    }

    filename_counter = 1;
    while (cdname_exists(d))
    {
        // the file name must be at least 8 chars long
        if (strlen(d->name_on_cd)<8)
            error_exit("'%s' is a duplicate file name, aborting...", filename);

        if ((d->name_on_cd[8] == '.') && (strlen(d->name_on_cd) < 13))
            error_exit("'%s' is a duplicate file name, aborting...", filename);

        // max 255 times for equal short filename
        if (filename_counter>255)
            error_exit("'%s' is a duplicate file name, aborting...", filename);

        d->name_on_cd[8] = '~';
        memset(&d->name_on_cd[9],0,5);
        sprintf(&d->name_on_cd[9],"%d",filename_counter);
        filename_counter++;
    }

    if (joliet)
    {
        joliet_length = strlen(filename);
        if (joliet_length > 64)
            error_exit("'%s' is not Joliet, aborting...", filename);
        d->joliet_name = malloc(joliet_length + 1);
        if (d->joliet_name == NULL)
            error_exit("Insufficient memory");
        strcpy(d->joliet_name, filename);
    }
}