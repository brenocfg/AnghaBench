#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; scalar_t__ is_ustar; } ;
struct TYPE_6__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ ar_archive_tar ;
struct TYPE_7__ {int /*<<< orphan*/  stream; scalar_t__ entry_offset; } ;
typedef  TYPE_3__ ar_archive ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TAR_BLOCK_SIZE ; 
 char* ar_conv_dos_to_utf8 (char*) ; 
 scalar_t__ ar_is_valid_utf8 (char*) ; 
 int ar_read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ar_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 

const char *tar_get_name(ar_archive *ar)
{
    ar_archive_tar *tar = (ar_archive_tar *)ar;
    if (!tar->entry.name) {
        char *name;

        if (!ar_seek(ar->stream, ar->entry_offset, SEEK_SET))
            return NULL;

        name = malloc(100 + 1);
        if (!name || ar_read(ar->stream, name, 100) != 100) {
            free(name);
            ar_seek(ar->stream, ar->entry_offset + TAR_BLOCK_SIZE, SEEK_SET);
            return NULL;
        }
        name[100] = '\0';

        if (tar->entry.is_ustar) {
            char *prefixed = malloc(256 + 1);
            if (!prefixed || !ar_skip(ar->stream, 245) || ar_read(ar->stream, prefixed, 167) != 167) {
                free(name);
                free(prefixed);
                ar_seek(ar->stream, ar->entry_offset + TAR_BLOCK_SIZE, SEEK_SET);
                return NULL;
            }
            if (prefixed[0] != '\0') {
                prefixed[156] = '\0';
                strcat(prefixed, "/");
                strcat(prefixed, name);
                free(name);
                name = prefixed;
                prefixed = NULL;
            }
            free(prefixed);
        }
        else
            ar_skip(ar->stream, TAR_BLOCK_SIZE - 100);

        /* name could be in any encoding, assume UTF-8 or whatever (DOS) */
        if (ar_is_valid_utf8(name)) {
            tar->entry.name = name;
        }
        else {
            tar->entry.name = ar_conv_dos_to_utf8(name);
            free(name);
        }
        /* normalize path separators */
        if (tar->entry.name) {
            char *p = tar->entry.name;
            while ((p = strchr(p, '\\')) != NULL) {
                *p = '/';
            }
        }
    }
    return tar->entry.name;
}