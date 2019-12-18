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
struct TYPE_3__ {int argc_; int /*<<< orphan*/ * argv_; } ;
typedef  TYPE_1__ CommandLineArguments ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const* const) ; 

__attribute__((used)) static int CountOccurrences(const CommandLineArguments* const args,
                            const char* const arg) {
  int i;
  int num_occurences = 0;

  for (i = 0; i < args->argc_; ++i) {
    if (!strcmp(args->argv_[i], arg)) {
      ++num_occurences;
    }
  }
  return num_occurences;
}