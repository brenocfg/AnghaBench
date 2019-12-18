#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ar_archive_zip_uncomp {int initialized; int /*<<< orphan*/ * clear_state; int /*<<< orphan*/ * uncompress_data; } ;
struct TYPE_5__ {scalar_t__ method; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ entry; struct ar_archive_zip_uncomp uncomp; } ;
typedef  TYPE_2__ ar_archive_zip ;

/* Variables and functions */
 scalar_t__ METHOD_BZIP2 ; 
 scalar_t__ METHOD_DEFLATE ; 
 scalar_t__ METHOD_DEFLATE64 ; 
 scalar_t__ METHOD_LZMA ; 
 scalar_t__ METHOD_PPMD ; 
 int /*<<< orphan*/  memset (struct ar_archive_zip_uncomp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/ * zip_clear_uncompress_bzip2 ; 
 int /*<<< orphan*/ * zip_clear_uncompress_deflate ; 
 void* zip_clear_uncompress_deflate64 ; 
 int /*<<< orphan*/ * zip_clear_uncompress_lzma ; 
 int /*<<< orphan*/ * zip_clear_uncompress_ppmd ; 
 scalar_t__ zip_init_uncompress_bzip2 (struct ar_archive_zip_uncomp*) ; 
 scalar_t__ zip_init_uncompress_deflate (struct ar_archive_zip_uncomp*) ; 
 scalar_t__ zip_init_uncompress_deflate64 (struct ar_archive_zip_uncomp*,int) ; 
 scalar_t__ zip_init_uncompress_lzma (struct ar_archive_zip_uncomp*,int /*<<< orphan*/ ) ; 
 scalar_t__ zip_init_uncompress_ppmd (TYPE_2__*) ; 
 int /*<<< orphan*/ * zip_uncompress_data_bzip2 ; 
 int /*<<< orphan*/ * zip_uncompress_data_deflate ; 
 void* zip_uncompress_data_deflate64 ; 
 int /*<<< orphan*/ * zip_uncompress_data_lzma ; 
 int /*<<< orphan*/ * zip_uncompress_data_ppmd ; 

__attribute__((used)) static bool zip_init_uncompress(ar_archive_zip *zip)
{
    struct ar_archive_zip_uncomp *uncomp = &zip->uncomp;
    if (uncomp->initialized)
        return true;
    memset(uncomp, 0, sizeof(*uncomp));
    if (zip->entry.method == METHOD_DEFLATE) {
#ifdef HAVE_ZLIB
        if (zip_init_uncompress_deflate(uncomp)) {
            uncomp->uncompress_data = zip_uncompress_data_deflate;
            uncomp->clear_state = zip_clear_uncompress_deflate;
        }
#else
        if (zip_init_uncompress_deflate64(uncomp, false)) {
            uncomp->uncompress_data = zip_uncompress_data_deflate64;
            uncomp->clear_state = zip_clear_uncompress_deflate64;
        }
#endif
    }
    else if (zip->entry.method == METHOD_DEFLATE64) {
        if (zip_init_uncompress_deflate64(uncomp, true)) {
            uncomp->uncompress_data = zip_uncompress_data_deflate64;
            uncomp->clear_state = zip_clear_uncompress_deflate64;
        }
    }
    else if (zip->entry.method == METHOD_BZIP2) {
#ifdef HAVE_BZIP2
        if (zip_init_uncompress_bzip2(uncomp)) {
            uncomp->uncompress_data = zip_uncompress_data_bzip2;
            uncomp->clear_state = zip_clear_uncompress_bzip2;
        }
#else
        warn("BZIP2 support requires BZIP2 (define HAVE_BZIP2)");
#endif
    }
    else if (zip->entry.method == METHOD_LZMA) {
        if (zip_init_uncompress_lzma(uncomp, zip->entry.flags)) {
            uncomp->uncompress_data = zip_uncompress_data_lzma;
            uncomp->clear_state = zip_clear_uncompress_lzma;
        }
    }
    else if (zip->entry.method == METHOD_PPMD) {
        if (zip_init_uncompress_ppmd(zip)) {
            uncomp->uncompress_data = zip_uncompress_data_ppmd;
            uncomp->clear_state = zip_clear_uncompress_ppmd;
        }
    }
    else
        warn("Unsupported compression method %d", zip->entry.method);
    uncomp->initialized = uncomp->uncompress_data != NULL && uncomp->clear_state != NULL;
    return uncomp->initialized;
}