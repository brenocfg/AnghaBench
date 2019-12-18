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
typedef  int /*<<< orphan*/  AnimatedImage ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int ReadAnimatedGIF(const char filename[], AnimatedImage* const image,
                           int dump_frames, const char dump_folder[]) {
  (void)filename;
  (void)image;
  (void)dump_frames;
  (void)dump_folder;
  fprintf(stderr, "GIF support not compiled. Please install the libgif-dev "
          "package before building.\n");
  return 0;
}