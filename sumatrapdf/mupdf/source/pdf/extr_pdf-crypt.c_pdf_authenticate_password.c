#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* crypt; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int r; } ;

/* Variables and functions */
 scalar_t__ pdf_authenticate_owner_password (int /*<<< orphan*/ *,TYPE_2__*,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_authenticate_user_password (int /*<<< orphan*/ *,TYPE_2__*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_docenc_from_utf8 (char*,char const*,int) ; 
 int /*<<< orphan*/  pdf_saslprep_from_utf8 (char*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
pdf_authenticate_password(fz_context *ctx, pdf_document *doc, const char *pwd_utf8)
{
	char password[2048];
	int auth;

	if (!doc->crypt)
		return 1; /* No password required */

	password[0] = 0;
	if (pwd_utf8)
	{
		if (doc->crypt->r <= 4)
			pdf_docenc_from_utf8(password, pwd_utf8, sizeof password);
		else
			pdf_saslprep_from_utf8(password, pwd_utf8, sizeof password);
	}

	auth = 0;
	if (pdf_authenticate_user_password(ctx, doc->crypt, (unsigned char *)password, strlen(password)))
		auth = 2;
	if (pdf_authenticate_owner_password(ctx, doc->crypt, (unsigned char *)password, strlen(password)))
		auth |= 4;
	else if (auth & 2)
	{
		/* We need to reauthenticate the user password,
		 * because the failed attempt to authenticate
		 * the owner password will have invalidated the
		 * stored keys. */
		(void)pdf_authenticate_user_password(ctx, doc->crypt, (unsigned char *)password, strlen(password));
	}

	/* To match Acrobat, we choose not to allow an empty owner
	 * password, unless the user password is also the empty one. */
	if (*password == 0 && auth == 4)
		return 0;

	return auth;
}