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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  msg (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aargh(const char *cause) {
  const char *why = strerror(errno);
  if (!why) why = "Unknown error";
  msg("%s: %s (%d)", cause, why, errno);
  exit(1);
}