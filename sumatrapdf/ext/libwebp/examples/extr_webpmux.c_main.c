#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Config ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteConfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREE_WARGV_AND_RETURN (int) ; 
 int /*<<< orphan*/  GET_WARGV_OR_NULL () ; 
 int /*<<< orphan*/  INIT_WARGV (int,char const**) ; 
 int InitializeConfig (int,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintHelp () ; 
 int Process (int /*<<< orphan*/ *) ; 

int main(int argc, const char* argv[]) {
  Config config;
  int ok;

  INIT_WARGV(argc, argv);

  ok = InitializeConfig(argc - 1, argv + 1, &config, GET_WARGV_OR_NULL());
  if (ok) {
    ok = Process(&config);
  } else {
    PrintHelp();
  }
  DeleteConfig(&config);
  FREE_WARGV_AND_RETURN(!ok);
}