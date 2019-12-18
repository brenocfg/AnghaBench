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
struct TYPE_3__ {int /*<<< orphan*/  ap_q_lock; int /*<<< orphan*/  active_paths; int /*<<< orphan*/  q_lock; int /*<<< orphan*/  event_q; } ;
typedef  TYPE_1__ WTStatus ;
typedef  int /*<<< orphan*/  WTEvent ;

/* Variables and functions */
 int /*<<< orphan*/  G_NORMALIZE_NFC ; 
#define  WT_EVENT_ATTRIB 133 
#define  WT_EVENT_CREATE_OR_UPDATE 132 
#define  WT_EVENT_DELETE 131 
#define  WT_EVENT_OVERFLOW 130 
#define  WT_EVENT_RENAME 129 
#define  WT_EVENT_SCAN_DIR 128 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_queue_peek_tail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_queue_push_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup (char const*) ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_debug (char*,char*,char const*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/ * wt_event_new (int,char*,char*) ; 

__attribute__((used)) static void
add_event_to_queue (WTStatus *status,
                    int type, const char *path, const char *new_path)
{
    char *nfc_path = NULL, *nfc_new_path = NULL;

    if (path)
        nfc_path = g_utf8_normalize (path, -1, G_NORMALIZE_NFC);
    if (new_path)
        nfc_new_path = g_utf8_normalize (new_path, -1, G_NORMALIZE_NFC);

    WTEvent *event = wt_event_new (type, nfc_path, nfc_new_path);

    g_free (nfc_path);
    g_free (nfc_new_path);

    char *name;
    switch (type) {
    case WT_EVENT_CREATE_OR_UPDATE:
        name = "create/update";
        break;
    case WT_EVENT_SCAN_DIR:
        name = "scan dir";
        break;
    case WT_EVENT_DELETE:
        name = "delete";
        break;
    case WT_EVENT_RENAME:
        name = "rename";
        break;
    case WT_EVENT_OVERFLOW:
        name = "overflow";
        break;
    case WT_EVENT_ATTRIB:
        name = "attribute change";
        break;
    default:
        name = "unknown";
    }

    seaf_debug ("Adding event: %s, %s %s\n", name, path, new_path?new_path:"");

    pthread_mutex_lock (&status->q_lock);
    g_queue_push_tail (status->event_q, event);
    pthread_mutex_unlock (&status->q_lock);

    if (type == WT_EVENT_CREATE_OR_UPDATE) {
        pthread_mutex_lock (&status->ap_q_lock);

        char *last = g_queue_peek_tail (status->active_paths);
        if (!last || strcmp(last, path) != 0)
            g_queue_push_tail (status->active_paths, g_strdup(path));

        pthread_mutex_unlock (&status->ap_q_lock);
    }
}