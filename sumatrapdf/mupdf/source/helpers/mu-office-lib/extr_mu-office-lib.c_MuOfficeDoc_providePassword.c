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
struct TYPE_3__ {int /*<<< orphan*/  password_sem; int /*<<< orphan*/  password; } ;
typedef  TYPE_1__ MuOfficeDoc ;

/* Variables and functions */
 int MuError_OK ; 
 int MuError_PasswordPending ; 
 int /*<<< orphan*/  Pal_Mem_malloc (size_t) ; 
 int /*<<< orphan*/  mu_trigger_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 

int MuOfficeDoc_providePassword(MuOfficeDoc *doc, const char *password)
{
	size_t len;

	if (doc->password)
		return MuError_PasswordPending;
	if (!password)
		password = "";

	len = strlen(password);
	doc->password = Pal_Mem_malloc(len+1);
	strcpy(doc->password, password);
	mu_trigger_semaphore(&doc->password_sem);

	return MuError_OK;
}