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

/* Variables and functions */
 scalar_t__ IMPORT_COMPRESS_BZIP2 ; 
 scalar_t__ IMPORT_COMPRESS_GZIP ; 
 scalar_t__ IMPORT_COMPRESS_UNCOMPRESSED ; 
 scalar_t__ IMPORT_COMPRESS_UNKNOWN ; 
 scalar_t__ IMPORT_COMPRESS_XZ ; 
 scalar_t__ arg_compress ; 
 scalar_t__ endswith (char const*,char*) ; 

__attribute__((used)) static void determine_compression_from_filename(const char *p) {

        if (arg_compress != IMPORT_COMPRESS_UNKNOWN)
                return;

        if (!p) {
                arg_compress = IMPORT_COMPRESS_UNCOMPRESSED;
                return;
        }

        if (endswith(p, ".xz"))
                arg_compress = IMPORT_COMPRESS_XZ;
        else if (endswith(p, ".gz"))
                arg_compress = IMPORT_COMPRESS_GZIP;
        else if (endswith(p, ".bz2"))
                arg_compress = IMPORT_COMPRESS_BZIP2;
        else
                arg_compress = IMPORT_COMPRESS_UNCOMPRESSED;
}