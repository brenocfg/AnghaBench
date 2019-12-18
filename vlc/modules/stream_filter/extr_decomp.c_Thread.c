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
struct iovec {unsigned char* iov_base; scalar_t__ iov_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {int write_fd; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; scalar_t__ paused; } ;
typedef  TYPE_2__ stream_sys_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 scalar_t__ EPIPE ; 
 int MAP_ANONYMOUS ; 
 unsigned char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SPLICE_F_GIFT ; 
 int /*<<< orphan*/  _SC_PAGE_SIZE ; 
 int /*<<< orphan*/  bufsize ; 
 int /*<<< orphan*/  cleanup_mmap (unsigned char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int /*<<< orphan*/ ) ; 
 unsigned char* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/  (*) (unsigned char*),unsigned char*) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 
 scalar_t__ vmsplice (int,struct iovec*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,unsigned char*,scalar_t__) ; 

__attribute__((used)) static void *Thread (void *data)
{
    stream_t *stream = data;
    stream_sys_t *p_sys = stream->p_sys;
#ifdef HAVE_VMSPLICE
    const ssize_t page_mask = sysconf (_SC_PAGE_SIZE) - 1;
#endif
    int fd = p_sys->write_fd;
    bool error = false;
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGPIPE);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    do
    {
        ssize_t len;
        int canc = vlc_savecancel ();
#ifdef HAVE_VMSPLICE
        unsigned char *buf = mmap (NULL, bufsize, PROT_READ|PROT_WRITE,
                                   MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        if (unlikely(buf == MAP_FAILED))
            break;
        vlc_cleanup_push (cleanup_mmap, buf);
#else
        unsigned char *buf = malloc (bufsize);
        if (unlikely(buf == NULL))
            break;
        vlc_cleanup_push (free, buf);
#endif

        vlc_mutex_lock (&p_sys->lock);
        while (p_sys->paused) /* practically always false, but... */
            vlc_cond_wait (&p_sys->wait, &p_sys->lock);
        len = vlc_stream_Read (stream->s, buf, bufsize);
        vlc_mutex_unlock (&p_sys->lock);

        vlc_restorecancel (canc);
        error = len <= 0;

        for (ssize_t i = 0, j; i < len; i += j)
        {
#ifdef HAVE_VMSPLICE
            if ((len - i) <= page_mask) /* incomplete last page */
                j = write (fd, buf + i, len - i);
            else
            {
                struct iovec iov = {
                    .iov_base = buf + i,
                    .iov_len = (len - i) & ~page_mask };

                j = vmsplice (fd, &iov, 1, SPLICE_F_GIFT);
            }
            if (j == -1 && errno == ENOSYS) /* vmsplice() not supported */
#endif
            j = write (fd, buf + i, len - i);
            if (j <= 0)
            {
                if (j == 0)
                    errno = EPIPE;
                msg_Err (stream, "cannot write data: %s",
                         vlc_strerror_c(errno));
                error = true;
                break;
            }
        }
        vlc_cleanup_pop ();
#ifdef HAVE_VMSPLICE
        munmap (buf, bufsize);
#else
        free (buf);
#endif
    }
    while (!error);

    msg_Dbg (stream, "compressed stream at EOF");
    /* Let child process know about EOF */
    p_sys->write_fd = -1;
    vlc_close (fd);
    return NULL;
}