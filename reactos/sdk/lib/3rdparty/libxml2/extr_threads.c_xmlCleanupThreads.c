#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  memory; struct TYPE_4__* next; } ;
typedef  TYPE_1__ xmlGlobalStateCleanupHelperParams ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 int /*<<< orphan*/  TlsFree (scalar_t__) ; 
 int /*<<< orphan*/  cleanup_helpers_cs ; 
 TYPE_1__* cleanup_helpers_head ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ globalkey ; 
 scalar_t__ libxml_is_threaded ; 
 int /*<<< orphan*/  once_control ; 
 int /*<<< orphan*/  once_control_init ; 
 int /*<<< orphan*/  pthread_key_delete (scalar_t__) ; 
 int /*<<< orphan*/  xmlFreeGlobalState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

void
xmlCleanupThreads(void)
{
#ifdef DEBUG_THREADS
    xmlGenericError(xmlGenericErrorContext, "xmlCleanupThreads()\n");
#endif
#ifdef HAVE_PTHREAD_H
    if (libxml_is_threaded != 0)
        pthread_key_delete(globalkey);
    once_control = once_control_init;
#elif defined(HAVE_WIN32_THREADS) && !defined(HAVE_COMPILER_TLS) && (!defined(LIBXML_STATIC) || defined(LIBXML_STATIC_FOR_DLL))
    if (globalkey != TLS_OUT_OF_INDEXES) {
        xmlGlobalStateCleanupHelperParams *p;

        EnterCriticalSection(&cleanup_helpers_cs);
        p = cleanup_helpers_head;
        while (p != NULL) {
            xmlGlobalStateCleanupHelperParams *temp = p;

            p = p->next;
            xmlFreeGlobalState(temp->memory);
            free(temp);
        }
        cleanup_helpers_head = 0;
        LeaveCriticalSection(&cleanup_helpers_cs);
        TlsFree(globalkey);
        globalkey = TLS_OUT_OF_INDEXES;
    }
    DeleteCriticalSection(&cleanup_helpers_cs);
#endif
}