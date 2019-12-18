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
struct TYPE_4__ {int /*<<< orphan*/  cmd_args_; int /*<<< orphan*/  args_; } ;
typedef  TYPE_1__ Config ;

/* Variables and functions */
 int /*<<< orphan*/  ExUtilDeleteCommandLineArguments (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void DeleteConfig(Config* const config) {
  if (config != NULL) {
    free(config->args_);
    ExUtilDeleteCommandLineArguments(&config->cmd_args_);
    memset(config, 0, sizeof(*config));
  }
}