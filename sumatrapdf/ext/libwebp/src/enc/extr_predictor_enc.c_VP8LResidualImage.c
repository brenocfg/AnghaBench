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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  histo ;

/* Variables and functions */
 int ARGB_BLACK ; 
 int /*<<< orphan*/  CopyImageWithPrediction (int,int,int,int* const,int* const,int* const,int,int const,int,int) ; 
 int GetBestPredictorForTile (int,int,int,int,int,int**,int* const,int* const,int const,int,int,int* const) ; 
 int VP8LNearLosslessBits (int) ; 
 int VP8LSubSampleSize (int,int) ; 
 int kPredLowEffort ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

void VP8LResidualImage(int width, int height, int bits, int low_effort,
                       uint32_t* const argb, uint32_t* const argb_scratch,
                       uint32_t* const image, int near_lossless_quality,
                       int exact, int used_subtract_green) {
  const int tiles_per_row = VP8LSubSampleSize(width, bits);
  const int tiles_per_col = VP8LSubSampleSize(height, bits);
  int tile_y;
  int histo[4][256];
  const int max_quantization = 1 << VP8LNearLosslessBits(near_lossless_quality);
  if (low_effort) {
    int i;
    for (i = 0; i < tiles_per_row * tiles_per_col; ++i) {
      image[i] = ARGB_BLACK | (kPredLowEffort << 8);
    }
  } else {
    memset(histo, 0, sizeof(histo));
    for (tile_y = 0; tile_y < tiles_per_col; ++tile_y) {
      int tile_x;
      for (tile_x = 0; tile_x < tiles_per_row; ++tile_x) {
        const int pred = GetBestPredictorForTile(width, height, tile_x, tile_y,
            bits, histo, argb_scratch, argb, max_quantization, exact,
            used_subtract_green, image);
        image[tile_y * tiles_per_row + tile_x] = ARGB_BLACK | (pred << 8);
      }
    }
  }

  CopyImageWithPrediction(width, height, bits, image, argb_scratch, argb,
                          low_effort, max_quantization, exact,
                          used_subtract_green);
}