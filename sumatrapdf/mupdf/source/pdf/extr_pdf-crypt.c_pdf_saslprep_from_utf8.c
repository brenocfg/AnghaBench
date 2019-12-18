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
 int /*<<< orphan*/  fz_strlcpy (char*,char const*,int) ; 

__attribute__((used)) static void pdf_saslprep_from_utf8(char *password, const char *utf8, int n)
{
	/* TODO: stringprep with SALSprep profile */
	fz_strlcpy(password, utf8, n);
}