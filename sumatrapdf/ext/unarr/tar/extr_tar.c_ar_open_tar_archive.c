#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ar_stream ;
struct TYPE_4__ {int /*<<< orphan*/  checksum; } ;
struct TYPE_5__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ ar_archive_tar ;
typedef  int /*<<< orphan*/  ar_archive ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * ar_open_archive (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tar_close ; 
 int /*<<< orphan*/  tar_get_name ; 
 int /*<<< orphan*/  tar_parse_entry ; 
 int /*<<< orphan*/  tar_parse_header (TYPE_2__*) ; 
 int /*<<< orphan*/  tar_uncompress ; 

ar_archive *ar_open_tar_archive(ar_stream *stream)
{
    ar_archive *ar;
    ar_archive_tar *tar;

    if (!ar_seek(stream, 0, SEEK_SET))
        return NULL;

    ar = ar_open_archive(stream, sizeof(ar_archive_tar), tar_close, tar_parse_entry, tar_get_name, tar_uncompress, NULL, 0);
    if (!ar)
        return NULL;

    tar = (ar_archive_tar *)ar;
    if (!tar_parse_header(tar) || !tar->entry.checksum) {
        free(ar);
        return NULL;
    }

    return ar;
}