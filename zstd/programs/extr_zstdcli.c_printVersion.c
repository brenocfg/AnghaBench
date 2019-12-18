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
 int /*<<< orphan*/  DISPLAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 scalar_t__ PLATFORM_POSIX_VERSION ; 
 int /*<<< orphan*/  WELCOME_MESSAGE ; 
 long ZSTD_LEGACY_SUPPORT ; 
 scalar_t__ _POSIX_C_SOURCE ; 
 scalar_t__ _POSIX_VERSION ; 

__attribute__((used)) static void printVersion(void)
{
    DISPLAY(WELCOME_MESSAGE);
    /* format support */
    DISPLAYLEVEL(3, "*** supports: zstd");
#if defined(ZSTD_LEGACY_SUPPORT) && (ZSTD_LEGACY_SUPPORT>0) && (ZSTD_LEGACY_SUPPORT<8)
    DISPLAYLEVEL(3, ", zstd legacy v0.%d+", ZSTD_LEGACY_SUPPORT);
#endif
#ifdef ZSTD_GZCOMPRESS
    DISPLAYLEVEL(3, ", gzip");
#endif
#ifdef ZSTD_LZ4COMPRESS
    DISPLAYLEVEL(3, ", lz4");
#endif
#ifdef ZSTD_LZMACOMPRESS
    DISPLAYLEVEL(3, ", lzma, xz ");
#endif
    DISPLAYLEVEL(3, "\n");
    /* posix support */
#ifdef _POSIX_C_SOURCE
    DISPLAYLEVEL(4, "_POSIX_C_SOURCE defined: %ldL\n", (long) _POSIX_C_SOURCE);
#endif
#ifdef _POSIX_VERSION
    DISPLAYLEVEL(4, "_POSIX_VERSION defined: %ldL \n", (long) _POSIX_VERSION);
#endif
#ifdef PLATFORM_POSIX_VERSION
    DISPLAYLEVEL(4, "PLATFORM_POSIX_VERSION defined: %ldL\n", (long) PLATFORM_POSIX_VERSION);
#endif
}