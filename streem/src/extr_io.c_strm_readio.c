#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; int st_size; } ;
struct fd_read_buffer {void* buf; void* end; void* beg; int /*<<< orphan*/  fd; void* fixed; TYPE_2__* io; } ;
struct TYPE_6__ {unsigned int flags; } ;
typedef  TYPE_1__ strm_stream ;
typedef  TYPE_2__* strm_io ;
typedef  int /*<<< orphan*/  strm_callback ;
struct TYPE_7__ {TYPE_1__* read_stream; int /*<<< orphan*/  fd; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 unsigned int STRM_IO_NOFILL ; 
 unsigned int STRM_IO_NOWAIT ; 
 int /*<<< orphan*/  STRM_IO_READING ; 
 int S_IFMT ; 
 int S_IFREG ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 struct fd_read_buffer* malloc (int) ; 
 void* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/  read_close ; 
 int /*<<< orphan*/  readline_cb ; 
 int /*<<< orphan*/  stdio_read ; 
 int /*<<< orphan*/  strm_producer ; 
 TYPE_1__* strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static strm_stream*
strm_readio(strm_io io)
{
  strm_callback cb = stdio_read;
  unsigned int flags = 0;

  if (io->read_stream == NULL) {
    struct fd_read_buffer *buf = malloc(sizeof(struct fd_read_buffer));
    struct stat st;

    io->mode |= STRM_IO_READING;
    buf->fd = io->fd;
    buf->io = io;
#ifdef STRM_IO_MMAP    
    buf->buf = buf->fixed;
#endif

    if (fstat(io->fd, &st) == 0 && (st.st_mode & S_IFMT) == S_IFREG) {
      /* fd must be a regular file */
      /* try mmap if STRM_IO_MMAP is defined */
      flags |= STRM_IO_NOWAIT;
#ifdef STRM_IO_MMAP
      void* map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, buf->fd, 0);
      if (map == MAP_FAILED) {
        buf->beg = buf->end = buf->buf;
      }
      else {
        buf->buf = buf->beg = map;
        buf->end = map + st.st_size;
        flags |= STRM_IO_NOFILL;
        /* enqueue task without waiting */
        cb = readline_cb;
      }
#else
      /* stdio_read (epoll) does not work for regular files */
      cb = read_cb;
      buf->beg = buf->end = buf->buf;
#endif
    }
    else {
      buf->beg = buf->end = buf->buf;
    }
    io->read_stream = strm_stream_new(strm_producer, cb, read_close, (void*)buf);
    io->read_stream->flags |= flags;
  }
  return io->read_stream;
}