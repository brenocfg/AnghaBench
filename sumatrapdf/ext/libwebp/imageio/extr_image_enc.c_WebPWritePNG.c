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
typedef  int /*<<< orphan*/  WebPDecBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int WebPWritePNG(FILE* fout, const WebPDecBuffer* const buffer) {
  if (fout == NULL || buffer == NULL) return 0;

  fprintf(stderr, "PNG support not compiled. Please install the libpng "
          "development package before building.\n");
  fprintf(stderr, "You can run with -ppm flag to decode in PPM format.\n");
  return 0;
}