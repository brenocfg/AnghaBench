#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iobuf ;
struct TYPE_6__ {int _bufsiz; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _IOFBF ; 
 char* _tempnam (char*,char*) ; 
 int /*<<< orphan*/  fclose (TYPE_1__*) ; 
 TYPE_1__* fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setvbuf (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_write_flush_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_write_flush(void)
{
    char iobuf[1024];
    char *tempf;
    FILE *file;

    tempf = _tempnam(".","wne");
    file = fopen(tempf, "wb+");
    ok(file != NULL, "unable to create test file\n");
    iobuf[0] = 0;
    ok(file->_bufsiz == 4096, "incorrect default buffer size: %d\n", file->_bufsiz);
    test_write_flush_size(file, file->_bufsiz);
    setvbuf(file, iobuf, _IOFBF, sizeof(iobuf));
    test_write_flush_size(file, sizeof(iobuf));
    fclose(file);
    unlink(tempf);
    free(tempf);
}