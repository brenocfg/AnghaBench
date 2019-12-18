#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_ino; int st_mode; int st_size; } ;
typedef  int ssize_t ;
typedef  int off_t ;
typedef  scalar_t__ ag_compression_type ;
struct TYPE_2__ {scalar_t__ stdout_inode; char* query; int query_len; int match_found; scalar_t__ mmap; int /*<<< orphan*/  path_sep; scalar_t__ print_nonmatching_files; scalar_t__ search_zip_files; int /*<<< orphan*/  search_binary_files; int /*<<< orphan*/  literal; scalar_t__ search_all_files; } ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AG_NO_COMPRESSION ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessageA (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int INT_MAX ; 
 int /*<<< orphan*/  LocalFree (void*) ; 
 int /*<<< orphan*/  MADV_SEQUENTIAL ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 scalar_t__ MapViewOfFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  POSIX_MADV_SEQUENTIAL ; 
 int /*<<< orphan*/  PROT_READ ; 
 int S_IFIFO ; 
 int /*<<< orphan*/  S_ISFIFO (int) ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int /*<<< orphan*/  UnmapViewOfFile (char*) ; 
 scalar_t__ _get_osfhandle (int) ; 
 char* ag_malloc (int) ; 
 int ag_min (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 char* decompress (scalar_t__,char*,int,char const*,int*) ; 
 int /*<<< orphan*/ * decompress_open (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  die (char*,char const*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 scalar_t__ is_binary (char*,int) ; 
 scalar_t__ is_zipped (char*,int) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int /*<<< orphan*/  log_err (char*,char const*,...) ; 
 int /*<<< orphan*/  madvise (char*,int,int /*<<< orphan*/ ) ; 
 char* mmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ opts ; 
 int /*<<< orphan*/  posix_fadvise (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_cleanup_context () ; 
 int /*<<< orphan*/  print_init_context () ; 
 int /*<<< orphan*/  print_mtx ; 
 int /*<<< orphan*/  print_path (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int read (int,char*,int) ; 
 int search_buf (char*,int,char const*) ; 
 int search_stream (int /*<<< orphan*/ *,char const*) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void search_file(const char *file_full_path) {
    int fd = -1;
    off_t f_len = 0;
    char *buf = NULL;
    struct stat statbuf;
    int rv = 0;
    int matches_count = -1;
    FILE *fp = NULL;

    rv = stat(file_full_path, &statbuf);
    if (rv != 0) {
        log_err("Skipping %s: Error fstat()ing file.", file_full_path);
        goto cleanup;
    }

    if (opts.stdout_inode != 0 && opts.stdout_inode == statbuf.st_ino) {
        log_debug("Skipping %s: stdout is redirected to it", file_full_path);
        goto cleanup;
    }

    // handling only regular files and FIFOs
    if (!S_ISREG(statbuf.st_mode) && !S_ISFIFO(statbuf.st_mode)) {
        log_err("Skipping %s: Mode %u is not a file.", file_full_path, statbuf.st_mode);
        goto cleanup;
    }

    fd = open(file_full_path, O_RDONLY);
    if (fd < 0) {
        /* XXXX: strerror is not thread-safe */
        log_err("Skipping %s: Error opening file: %s", file_full_path, strerror(errno));
        goto cleanup;
    }

    // repeating stat check with file handle to prevent TOCTOU issue
    rv = fstat(fd, &statbuf);
    if (rv != 0) {
        log_err("Skipping %s: Error fstat()ing file.", file_full_path);
        goto cleanup;
    }

    if (opts.stdout_inode != 0 && opts.stdout_inode == statbuf.st_ino) {
        log_debug("Skipping %s: stdout is redirected to it", file_full_path);
        goto cleanup;
    }

    // handling only regular files and FIFOs
    if (!S_ISREG(statbuf.st_mode) && !S_ISFIFO(statbuf.st_mode)) {
        log_err("Skipping %s: Mode %u is not a file.", file_full_path, statbuf.st_mode);
        goto cleanup;
    }

    print_init_context();

    if (statbuf.st_mode & S_IFIFO) {
        log_debug("%s is a named pipe. stream searching", file_full_path);
        fp = fdopen(fd, "r");
        matches_count = search_stream(fp, file_full_path);
        fclose(fp);
        goto cleanup;
    }

    f_len = statbuf.st_size;

    if (f_len == 0) {
        if (opts.query[0] == '.' && opts.query_len == 1 && !opts.literal && opts.search_all_files) {
            matches_count = search_buf(buf, f_len, file_full_path);
        } else {
            log_debug("Skipping %s: file is empty.", file_full_path);
        }
        goto cleanup;
    }

    if (!opts.literal && f_len > INT_MAX) {
        log_err("Skipping %s: pcre_exec() can't handle files larger than %i bytes.", file_full_path, INT_MAX);
        goto cleanup;
    }

#ifdef _WIN32
    {
        HANDLE hmmap = CreateFileMapping(
            (HANDLE)_get_osfhandle(fd), 0, PAGE_READONLY, 0, f_len, NULL);
        buf = (char *)MapViewOfFile(hmmap, FILE_SHARE_READ, 0, 0, f_len);
        if (hmmap != NULL)
            CloseHandle(hmmap);
    }
    if (buf == NULL) {
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, GetLastError(), 0, (void *)&buf, 0, NULL);
        log_err("File %s failed to load: %s.", file_full_path, buf);
        LocalFree((void *)buf);
        goto cleanup;
    }
#else

    if (opts.mmap) {
        buf = mmap(0, f_len, PROT_READ, MAP_PRIVATE, fd, 0);
        if (buf == MAP_FAILED) {
            log_err("File %s failed to load: %s.", file_full_path, strerror(errno));
            goto cleanup;
        }
#if HAVE_MADVISE
        madvise(buf, f_len, MADV_SEQUENTIAL);
#elif HAVE_POSIX_FADVISE
        posix_fadvise(fd, 0, f_len, POSIX_MADV_SEQUENTIAL);
#endif
    } else {
        buf = ag_malloc(f_len);

        ssize_t bytes_read = 0;

        if (!opts.search_binary_files) {
            bytes_read += read(fd, buf, ag_min(f_len, 512));
            // Optimization: If skipping binary files, don't read the whole buffer before checking if binary or not.
            if (is_binary(buf, f_len)) {
                log_debug("File %s is binary. Skipping...", file_full_path);
                goto cleanup;
            }
        }

        while (bytes_read < f_len) {
            bytes_read += read(fd, buf + bytes_read, f_len);
        }
        if (bytes_read != f_len) {
            die("File %s read(): expected to read %u bytes but read %u", file_full_path, f_len, bytes_read);
        }
    }
#endif

    if (opts.search_zip_files) {
        ag_compression_type zip_type = is_zipped(buf, f_len);
        if (zip_type != AG_NO_COMPRESSION) {
#if HAVE_FOPENCOOKIE
            log_debug("%s is a compressed file. stream searching", file_full_path);
            fp = decompress_open(fd, "r", zip_type);
            matches_count = search_stream(fp, file_full_path);
            fclose(fp);
#else
            int _buf_len = (int)f_len;
            char *_buf = decompress(zip_type, buf, f_len, file_full_path, &_buf_len);
            if (_buf == NULL || _buf_len == 0) {
                log_err("Cannot decompress zipped file %s", file_full_path);
                goto cleanup;
            }
            matches_count = search_buf(_buf, _buf_len, file_full_path);
            free(_buf);
#endif
            goto cleanup;
        }
    }

    matches_count = search_buf(buf, f_len, file_full_path);

cleanup:

    if (opts.print_nonmatching_files && matches_count == 0) {
        pthread_mutex_lock(&print_mtx);
        print_path(file_full_path, opts.path_sep);
        pthread_mutex_unlock(&print_mtx);
        opts.match_found = 1;
    }

    print_cleanup_context();
    if (buf != NULL) {
#ifdef _WIN32
        UnmapViewOfFile(buf);
#else
        if (opts.mmap) {
            if (buf != MAP_FAILED) {
                munmap(buf, f_len);
            }
        } else {
            free(buf);
        }
#endif
    }
    if (fd != -1) {
        close(fd);
    }
}