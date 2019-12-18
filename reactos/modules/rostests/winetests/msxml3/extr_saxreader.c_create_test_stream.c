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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_SetSize (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int strlen (char const*) ; 

__attribute__((used)) static IStream *create_test_stream(const char *data, int len)
{
     ULARGE_INTEGER size;
     LARGE_INTEGER pos;
     IStream *stream;
     ULONG written;

     if (len == -1) len = strlen(data);
     CreateStreamOnHGlobal(NULL, TRUE, &stream);
     size.QuadPart = len;
     IStream_SetSize(stream, size);
     IStream_Write(stream, data, len, &written);
     pos.QuadPart = 0;
     IStream_Seek(stream, pos, STREAM_SEEK_SET, NULL);

     return stream;
}