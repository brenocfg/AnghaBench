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
struct TYPE_6__ {int strings_size; int /*<<< orphan*/ ** strings; int /*<<< orphan*/  strings_stream; } ;
struct TYPE_5__ {int QuadPart; } ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_2__ CHMInfo ;

/* Variables and functions */
 int BLOCK_BITS ; 
 int BLOCK_MASK ; 
 int /*<<< orphan*/  BLOCK_SIZE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** heap_realloc_zero (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static LPCSTR GetChmString(CHMInfo *chm, DWORD offset)
{
    LPCSTR str;

    if(!chm->strings_stream)
        return NULL;

    if(chm->strings_size <= (offset >> BLOCK_BITS)) {
        chm->strings_size = (offset >> BLOCK_BITS)+1;
        if(chm->strings)
            chm->strings = heap_realloc_zero(chm->strings,
                    chm->strings_size*sizeof(char*));
        else
            chm->strings = heap_alloc_zero(
                    chm->strings_size*sizeof(char*));

    }

    if(!chm->strings[offset >> BLOCK_BITS]) {
        LARGE_INTEGER pos;
        DWORD read;
        HRESULT hres;

        pos.QuadPart = offset & ~BLOCK_MASK;
        hres = IStream_Seek(chm->strings_stream, pos, STREAM_SEEK_SET, NULL);
        if(FAILED(hres)) {
            WARN("Seek failed: %08x\n", hres);
            return NULL;
        }

        chm->strings[offset >> BLOCK_BITS] = heap_alloc(BLOCK_SIZE);

        hres = IStream_Read(chm->strings_stream, chm->strings[offset >> BLOCK_BITS],
                            BLOCK_SIZE, &read);
        if(FAILED(hres)) {
            WARN("Read failed: %08x\n", hres);
            heap_free(chm->strings[offset >> BLOCK_BITS]);
            chm->strings[offset >> BLOCK_BITS] = NULL;
            return NULL;
        }
    }

    str = chm->strings[offset >> BLOCK_BITS] + (offset & BLOCK_MASK);
    TRACE("offset %#x => %s\n", offset, debugstr_a(str));
    return str;
}