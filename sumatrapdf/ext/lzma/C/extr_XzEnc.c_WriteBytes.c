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
typedef  scalar_t__ UInt32 ;
struct TYPE_4__ {scalar_t__ (* Write ) (TYPE_1__*,void const*,scalar_t__) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISeqOutStream ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_ERROR_WRITE ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ stub1 (TYPE_1__*,void const*,scalar_t__) ; 

__attribute__((used)) static SRes WriteBytes(ISeqOutStream *s, const void *buf, UInt32 size)
{
  return (s->Write(s, buf, size) == size) ? SZ_OK : SZ_ERROR_WRITE;
}