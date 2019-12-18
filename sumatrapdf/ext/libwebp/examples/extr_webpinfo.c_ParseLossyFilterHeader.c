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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  WebPInfoStatus ;
typedef  int /*<<< orphan*/  WebPInfo ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BITS (int,int) ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static WebPInfoStatus ParseLossyFilterHeader(const WebPInfo* const webp_info,
                                             const uint8_t* const data,
                                             size_t data_size,
                                             uint64_t* const bit_pos) {
  int simple_filter, level, sharpness, use_lf_delta;
  GET_BITS(simple_filter, 1);
  GET_BITS(level, 6);
  GET_BITS(sharpness, 3);
  GET_BITS(use_lf_delta, 1);
  printf("  Simple filter:    %d\n", simple_filter);
  printf("  Level:            %d\n", level);
  printf("  Sharpness:        %d\n", sharpness);
  printf("  Use lf delta:     %d\n", use_lf_delta);
  if (use_lf_delta) {
    int update;
    GET_BITS(update, 1);
    printf("  Update lf delta:  %d\n", update);
    if (update) {
      int i;
      for (i = 0; i < 4 + 4; ++i) {
        int temp;
        GET_BITS(temp, 1);
        if (temp) GET_BITS(temp, 7);
      }
    }
  }
  return WEBP_INFO_OK;
}