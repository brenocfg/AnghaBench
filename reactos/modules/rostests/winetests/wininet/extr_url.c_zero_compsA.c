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
struct TYPE_4__ {int dwStructSize; void* dwExtraInfoLength; void* dwUrlPathLength; void* dwPasswordLength; void* dwUserNameLength; void* dwHostNameLength; void* dwSchemeLength; } ;
typedef  TYPE_1__ URL_COMPONENTSA ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static void zero_compsA(
    URL_COMPONENTSA *dst, 
    DWORD scheLen,
    DWORD hostLen,
    DWORD userLen,
    DWORD passLen,
    DWORD pathLen,
    DWORD extrLen )
{
    ZeroMemory(dst, sizeof(URL_COMPONENTSA));
    dst->dwStructSize = sizeof(URL_COMPONENTSA);
    dst->dwSchemeLength    = scheLen;
    dst->dwHostNameLength  = hostLen;
    dst->dwUserNameLength  = userLen;
    dst->dwPasswordLength  = passLen;
    dst->dwUrlPathLength   = pathLen;
    dst->dwExtraInfoLength = extrLen;
    SetLastError(0xfaceabad);
}