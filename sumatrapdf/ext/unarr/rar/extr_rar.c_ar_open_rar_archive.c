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
typedef  int /*<<< orphan*/  signature ;
typedef  int /*<<< orphan*/  ar_stream ;
typedef  int /*<<< orphan*/  ar_archive_rar ;
typedef  int /*<<< orphan*/  ar_archive ;

/* Variables and functions */
 int FILE_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * ar_open_archive (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ar_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ar_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  rar_close ; 
 int /*<<< orphan*/  rar_get_name ; 
 int /*<<< orphan*/  rar_parse_entry ; 
 int /*<<< orphan*/  rar_uncompress ; 
 int /*<<< orphan*/  warn (char*) ; 

ar_archive *ar_open_rar_archive(ar_stream *stream)
{
    char signature[FILE_SIGNATURE_SIZE];
    if (!ar_seek(stream, 0, SEEK_SET))
        return NULL;
    if (ar_read(stream, signature, sizeof(signature)) != sizeof(signature))
        return NULL;
    if (memcmp(signature, "Rar!\x1A\x07\x00", sizeof(signature)) != 0) {
        if (memcmp(signature, "Rar!\x1A\x07\x01", sizeof(signature)) == 0)
            warn("RAR 5 format isn't supported");
        else if (memcmp(signature, "RE~^", 4) == 0)
            warn("Ancient RAR format isn't supported");
        else if (memcmp(signature, "MZ", 2) == 0 || memcmp(signature, "\x7F\x45LF", 4) == 0)
            warn("SFX archives aren't supported");
        return NULL;
    }

    return ar_open_archive(stream, sizeof(ar_archive_rar), rar_close, rar_parse_entry, rar_get_name, rar_uncompress, NULL, FILE_SIGNATURE_SIZE);
}