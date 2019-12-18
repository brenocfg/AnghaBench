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
typedef  int /*<<< orphan*/  ar_stream ;
typedef  int /*<<< orphan*/  ar_archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ar_open_7z_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ar_open_rar_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ar_open_tar_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ar_open_zip_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

ar_archive *ar_open_any_archive(ar_stream *stream, const char *fileext)
{
    ar_archive *ar = ar_open_rar_archive(stream);
    if (!ar)
        ar = ar_open_zip_archive(stream, fileext && (strcmp(fileext, ".xps") == 0 || strcmp(fileext, ".epub") == 0));
    if (!ar)
        ar = ar_open_7z_archive(stream);
    if (!ar)
        ar = ar_open_tar_archive(stream);
    return ar;
}