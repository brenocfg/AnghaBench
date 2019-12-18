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
struct rusage {scalar_t__ ru_inblock; scalar_t__ ru_oublock; scalar_t__ ru_maxrss; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  memset (struct rusage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static void lsmtest_rusage_report(void){
  struct rusage r;
  memset(&r, 0, sizeof(r));

  getrusage(RUSAGE_SELF, &r);
  printf("# getrusage: { ru_maxrss %d ru_oublock %d ru_inblock %d }\n", 
      (int)r.ru_maxrss, (int)r.ru_oublock, (int)r.ru_inblock
  );
}