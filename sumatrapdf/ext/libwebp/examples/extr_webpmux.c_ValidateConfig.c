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
struct TYPE_3__ {scalar_t__ action_type_; scalar_t__ type_; int /*<<< orphan*/ * output_; int /*<<< orphan*/ * input_; } ;
typedef  TYPE_1__ Config ;

/* Variables and functions */
 scalar_t__ ACTION_INFO ; 
 scalar_t__ ACTION_IS_NIL ; 
 scalar_t__ ACTION_SET ; 
 int /*<<< orphan*/  ERROR_GOTO1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ErrValidate2 ; 
 scalar_t__ FEATURETYPE_IS_NIL ; 
 scalar_t__ FEATURE_ANMF ; 

__attribute__((used)) static int ValidateConfig(Config* const config) {
  int ok = 1;

  // Action.
  if (ACTION_IS_NIL) {
    ERROR_GOTO1("ERROR: No action specified.\n", ErrValidate2);
  }

  // Feature type.
  if (FEATURETYPE_IS_NIL && config->action_type_ != ACTION_INFO) {
    ERROR_GOTO1("ERROR: No feature specified.\n", ErrValidate2);
  }

  // Input file.
  if (config->input_ == NULL) {
    if (config->action_type_ != ACTION_SET) {
      ERROR_GOTO1("ERROR: No input file specified.\n", ErrValidate2);
    } else if (config->type_ != FEATURE_ANMF) {
      ERROR_GOTO1("ERROR: No input file specified.\n", ErrValidate2);
    }
  }

  // Output file.
  if (config->output_ == NULL && config->action_type_ != ACTION_INFO) {
    ERROR_GOTO1("ERROR: No output file specified.\n", ErrValidate2);
  }

 ErrValidate2:
  return ok;
}