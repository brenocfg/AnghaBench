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
struct BlobReader {scalar_t__ current; TYPE_1__* blob; } ;
struct TYPE_2__ {scalar_t__ cbData; scalar_t__ pbData; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL read_blob_wrapper(void *handle, void *buffer, DWORD bytesToRead,
 DWORD *bytesRead)
{
    struct BlobReader *reader = handle;
    BOOL ret;

    if (reader->current < reader->blob->cbData)
    {
        *bytesRead = min(bytesToRead, reader->blob->cbData - reader->current);
        memcpy(buffer, reader->blob->pbData + reader->current, *bytesRead);
        reader->current += *bytesRead;
        ret = TRUE;
    }
    else if (reader->current == reader->blob->cbData)
    {
        *bytesRead = 0;
        ret = TRUE;
    }
    else
        ret = FALSE;
    return ret;
}