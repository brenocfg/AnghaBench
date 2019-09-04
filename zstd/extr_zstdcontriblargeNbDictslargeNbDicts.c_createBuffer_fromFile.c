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
struct TYPE_6__ {scalar_t__ size; scalar_t__ capacity; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ buffer_t ;
typedef  scalar_t__ U64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL (int) ; 
 scalar_t__ const UTIL_FILESIZE_UNKNOWN ; 
 scalar_t__ UTIL_getFileSize (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ createBuffer (size_t const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  fillBuffer_fromHandle (TYPE_1__*,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 TYPE_1__ kBuffNull ; 

__attribute__((used)) static buffer_t createBuffer_fromFile(const char* fileName)
{
    U64 const fileSize = UTIL_getFileSize(fileName);
    size_t const bufferSize = (size_t) fileSize;

    if (fileSize == UTIL_FILESIZE_UNKNOWN) return kBuffNull;
    assert((U64)bufferSize == fileSize);   /* check overflow */

    {   FILE* const f = fopen(fileName, "rb");
        if (f == NULL) return kBuffNull;

        buffer_t buff = createBuffer(bufferSize);
        CONTROL(buff.ptr != NULL);

        fillBuffer_fromHandle(&buff, f);
        CONTROL(buff.size == buff.capacity);

        fclose(f);   /* do nothing specific if fclose() fails */
        return buff;
    }
}