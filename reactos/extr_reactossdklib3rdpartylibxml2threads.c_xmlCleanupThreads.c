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