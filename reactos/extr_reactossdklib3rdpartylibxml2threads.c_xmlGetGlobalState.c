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
typedef  int /*<<< orphan*/ * xmlGlobalStatePtr ;

/* Variables and functions */

xmlGlobalStatePtr
xmlGetGlobalState(void)
{
#ifdef HAVE_PTHREAD_H
    xmlGlobalState *globalval;

    if (libxml_is_threaded == 0)
        return (NULL);

    pthread_once(&once_control, xmlOnceInit);

    if ((globalval = (xmlGlobalState *)
         pthread_getspecific(globalkey)) == NULL) {
        xmlGlobalState *tsd = xmlNewGlobalState();
	if (tsd == NULL)
	    return(NULL);

        pthread_setspecific(globalkey, tsd);
        return (tsd);
    }
    return (globalval);
#elif defined HAVE_WIN32_THREADS
#if defined(HAVE_COMPILER_TLS)
    if (!tlstate_inited) {
        tlstate_inited = 1;
        xmlInitializeGlobalState(&tlstate);
    }
    return &tlstate;
#else /* HAVE_COMPILER_TLS */
    xmlGlobalState *globalval;
    xmlGlobalStateCleanupHelperParams *p;

    xmlOnceInit();
#if defined(LIBXML_STATIC) && !defined(LIBXML_STATIC_FOR_DLL)
    globalval = (xmlGlobalState *) TlsGetValue(globalkey);
#else
    p = (xmlGlobalStateCleanupHelperParams *) TlsGetValue(globalkey);
    globalval = (xmlGlobalState *) (p ? p->memory : NULL);
#endif
    if (globalval == NULL) {
        xmlGlobalState *tsd = xmlNewGlobalState();

        if (tsd == NULL)
	    return(NULL);
        p = (xmlGlobalStateCleanupHelperParams *)
            malloc(sizeof(xmlGlobalStateCleanupHelperParams));
	if (p == NULL) {
            xmlGenericError(xmlGenericErrorContext,
                            "xmlGetGlobalState: out of memory\n");
            xmlFreeGlobalState(tsd);
	    return(NULL);
	}
        p->memory = tsd;
#if defined(LIBXML_STATIC) && !defined(LIBXML_STATIC_FOR_DLL)
        DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
                        GetCurrentProcess(), &p->thread, 0, TRUE,
                        DUPLICATE_SAME_ACCESS);
        TlsSetValue(globalkey, tsd);
        _beginthread(xmlGlobalStateCleanupHelper, 0, p);
#else
        EnterCriticalSection(&cleanup_helpers_cs);
        if (cleanup_helpers_head != NULL) {
            cleanup_helpers_head->prev = p;
        }
        p->next = cleanup_helpers_head;
        p->prev = NULL;
        cleanup_helpers_head = p;
        TlsSetValue(globalkey, p);
        LeaveCriticalSection(&cleanup_helpers_cs);
#endif

        return (tsd);
    }
    return (globalval);
#endif /* HAVE_COMPILER_TLS */
#elif defined HAVE_BEOS_THREADS
    xmlGlobalState *globalval;

    xmlOnceInit();

    if ((globalval = (xmlGlobalState *) tls_get(globalkey)) == NULL) {
        xmlGlobalState *tsd = xmlNewGlobalState();
	if (tsd == NULL)
	    return (NULL);

        tls_set(globalkey, tsd);
        on_exit_thread(xmlGlobalStateCleanup, NULL);
        return (tsd);
    }
    return (globalval);
#else
    return (NULL);
#endif
}