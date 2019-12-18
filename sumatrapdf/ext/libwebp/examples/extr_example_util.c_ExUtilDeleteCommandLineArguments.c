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
struct TYPE_4__ {int /*<<< orphan*/  argv_data_; scalar_t__ argv_; scalar_t__ own_argv_; } ;
typedef  TYPE_1__ CommandLineArguments ;

/* Variables and functions */
 int /*<<< orphan*/  ResetCommandLineArguments (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__* const) ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPFree (void*) ; 

void ExUtilDeleteCommandLineArguments(CommandLineArguments* const args) {
  if (args != NULL) {
    if (args->own_argv_) {
      WebPFree((void*)args->argv_);
      WebPDataClear(&args->argv_data_);
    }
    ResetCommandLineArguments(0, NULL, args);
  }
}