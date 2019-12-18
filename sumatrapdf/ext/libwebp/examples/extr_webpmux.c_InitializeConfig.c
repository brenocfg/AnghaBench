#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  W_CHAR ;
struct TYPE_6__ {int arg_count_; int /*<<< orphan*/ * args_; int /*<<< orphan*/  cmd_args_; } ;
typedef  int /*<<< orphan*/  FeatureArg ;
typedef  TYPE_1__ Config ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_GOTO1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Err1 ; 
 int ExUtilInitCommandLineArguments (int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseCommandLine (TYPE_1__* const,int /*<<< orphan*/  const** const) ; 
 int /*<<< orphan*/  ValidateCommandLine (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ValidateConfig (TYPE_1__* const) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int InitializeConfig(int argc, const char* argv[], Config* const config,
                            const W_CHAR** const unicode_argv) {
  int num_feature_args = 0;
  int ok;

  memset(config, 0, sizeof(*config));

  ok = ExUtilInitCommandLineArguments(argc, argv, &config->cmd_args_);
  if (!ok) return 0;

  // Validate command-line arguments.
  if (!ValidateCommandLine(&config->cmd_args_, &num_feature_args)) {
    ERROR_GOTO1("Exiting due to command-line parsing error.\n", Err1);
  }

  config->arg_count_ = num_feature_args;
  config->args_ = (FeatureArg*)calloc(num_feature_args, sizeof(*config->args_));
  if (config->args_ == NULL) {
    ERROR_GOTO1("ERROR: Memory allocation error.\n", Err1);
  }

  // Parse command-line.
  if (!ParseCommandLine(config, unicode_argv) || !ValidateConfig(config)) {
    ERROR_GOTO1("Exiting due to command-line parsing error.\n", Err1);
  }

 Err1:
  return ok;
}