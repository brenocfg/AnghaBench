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

/* Variables and functions */
 scalar_t__ sqllog_isspace (char const) ; 

__attribute__((used)) static void sqllogTokenize(const char *z, const char **pz, int *pn){
  const char *p = z;
  int n;

  /* Skip past any whitespace */
  while( sqllog_isspace(*p) ){
    p++;
  }

  /* Figure out how long the first token is */
  *pz = p;
  n = 0;
  while( (p[n]>='a' && p[n]<='z') || (p[n]>='A' && p[n]<='Z') ) n++;
  *pn = n;
}