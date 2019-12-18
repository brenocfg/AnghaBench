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
struct TYPE_4__ {scalar_t__ fd; void* path; } ;
typedef  TYPE_1__ sqliterk_file ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int SQLITERK_CANTOPEN ; 
 int SQLITERK_MISUSE ; 
 int SQLITERK_NOMEM ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ open (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliterkOSClose (TYPE_1__*) ; 
 int /*<<< orphan*/  sqliterkOSError (int,char*,int,...) ; 
 void* sqliterkOSMalloc (size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (void*,char const*,size_t) ; 

int sqliterkOSReadOnlyOpen(const char *path, sqliterk_file **file)
{
    if (!path || !path[0] || !file) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    sqliterk_file *theFile = sqliterkOSMalloc(sizeof(sqliterk_file));
    if (!theFile) {
        rc = SQLITERK_NOMEM;
        sqliterkOSError(rc, "Not enough memory, required %zu bytes.",
                        sizeof(sqliterk_file));
        goto sqliterkOSReadOnlyOpen_Failed;
    }

    size_t len = sizeof(char) * (strlen(path) + 1);
    theFile->path = sqliterkOSMalloc(len);
    if (!theFile->path) {
        rc = SQLITERK_NOMEM;
        sqliterkOSError(rc, "Not enough memory, required %zu bytes.", len);
        goto sqliterkOSReadOnlyOpen_Failed;
    }
    strncpy(theFile->path, path, len);

    // Open the file in read-only mode, since we do not intend to modify it
    theFile->fd = open(theFile->path, O_RDONLY);
    if (theFile->fd < 0) {
        rc = SQLITERK_CANTOPEN;
        sqliterkOSError(rc, "Cannot open '%s' for reading: %s", theFile->path,
                        strerror(errno));
        goto sqliterkOSReadOnlyOpen_Failed;
    }
    *file = theFile;
    return SQLITERK_OK;

sqliterkOSReadOnlyOpen_Failed:
    if (theFile) {
        sqliterkOSClose(theFile);
    }
    *file = NULL;
    return rc;
}