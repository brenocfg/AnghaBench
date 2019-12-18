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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int,...) ; 
 int flock (int,int) ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 
 int g_open (char const*,int,int) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,...) ; 
 int getpid () ; 
 int /*<<< orphan*/  remove_pid_file (int) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ write (int,char*,int) ; 

int create_pid_file ( const char *pidfile )
{
    if ( pidfile == NULL ) {
        return -1;
    }

    int fd = g_open ( pidfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    if ( fd < 0 ) {
        g_warning ( "Failed to create pid file: '%s'.", pidfile );
        return -1;
    }
    // Set it to close the File Descriptor on exit.
    int flags = fcntl ( fd, F_GETFD, NULL );
    flags = flags | FD_CLOEXEC;
    if ( fcntl ( fd, F_SETFD, flags, NULL ) < 0 ) {
        g_warning ( "Failed to set CLOEXEC on pidfile." );
        remove_pid_file ( fd );
        return -1;
    }
    // Try to get exclusive write lock on FD
    int retv = flock ( fd, LOCK_EX | LOCK_NB );
    if ( retv != 0 ) {
        g_warning ( "Failed to set lock on pidfile: Rofi already running?" );
        g_warning ( "Got error: %d %s", retv, g_strerror ( errno ) );
        remove_pid_file ( fd );
        return -1;
    }
    if ( ftruncate ( fd, (off_t) 0 ) == 0 ) {
        // Write pid, not needed, but for completeness sake.
        char    buffer[64];
        int     length = snprintf ( buffer, 64, "%i", getpid () );
        ssize_t l      = 0;
        while ( l < length ) {
            l += write ( fd, &buffer[l], length - l );
        }
    }
    return fd;
}