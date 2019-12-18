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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  histo_stack_1 ;

/* Variables and functions */
 int GetMin (int const,int) ; 
 int /*<<< orphan*/  GetResidual (int,int,int*,int*,int /*<<< orphan*/ * const,int,int const,int const,int const,int,int,int,int*) ; 
 float MAX_DIFF_COST ; 
 int MAX_TRANSFORM_BITS ; 
 int /*<<< orphan*/  MaxDiffsForRow (int const,int,int const* const,int /*<<< orphan*/ * const,int) ; 
 float PredictionCostSpatialHistogram (int const**,int const**) ; 
 int /*<<< orphan*/  UpdateHisto (int**,int) ; 
 int VP8LSubSampleSize (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kSpatialPredictorBias ; 
 int /*<<< orphan*/  memcpy (int*,int const* const,int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int GetBestPredictorForTile(int width, int height,
                                   int tile_x, int tile_y, int bits,
                                   int accumulated[4][256],
                                   uint32_t* const argb_scratch,
                                   const uint32_t* const argb,
                                   int max_quantization,
                                   int exact, int used_subtract_green,
                                   const uint32_t* const modes) {
  const int kNumPredModes = 14;
  const int start_x = tile_x << bits;
  const int start_y = tile_y << bits;
  const int tile_size = 1 << bits;
  const int max_y = GetMin(tile_size, height - start_y);
  const int max_x = GetMin(tile_size, width - start_x);
  // Whether there exist columns just outside the tile.
  const int have_left = (start_x > 0);
  // Position and size of the strip covering the tile and adjacent columns if
  // they exist.
  const int context_start_x = start_x - have_left;
#if (WEBP_NEAR_LOSSLESS == 1)
  const int context_width = max_x + have_left + (max_x < width - start_x);
#endif
  const int tiles_per_row = VP8LSubSampleSize(width, bits);
  // Prediction modes of the left and above neighbor tiles.
  const int left_mode = (tile_x > 0) ?
      (modes[tile_y * tiles_per_row + tile_x - 1] >> 8) & 0xff : 0xff;
  const int above_mode = (tile_y > 0) ?
      (modes[(tile_y - 1) * tiles_per_row + tile_x] >> 8) & 0xff : 0xff;
  // The width of upper_row and current_row is one pixel larger than image width
  // to allow the top right pixel to point to the leftmost pixel of the next row
  // when at the right edge.
  uint32_t* upper_row = argb_scratch;
  uint32_t* current_row = upper_row + width + 1;
  uint8_t* const max_diffs = (uint8_t*)(current_row + width + 1);
  float best_diff = MAX_DIFF_COST;
  int best_mode = 0;
  int mode;
  int histo_stack_1[4][256];
  int histo_stack_2[4][256];
  // Need pointers to be able to swap arrays.
  int (*histo_argb)[256] = histo_stack_1;
  int (*best_histo)[256] = histo_stack_2;
  int i, j;
  uint32_t residuals[1 << MAX_TRANSFORM_BITS];
  assert(bits <= MAX_TRANSFORM_BITS);
  assert(max_x <= (1 << MAX_TRANSFORM_BITS));

  for (mode = 0; mode < kNumPredModes; ++mode) {
    float cur_diff;
    int relative_y;
    memset(histo_argb, 0, sizeof(histo_stack_1));
    if (start_y > 0) {
      // Read the row above the tile which will become the first upper_row.
      // Include a pixel to the left if it exists; include a pixel to the right
      // in all cases (wrapping to the leftmost pixel of the next row if it does
      // not exist).
      memcpy(current_row + context_start_x,
             argb + (start_y - 1) * width + context_start_x,
             sizeof(*argb) * (max_x + have_left + 1));
    }
    for (relative_y = 0; relative_y < max_y; ++relative_y) {
      const int y = start_y + relative_y;
      int relative_x;
      uint32_t* tmp = upper_row;
      upper_row = current_row;
      current_row = tmp;
      // Read current_row. Include a pixel to the left if it exists; include a
      // pixel to the right in all cases except at the bottom right corner of
      // the image (wrapping to the leftmost pixel of the next row if it does
      // not exist in the current row).
      memcpy(current_row + context_start_x,
             argb + y * width + context_start_x,
             sizeof(*argb) * (max_x + have_left + (y + 1 < height)));
#if (WEBP_NEAR_LOSSLESS == 1)
      if (max_quantization > 1 && y >= 1 && y + 1 < height) {
        MaxDiffsForRow(context_width, width, argb + y * width + context_start_x,
                       max_diffs + context_start_x, used_subtract_green);
      }
#endif

      GetResidual(width, height, upper_row, current_row, max_diffs, mode,
                  start_x, start_x + max_x, y, max_quantization, exact,
                  used_subtract_green, residuals);
      for (relative_x = 0; relative_x < max_x; ++relative_x) {
        UpdateHisto(histo_argb, residuals[relative_x]);
      }
    }
    cur_diff = PredictionCostSpatialHistogram(
        (const int (*)[256])accumulated, (const int (*)[256])histo_argb);
    // Favor keeping the areas locally similar.
    if (mode == left_mode) cur_diff -= kSpatialPredictorBias;
    if (mode == above_mode) cur_diff -= kSpatialPredictorBias;

    if (cur_diff < best_diff) {
      int (*tmp)[256] = histo_argb;
      histo_argb = best_histo;
      best_histo = tmp;
      best_diff = cur_diff;
      best_mode = mode;
    }
  }

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 256; j++) {
      accumulated[i][j] += best_histo[i][j];
    }
  }

  return best_mode;
}