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
typedef  scalar_t__ Int32 ;
typedef  int /*<<< orphan*/  const Char ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ strlen (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static 
Bool hasSuffix ( Char* s, const Char* suffix )
{
   Int32 ns = strlen(s);
   Int32 nx = strlen(suffix);
   if (ns < nx) return False;
   if (strcmp(s + ns - nx, suffix) == 0) return True;
   return False;
}