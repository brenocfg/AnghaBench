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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unused_parameter (int) ; 

__attribute__((used)) static void xLog(void *pCtx, int rc, const char *z){
  unused_parameter(rc);
  /* fprintf(stderr, "lsm: rc=%d \"%s\"\n", rc, z); */
  if( pCtx ) fprintf(stderr, "%s: ", (char *)pCtx);
  fprintf(stderr, "%s\n", z);
  fflush(stderr);
}