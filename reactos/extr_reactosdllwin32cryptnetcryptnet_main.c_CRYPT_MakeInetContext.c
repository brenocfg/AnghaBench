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
struct InetContext {int /*<<< orphan*/  error; int /*<<< orphan*/  timeout; int /*<<< orphan*/  event; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct InetContext* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (struct InetContext*) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static struct InetContext *CRYPT_MakeInetContext(DWORD dwTimeout)
{
    struct InetContext *context = CryptMemAlloc(sizeof(struct InetContext));

    if (context)
    {
        context->event = CreateEventW(NULL, FALSE, FALSE, NULL);
        if (!context->event)
        {
            CryptMemFree(context);
            context = NULL;
        }
        else
        {
            context->timeout = dwTimeout;
            context->error = ERROR_SUCCESS;
        }
    }
    return context;
}