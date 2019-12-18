#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  rescaler_t ;
typedef  int /*<<< orphan*/  WebPRescaler ;
struct TYPE_5__ {int /*<<< orphan*/ * rescaler; int /*<<< orphan*/ * rescaler_memory; int /*<<< orphan*/  status_; } ;
typedef  TYPE_1__ VP8LDecoder ;
struct TYPE_6__ {int mb_w; int scaled_width; int mb_h; int scaled_height; } ;
typedef  TYPE_2__ VP8Io ;

/* Variables and functions */
 int /*<<< orphan*/  VP8_STATUS_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  WebPRescalerInit (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 scalar_t__ WebPSafeMalloc (int const,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AllocateAndInitRescaler(VP8LDecoder* const dec, VP8Io* const io) {
  const int num_channels = 4;
  const int in_width = io->mb_w;
  const int out_width = io->scaled_width;
  const int in_height = io->mb_h;
  const int out_height = io->scaled_height;
  const uint64_t work_size = 2 * num_channels * (uint64_t)out_width;
  rescaler_t* work;        // Rescaler work area.
  const uint64_t scaled_data_size = (uint64_t)out_width;
  uint32_t* scaled_data;  // Temporary storage for scaled BGRA data.
  const uint64_t memory_size = sizeof(*dec->rescaler) +
                               work_size * sizeof(*work) +
                               scaled_data_size * sizeof(*scaled_data);
  uint8_t* memory = (uint8_t*)WebPSafeMalloc(memory_size, sizeof(*memory));
  if (memory == NULL) {
    dec->status_ = VP8_STATUS_OUT_OF_MEMORY;
    return 0;
  }
  assert(dec->rescaler_memory == NULL);
  dec->rescaler_memory = memory;

  dec->rescaler = (WebPRescaler*)memory;
  memory += sizeof(*dec->rescaler);
  work = (rescaler_t*)memory;
  memory += work_size * sizeof(*work);
  scaled_data = (uint32_t*)memory;

  WebPRescalerInit(dec->rescaler, in_width, in_height, (uint8_t*)scaled_data,
                   out_width, out_height, 0, num_channels, work);
  return 1;
}