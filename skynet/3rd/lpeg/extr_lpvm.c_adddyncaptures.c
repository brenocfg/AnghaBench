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
struct TYPE_3__ {int siz; int idx; char const* s; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ Capture ;

/* Variables and functions */
 int /*<<< orphan*/  Cclose ; 
 int /*<<< orphan*/  Cgroup ; 
 int /*<<< orphan*/  Cruntime ; 

__attribute__((used)) static void adddyncaptures (const char *s, Capture *base, int n, int fd) {
  int i;
  base[0].kind = Cgroup;  /* create group capture */
  base[0].siz = 0;
  base[0].idx = 0;  /* make it an anonymous group */
  for (i = 1; i <= n; i++) {  /* add runtime captures */
    base[i].kind = Cruntime;
    base[i].siz = 1;  /* mark it as closed */
    base[i].idx = fd + i - 1;  /* stack index of capture value */
    base[i].s = s;
  }
  base[i].kind = Cclose;  /* close group */
  base[i].siz = 1;
  base[i].s = s;
}