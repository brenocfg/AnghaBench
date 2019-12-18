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
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int psd_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi_psd_test(stbi *s)
{
   int r = psd_test(s);
   stbi_rewind(s);
   return r;
}