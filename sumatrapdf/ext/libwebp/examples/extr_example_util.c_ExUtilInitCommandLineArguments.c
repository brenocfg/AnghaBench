#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bytes; } ;
struct TYPE_5__ {int own_argv_; char const** argv_; int argc_; TYPE_3__ argv_data_; } ;
typedef  TYPE_1__ CommandLineArguments ;

/* Variables and functions */
 int /*<<< orphan*/  ExUtilReadFileToWebPData (char const*,TYPE_3__*) ; 
 int MAX_ARGC ; 
 int /*<<< orphan*/  ResetCommandLineArguments (int,char const**,TYPE_1__* const) ; 
 scalar_t__ WebPMalloc (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 
 char* strtok (char*,char const*) ; 

int ExUtilInitCommandLineArguments(int argc, const char* argv[],
                                   CommandLineArguments* const args) {
  if (args == NULL || argv == NULL) return 0;
  ResetCommandLineArguments(argc, argv, args);
  if (argc == 1 && argv[0][0] != '-') {
    char* cur;
    const char sep[] = " \t\r\n\f\v";

#if defined(_WIN32) && defined(_UNICODE)
    fprintf(stderr,
            "Error: Reading arguments from a file is a feature unavailable "
            "with Unicode binaries.\n");
    return 0;
#endif

    if (!ExUtilReadFileToWebPData(argv[0], &args->argv_data_)) {
      return 0;
    }
    args->own_argv_ = 1;
    args->argv_ = (const char**)WebPMalloc(MAX_ARGC * sizeof(*args->argv_));
    if (args->argv_ == NULL) return 0;

    argc = 0;
    for (cur = strtok((char*)args->argv_data_.bytes, sep);
         cur != NULL;
         cur = strtok(NULL, sep)) {
      if (argc == MAX_ARGC) {
        fprintf(stderr, "ERROR: Arguments limit %d reached\n", MAX_ARGC);
        return 0;
      }
      assert(strlen(cur) != 0);
      args->argv_[argc++] = cur;
    }
    args->argc_ = argc;
  }
  return 1;
}