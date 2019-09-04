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
typedef  scalar_t__ adns_status ;

/* Variables and functions */
 char* adns_strerror (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void dumptype(adns_status ri, const char *rrtn, const char *fmtn) {
  fprintf(stdout, "%s(%s)%s%s",
	  ri ? "?" : rrtn, ri ? "?" : fmtn ? fmtn : "-",
	  ri ? " " : "", ri ? adns_strerror(ri) : "");
}