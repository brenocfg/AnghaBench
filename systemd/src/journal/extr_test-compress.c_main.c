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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  huge ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int EXIT_TEST_SKIP ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  OBJECT_COMPRESSED_LZ4 ; 
 int /*<<< orphan*/  OBJECT_COMPRESSED_XZ ; 
 int /*<<< orphan*/  char_array_0 (char*) ; 
 int /*<<< orphan*/  compress_blob_lz4 ; 
 int /*<<< orphan*/  compress_blob_xz ; 
 int /*<<< orphan*/  compress_stream_lz4 ; 
 int /*<<< orphan*/  compress_stream_xz ; 
 int /*<<< orphan*/  decompress_blob_lz4 ; 
 int /*<<< orphan*/  decompress_blob_xz ; 
 int /*<<< orphan*/  decompress_startswith_lz4 ; 
 int /*<<< orphan*/  decompress_startswith_xz ; 
 int /*<<< orphan*/  decompress_stream_lz4 ; 
 int /*<<< orphan*/  decompress_stream_xz ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  random_bytes (char*,int) ; 
 int /*<<< orphan*/  test_compress_decompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  test_compress_stream (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  test_decompress_startswith (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  test_decompress_startswith_short (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_lz4_decompress_partial () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
#if HAVE_XZ || HAVE_LZ4
        const char text[] =
                "text\0foofoofoofoo AAAA aaaaaaaaa ghost busters barbarbar FFF"
                "foofoofoofoo AAAA aaaaaaaaa ghost busters barbarbar FFF";

        /* The file to test compression on can be specified as the first argument */
        const char *srcfile = argc > 1 ? argv[1] : argv[0];

        char data[512] = "random\0";

        char huge[4096*1024];
        memset(huge, 'x', sizeof(huge));
        memcpy(huge, "HUGE=", 5);
        char_array_0(huge);

        test_setup_logging(LOG_DEBUG);

        random_bytes(data + 7, sizeof(data) - 7);

#if HAVE_XZ
        test_compress_decompress(OBJECT_COMPRESSED_XZ, compress_blob_xz, decompress_blob_xz,
                                 text, sizeof(text), false);
        test_compress_decompress(OBJECT_COMPRESSED_XZ, compress_blob_xz, decompress_blob_xz,
                                 data, sizeof(data), true);

        test_decompress_startswith(OBJECT_COMPRESSED_XZ,
                                   compress_blob_xz, decompress_startswith_xz,
                                   text, sizeof(text), false);
        test_decompress_startswith(OBJECT_COMPRESSED_XZ,
                                   compress_blob_xz, decompress_startswith_xz,
                                   data, sizeof(data), true);
        test_decompress_startswith(OBJECT_COMPRESSED_XZ,
                                   compress_blob_xz, decompress_startswith_xz,
                                   huge, sizeof(huge), true);

        test_compress_stream(OBJECT_COMPRESSED_XZ, "xzcat",
                             compress_stream_xz, decompress_stream_xz, srcfile);

        test_decompress_startswith_short(OBJECT_COMPRESSED_XZ, compress_blob_xz, decompress_startswith_xz);

#else
        log_info("/* XZ test skipped */");
#endif

#if HAVE_LZ4
        test_compress_decompress(OBJECT_COMPRESSED_LZ4, compress_blob_lz4, decompress_blob_lz4,
                                 text, sizeof(text), false);
        test_compress_decompress(OBJECT_COMPRESSED_LZ4, compress_blob_lz4, decompress_blob_lz4,
                                 data, sizeof(data), true);

        test_decompress_startswith(OBJECT_COMPRESSED_LZ4,
                                   compress_blob_lz4, decompress_startswith_lz4,
                                   text, sizeof(text), false);
        test_decompress_startswith(OBJECT_COMPRESSED_LZ4,
                                   compress_blob_lz4, decompress_startswith_lz4,
                                   data, sizeof(data), true);
        test_decompress_startswith(OBJECT_COMPRESSED_LZ4,
                                   compress_blob_lz4, decompress_startswith_lz4,
                                   huge, sizeof(huge), true);

        test_compress_stream(OBJECT_COMPRESSED_LZ4, "lz4cat",
                             compress_stream_lz4, decompress_stream_lz4, srcfile);

        test_lz4_decompress_partial();

        test_decompress_startswith_short(OBJECT_COMPRESSED_LZ4, compress_blob_lz4, decompress_startswith_lz4);

#else
        log_info("/* LZ4 test skipped */");
#endif

        return 0;
#else
        log_info("/* XZ and LZ4 tests skipped */");
        return EXIT_TEST_SKIP;
#endif
}