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
typedef  int ag_compression_type ;

/* Variables and functions */
#define  AG_COMPRESS 132 
#define  AG_GZIP 131 
#define  AG_NO_COMPRESSION 130 
#define  AG_XZ 129 
#define  AG_ZIP 128 
 void* decompress_lzma (void const*,int const,char const*,int*) ; 
 void* decompress_lzw (void const*,int const,char const*,int*) ; 
 void* decompress_zip (void const*,int const,char const*,int*) ; 
 void* decompress_zlib (void const*,int const,char const*,int*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 

void *decompress(const ag_compression_type zip_type, const void *buf, const int buf_len,
                 const char *dir_full_path, int *new_buf_len) {
    switch (zip_type) {
#ifdef HAVE_ZLIB_H
        case AG_GZIP:
            return decompress_zlib(buf, buf_len, dir_full_path, new_buf_len);
#endif
        case AG_COMPRESS:
            return decompress_lzw(buf, buf_len, dir_full_path, new_buf_len);
        case AG_ZIP:
            return decompress_zip(buf, buf_len, dir_full_path, new_buf_len);
#ifdef HAVE_LZMA_H
        case AG_XZ:
            return decompress_lzma(buf, buf_len, dir_full_path, new_buf_len);
#endif
        case AG_NO_COMPRESSION:
            log_err("File %s is not compressed", dir_full_path);
            break;
        default:
            log_err("Unsupported compression type: %d", zip_type);
    }

    *new_buf_len = 0;
    return NULL;
}