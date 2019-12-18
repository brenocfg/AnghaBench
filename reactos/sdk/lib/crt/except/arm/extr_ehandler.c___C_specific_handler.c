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
struct _EXCEPTION_RECORD {int dummy; } ;
struct _DISPATCHER_CONTEXT {int dummy; } ;
struct _CONTEXT {int dummy; } ;
typedef  int /*<<< orphan*/  __cdecl ;

/* Variables and functions */
 int /*<<< orphan*/  UNIMPLEMENTED ; 
 int /*<<< orphan*/  __debugbreak () ; 

__cdecl
__C_specific_handler(
    struct _EXCEPTION_RECORD *_ExceptionRecord,
    void *_EstablisherFrame,
    struct _CONTEXT *_ContextRecord,
    struct _DISPATCHER_CONTEXT *_DispatcherContext)
{
    UNIMPLEMENTED;
    __debugbreak();
    return 0;
}