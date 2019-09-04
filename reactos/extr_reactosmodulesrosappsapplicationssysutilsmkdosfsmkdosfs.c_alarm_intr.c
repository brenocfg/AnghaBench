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
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 scalar_t__ blocks ; 
 scalar_t__ currently_testing ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
alarm_intr (int alnum)
{
  if (currently_testing >= blocks)
    return;

  signal (SIGALRM, alarm_intr);
  alarm (5);
  if (!currently_testing)
    return;

  printf ("%d... ", currently_testing);
  fflush (stdout);
}