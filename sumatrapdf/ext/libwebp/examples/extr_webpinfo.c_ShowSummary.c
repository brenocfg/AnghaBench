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
struct TYPE_3__ {int num_frames_; int* chunk_counts_; int* anmf_subchunk_counts_; } ;
typedef  TYPE_1__ WebPInfo ;

/* Variables and functions */
 int CHUNK_ANMF ; 
 int CHUNK_TYPES ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void ShowSummary(const WebPInfo* const webp_info) {
  int i;
  printf("Summary:\n");
  printf("Number of frames: %d\n", webp_info->num_frames_);
  printf("Chunk type  :  VP8 VP8L VP8X ALPH ANIM ANMF(VP8 /VP8L/ALPH) ICCP "
      "EXIF  XMP\n");
  printf("Chunk counts: ");
  for (i = 0; i < CHUNK_TYPES; ++i) {
    printf("%4d ", webp_info->chunk_counts_[i]);
    if (i == CHUNK_ANMF) {
      printf("%4d %4d %4d  ",
             webp_info->anmf_subchunk_counts_[0],
             webp_info->anmf_subchunk_counts_[1],
             webp_info->anmf_subchunk_counts_[2]);
    }
  }
  printf("\n");
}