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
struct TYPE_3__ {scalar_t__ eType; char* zText; } ;
typedef  TYPE_1__ CmdLineOption ;

/* Variables and functions */
 scalar_t__ CMDLINE_INTEGER ; 
 scalar_t__ CMDLINE_STRING ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void option_requires_argument_error(CmdLineOption *pOpt){
  fprintf(stderr, "Option requires a%s argument: %s\n", 
      pOpt->eType==CMDLINE_INTEGER ? "n integer" :
      pOpt->eType==CMDLINE_STRING ? " string" : " boolean",
      pOpt->zText
  );
  exit(1);
}