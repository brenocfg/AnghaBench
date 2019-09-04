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
 int LIBAVCODEC_VERSION_MAJOR ; 
 int LIBAVCODEC_VERSION_MICRO ; 
 int LIBAVCODEC_VERSION_MINOR ; 
 int LIBAVFORMAT_VERSION_MAJOR ; 
 int LIBAVFORMAT_VERSION_MICRO ; 
 int LIBAVFORMAT_VERSION_MINOR ; 
 int LIBAVUTIL_VERSION_MAJOR ; 
 int LIBAVUTIL_VERSION_MICRO ; 
 int LIBAVUTIL_VERSION_MINOR ; 
 char* SCRCPY_VERSION ; 
 int SDL_MAJOR_VERSION ; 
 int SDL_MINOR_VERSION ; 
 int SDL_PATCHLEVEL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_version(void) {
    fprintf(stderr, "scrcpy %s\n\n", SCRCPY_VERSION);

    fprintf(stderr, "dependencies:\n");
    fprintf(stderr, " - SDL %d.%d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION,
                                         SDL_PATCHLEVEL);
    fprintf(stderr, " - libavcodec %d.%d.%d\n", LIBAVCODEC_VERSION_MAJOR,
                                                LIBAVCODEC_VERSION_MINOR,
                                                LIBAVCODEC_VERSION_MICRO);
    fprintf(stderr, " - libavformat %d.%d.%d\n", LIBAVFORMAT_VERSION_MAJOR,
                                                 LIBAVFORMAT_VERSION_MINOR,
                                                 LIBAVFORMAT_VERSION_MICRO);
    fprintf(stderr, " - libavutil %d.%d.%d\n", LIBAVUTIL_VERSION_MAJOR,
                                               LIBAVUTIL_VERSION_MINOR,
                                               LIBAVUTIL_VERSION_MICRO);
}