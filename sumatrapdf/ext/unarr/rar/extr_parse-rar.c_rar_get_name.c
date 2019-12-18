#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct rar_header {int flags; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_6__ {char* name; scalar_t__ header_size; } ;
struct TYPE_7__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ ar_archive_rar ;
struct TYPE_8__ {scalar_t__ entry_offset; int /*<<< orphan*/  stream; } ;
typedef  TYPE_3__ ar_archive ;

/* Variables and functions */
 int LHD_LARGE ; 
 int LHD_UNICODE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* ar_conv_dos_to_utf8 (char*) ; 
 int ar_read (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ar_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* rar_conv_unicode_to_utf8 (char*,int) ; 
 int /*<<< orphan*/  rar_parse_header (TYPE_3__*,struct rar_header*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int uint16le (unsigned char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

const char *rar_get_name(ar_archive *ar)
{
    ar_archive_rar *rar = (ar_archive_rar *)ar;
    if (!rar->entry.name) {
        unsigned char data[21];
        uint16_t namelen;
        char *name;

        struct rar_header header;
        if (!ar_seek(ar->stream, ar->entry_offset, SEEK_SET))
            return NULL;
        if (!rar_parse_header(ar, &header))
            return NULL;
        if (ar_read(ar->stream, data, sizeof(data)) != sizeof(data))
            return NULL;
        if ((header.flags & LHD_LARGE) && !ar_skip(ar->stream, 8))
            return NULL;

        namelen = uint16le(data + 15);
        name = malloc(namelen + 1);
        if (!name || ar_read(ar->stream, name, namelen) != namelen) {
            free(name);
            return NULL;
        }
        name[namelen] = '\0';

        if (!(header.flags & LHD_UNICODE)) {
            rar->entry.name = ar_conv_dos_to_utf8(name);
            free(name);
        }
        else if (namelen == strlen(name)) {
            rar->entry.name = name;
        }
        else {
            rar->entry.name = rar_conv_unicode_to_utf8(name, namelen);
            free(name);
        }
        /* normalize path separators */
        if (rar->entry.name) {
            char *p = rar->entry.name;
            while ((p = strchr(p, '\\')) != NULL) {
                *p = '/';
            }
        }

        if (!ar_seek(ar->stream, ar->entry_offset + rar->entry.header_size, SEEK_SET))
            warn("Couldn't seek back to the end of the entry header");
    }
    return rar->entry.name;
}