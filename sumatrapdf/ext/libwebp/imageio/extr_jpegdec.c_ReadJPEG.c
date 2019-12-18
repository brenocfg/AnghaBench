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
typedef  int /*<<< orphan*/  uint8_t ;
struct WebPPicture {int dummy; } ;
struct Metadata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int ReadJPEG(const uint8_t* const data, size_t data_size,
             struct WebPPicture* const pic, int keep_alpha,
             struct Metadata* const metadata) {
  (void)data;
  (void)data_size;
  (void)pic;
  (void)keep_alpha;
  (void)metadata;
  fprintf(stderr, "JPEG support not compiled. Please install the libjpeg "
          "development package before building.\n");
  return 0;
}