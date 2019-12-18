#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* extra_info; int width; int height; int extra_info_type; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void PrintMapInfo(const WebPPicture* const pic) {
  if (pic->extra_info != NULL) {
    const int mb_w = (pic->width + 15) / 16;
    const int mb_h = (pic->height + 15) / 16;
    const int type = pic->extra_info_type;
    int x, y;
    for (y = 0; y < mb_h; ++y) {
      for (x = 0; x < mb_w; ++x) {
        const int c = pic->extra_info[x + y * mb_w];
        if (type == 1) {   // intra4/intra16
          fprintf(stderr, "%c", "+."[c]);
        } else if (type == 2) {    // segments
          fprintf(stderr, "%c", ".-*X"[c]);
        } else if (type == 3) {    // quantizers
          fprintf(stderr, "%.2d ", c);
        } else if (type == 6 || type == 7) {
          fprintf(stderr, "%3d ", c);
        } else {
          fprintf(stderr, "0x%.2x ", c);
        }
      }
      fprintf(stderr, "\n");
    }
  }
}