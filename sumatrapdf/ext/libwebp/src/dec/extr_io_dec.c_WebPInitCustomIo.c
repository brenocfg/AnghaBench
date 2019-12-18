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
typedef  int /*<<< orphan*/  WebPDecParams ;
struct TYPE_3__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/  teardown; int /*<<< orphan*/  setup; int /*<<< orphan*/  put; } ;
typedef  TYPE_1__ VP8Io ;

/* Variables and functions */
 int /*<<< orphan*/  CustomPut ; 
 int /*<<< orphan*/  CustomSetup ; 
 int /*<<< orphan*/  CustomTeardown ; 

void WebPInitCustomIo(WebPDecParams* const params, VP8Io* const io) {
  io->put      = CustomPut;
  io->setup    = CustomSetup;
  io->teardown = CustomTeardown;
  io->opaque   = params;
}