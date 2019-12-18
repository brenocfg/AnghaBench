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
typedef  int /*<<< orphan*/  ag_compression_type ;

/* Variables and functions */
 int /*<<< orphan*/  AG_COMPRESS ; 
 int /*<<< orphan*/  AG_GZIP ; 
 int /*<<< orphan*/  AG_NO_COMPRESSION ; 
 int /*<<< orphan*/  AG_XZ ; 
 int /*<<< orphan*/  AG_ZIP ; 
 int /*<<< orphan*/  LZMA_HEADER_SOMETIMES ; 
 int /*<<< orphan*/  XZ_HEADER_MAGIC ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char const*,int) ; 

ag_compression_type is_zipped(const void *buf, const int buf_len) {
    /* Zip magic numbers
     * compressed file: { 0x1F, 0x9B }
     * http://en.wikipedia.org/wiki/Compress
     * 
     * gzip file:       { 0x1F, 0x8B }
     * http://www.gzip.org/zlib/rfc-gzip.html#file-format
     *
     * zip file:        { 0x50, 0x4B, 0x03, 0x04 }
     * http://www.pkware.com/documents/casestudies/APPNOTE.TXT (Section 4.3)
     */

    const unsigned char *buf_c = buf;

    if (buf_len == 0)
        return AG_NO_COMPRESSION;

    /* Check for gzip & compress */
    if (buf_len >= 2) {
        if (buf_c[0] == 0x1F) {
            if (buf_c[1] == 0x8B) {
#ifdef HAVE_ZLIB_H
                log_debug("Found gzip-based stream");
                return AG_GZIP;
#endif
            } else if (buf_c[1] == 0x9B) {
                log_debug("Found compress-based stream");
                return AG_COMPRESS;
            }
        }
    }

    /* Check for zip */
    if (buf_len >= 4) {
        if (buf_c[0] == 0x50 && buf_c[1] == 0x4B && buf_c[2] == 0x03 && buf_c[3] == 0x04) {
            log_debug("Found zip-based stream");
            return AG_ZIP;
        }
    }

#ifdef HAVE_LZMA_H
    if (buf_len >= 6) {
        if (memcmp(XZ_HEADER_MAGIC, buf_c, 6) == 0) {
            log_debug("Found xz based stream");
            return AG_XZ;
        }
    }

    /* LZMA doesn't really have a header: http://www.mail-archive.com/xz-devel@tukaani.org/msg00003.html */
    if (buf_len >= 3) {
        if (memcmp(LZMA_HEADER_SOMETIMES, buf_c, 3) == 0) {
            log_debug("Found lzma-based stream");
            return AG_XZ;
        }
    }
#endif

    return AG_NO_COMPRESSION;
}