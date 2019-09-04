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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  gint ;
struct TYPE_5__ {int /*<<< orphan*/  last_changed; } ;
typedef  TYPE_1__ WTStatus ;
struct TYPE_6__ {TYPE_1__* status; } ;
typedef  TYPE_2__ RepoWatchInfo ;
typedef  int /*<<< orphan*/  FSEventStreamEventId ;
typedef  int FSEventStreamEventFlags ;

/* Variables and functions */
 int /*<<< orphan*/  G_NORMALIZE_NFC ; 
 int /*<<< orphan*/  WT_EVENT_CREATE_OR_UPDATE ; 
 int /*<<< orphan*/  WT_EVENT_DELETE ; 
 int /*<<< orphan*/  add_event_to_queue (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_atomic_int_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 int const kFSEventStreamEventFlagItemCreated ; 
 int const kFSEventStreamEventFlagItemModified ; 
 int const kFSEventStreamEventFlagItemRemoved ; 
 int const kFSEventStreamEventFlagItemRenamed ; 
 int /*<<< orphan*/  seaf_debug (char*,char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int strlen (char const*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_one_event (const char* eventPath,
                   RepoWatchInfo *info,
                   const char *worktree,
                   const FSEventStreamEventId eventId,
                   const FSEventStreamEventFlags eventFlags)
{
    WTStatus *status = info->status;
    char *filename;
    char *event_path_nfc;
    const char *tmp;
    struct stat buf;

    event_path_nfc = g_utf8_normalize (eventPath, -1, G_NORMALIZE_NFC);

    tmp = event_path_nfc + strlen(worktree);
    if (*tmp == '/')
        tmp++;
    filename = g_strdup(tmp);
    g_free (event_path_nfc);

    /* Path for folder returned from system may contain a '/' at the end. */
    int len = strlen(filename);
    if (len > 0 && filename[len - 1] == '/')
        filename[len - 1] = 0;

    /* Reinterpreted RENAMED as combine of CREATED or DELETED event */
    if (eventFlags & kFSEventStreamEventFlagItemRenamed) {
        seaf_debug ("Rename flag set for %s \n", filename);
        if (stat (eventPath, &buf) < 0) {
            /* ret = -1, file is gone */
            add_event_to_queue (status, WT_EVENT_DELETE, filename, NULL);
        } else {
            /* ret = 0, file is here, but rename behaviour is unknown to us */
            add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
        }
    }

    if (eventFlags & kFSEventStreamEventFlagItemRemoved) {
        seaf_debug ("Deleted flag set for %s.\n", filename);
        if (stat (eventPath, &buf) < 0) {
            add_event_to_queue (status, WT_EVENT_DELETE, filename, NULL);
        }
    }

    if (eventFlags & kFSEventStreamEventFlagItemModified) {
        seaf_debug ("Modified flag set for %s.\n", filename);
        if (stat (eventPath, &buf) == 0) {
            add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
        }
    }

    if (eventFlags & kFSEventStreamEventFlagItemCreated) {
        seaf_debug ("Created flag set for %s.\n", filename);
         /**
          * no need to rechecking recursively in FSEventStream
          *
          * these flags are useful if necessary:
          * kFSEventStreamEventFlagItemIsFile
          * kFSEventStreamEventFlagItemIsDir
          * kFSEventStreamEventFlagItemIsSymlink
          */
        if (stat (eventPath, &buf) == 0) {
            add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
        }
    }

    g_free (filename);
    g_atomic_int_set (&info->status->last_changed, (gint)time(NULL));
}