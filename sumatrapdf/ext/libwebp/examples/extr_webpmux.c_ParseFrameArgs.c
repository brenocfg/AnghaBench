#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  blend_method; int /*<<< orphan*/  dispose_method; int /*<<< orphan*/  y_offset; int /*<<< orphan*/  x_offset; int /*<<< orphan*/  duration; } ;
typedef  TYPE_1__ WebPMuxFrameInfo ;
typedef  int /*<<< orphan*/  WebPMuxAnimDispose ;

/* Variables and functions */
 int /*<<< orphan*/  WEBP_MUX_BLEND ; 
 int /*<<< orphan*/  WEBP_MUX_NO_BLEND ; 
 int /*<<< orphan*/  WarnAboutOddOffset (TYPE_1__* const) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,char*,char*,int*) ; 

__attribute__((used)) static int ParseFrameArgs(const char* args, WebPMuxFrameInfo* const info) {
  int dispose_method, dummy;
  char plus_minus, blend_method;
  const int num_args = sscanf(args, "+%d+%d+%d+%d%c%c+%d", &info->duration,
                              &info->x_offset, &info->y_offset, &dispose_method,
                              &plus_minus, &blend_method, &dummy);
  switch (num_args) {
    case 1:
      info->x_offset = info->y_offset = 0;  // fall through
    case 3:
      dispose_method = 0;  // fall through
    case 4:
      plus_minus = '+';
      blend_method = 'b';  // fall through
    case 6:
      break;
    case 2:
    case 5:
    default:
      return 0;
  }

  WarnAboutOddOffset(info);

  // Note: The sanity of the following conversion is checked by
  // WebPMuxPushFrame().
  info->dispose_method = (WebPMuxAnimDispose)dispose_method;

  if (blend_method != 'b') return 0;
  if (plus_minus != '-' && plus_minus != '+') return 0;
  info->blend_method =
      (plus_minus == '+') ? WEBP_MUX_BLEND : WEBP_MUX_NO_BLEND;
  return 1;
}