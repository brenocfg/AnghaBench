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
struct HttpAuthInfo {struct HttpAuthInfo* scheme; struct HttpAuthInfo* auth_data; int /*<<< orphan*/  cred; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (struct HttpAuthInfo*) ; 

__attribute__((used)) static void destroy_authinfo( struct HttpAuthInfo *authinfo )
{
    if (!authinfo) return;

    if (SecIsValidHandle(&authinfo->ctx))
        DeleteSecurityContext(&authinfo->ctx);
    if (SecIsValidHandle(&authinfo->cred))
        FreeCredentialsHandle(&authinfo->cred);

    heap_free(authinfo->auth_data);
    heap_free(authinfo->scheme);
    heap_free(authinfo);
}