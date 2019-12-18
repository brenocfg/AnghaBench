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
typedef  int /*<<< orphan*/  UInt64 ;
struct TYPE_4__ {int /*<<< orphan*/  (* Seek ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  Int64 ;
typedef  TYPE_1__ ILookInStream ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_SEEK_SET ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SRes LookInStream_SeekTo(ILookInStream *stream, UInt64 offset)
{
  Int64 t = offset;
  return stream->Seek(stream, &t, SZ_SEEK_SET);
}