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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pSnmpUtilAsnAnyCpy ; 
 void* pSnmpUtilAsnAnyFree ; 
 void* pSnmpUtilOctetsCmp ; 
 void* pSnmpUtilOctetsCpy ; 
 void* pSnmpUtilOctetsFree ; 
 void* pSnmpUtilOctetsNCmp ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    HMODULE hSnmpapi = GetModuleHandleA("snmpapi.dll");

#define SNMPAPI_GET_PROC(func) \
    p ## func = (void*)GetProcAddress(hSnmpapi, #func); \
    if(!p ## func) \
      trace("GetProcAddress(%s) failed\n", #func);

    SNMPAPI_GET_PROC(SnmpUtilAsnAnyCpy)
    SNMPAPI_GET_PROC(SnmpUtilAsnAnyFree)
    SNMPAPI_GET_PROC(SnmpUtilOctetsCmp)
    SNMPAPI_GET_PROC(SnmpUtilOctetsCpy)
    SNMPAPI_GET_PROC(SnmpUtilOctetsFree)
    SNMPAPI_GET_PROC(SnmpUtilOctetsNCmp)

#undef SNMPAPI_GET_PROC
}