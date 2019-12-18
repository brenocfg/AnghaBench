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
struct TYPE_4__ {int use_argb; int /*<<< orphan*/ * custom_ptr; int /*<<< orphan*/  writer; } ;
typedef  TYPE_1__ WebPPicture ;
typedef  int /*<<< orphan*/  WebPMemoryWriter ;
typedef  int /*<<< orphan*/  WebPConfig ;

/* Variables and functions */
 int /*<<< orphan*/  WebPEncode (int /*<<< orphan*/  const* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  WebPMemoryWrite ; 

__attribute__((used)) static int EncodeFrame(const WebPConfig* const config, WebPPicture* const pic,
                       WebPMemoryWriter* const memory) {
  pic->use_argb = 1;
  pic->writer = WebPMemoryWrite;
  pic->custom_ptr = memory;
  if (!WebPEncode(config, pic)) {
    return 0;
  }
  return 1;
}