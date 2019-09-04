#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct FSEventStreamContext {int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; TYPE_3__* member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__* gpointer ;
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  info_hash; int /*<<< orphan*/  handle_hash; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ SeafWTMonitorPriv ;
typedef  TYPE_3__ SeafWTMonitor ;
typedef  TYPE_1__ RepoWatchInfo ;
typedef  scalar_t__ FSEventStreamRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFArrayCreate (int /*<<< orphan*/ *,void const**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRunLoopGetCurrent () ; 
 int /*<<< orphan*/  CFStringCreateWithCString (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FSEventStreamCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct FSEventStreamContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSEventStreamScheduleWithRunLoop (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSEventStreamStart (scalar_t__) ; 
 int /*<<< orphan*/  G_NORMALIZE_NFD ; 
 int /*<<< orphan*/  WT_EVENT_SCAN_DIR ; 
 int /*<<< orphan*/  add_event_to_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_repo_watch_info (char const*,char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* g_strdup (char const*) ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFRunLoopDefaultMode ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  kFSEventStreamCreateFlagFileEvents ; 
 int /*<<< orphan*/  kFSEventStreamEventIdSinceNow ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_debug (char*,char const*,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/  stream_callback ; 

__attribute__((used)) static FSEventStreamRef
add_watch (SeafWTMonitor *monitor, const char* repo_id, const char* worktree)
{
    SeafWTMonitorPriv *priv = monitor->priv;
    RepoWatchInfo *info;
    double latency = 0.25; /* unit: second */

    char *worktree_nfd = g_utf8_normalize (worktree, -1, G_NORMALIZE_NFD);

    CFStringRef mypaths[1];
    mypaths[0] = CFStringCreateWithCString (kCFAllocatorDefault,
                                            worktree_nfd, kCFStringEncodingUTF8);
    g_free (worktree_nfd);
    CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)mypaths, 1, NULL);
    FSEventStreamRef stream;

    /* Create the stream, passing in a callback */
    // kFSEventStreamCreateFlagFileEvents does not work for libraries with name
    // containing accent characters.
    struct FSEventStreamContext ctx = {0, monitor, NULL, NULL, NULL};
    stream = FSEventStreamCreate(kCFAllocatorDefault,
                                 stream_callback,
                                 &ctx,
                                 pathsToWatch,
                                 kFSEventStreamEventIdSinceNow,
                                 latency,
                                 kFSEventStreamCreateFlagFileEvents
                                 );

    CFRelease (mypaths[0]);
    CFRelease (pathsToWatch);

    if (!stream) {
        seaf_warning ("[wt] Failed to create event stream.\n");
        return stream;
    }

    FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
    FSEventStreamStart (stream);
    /* FSEventStreamShow (stream); */
    seaf_debug ("[wt mon] Add repo %s watch success: %s.\n", repo_id, worktree);

    pthread_mutex_lock (&priv->hash_lock);
    g_hash_table_insert (priv->handle_hash,
                         g_strdup(repo_id), (gpointer)(long)stream);

    info = create_repo_watch_info (repo_id, worktree);
    g_hash_table_insert (priv->info_hash, (gpointer)(long)stream, info);
    pthread_mutex_unlock (&priv->hash_lock);

    /* A special event indicates repo-mgr to scan the whole worktree. */
    add_event_to_queue (info->status, WT_EVENT_SCAN_DIR, "", NULL);
    return stream;
}