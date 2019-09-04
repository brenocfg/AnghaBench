#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void (* dtor ) (void*) ;struct TYPE_3__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ __mingwthr_key_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mingwthr_cs ; 
 scalar_t__ __mingwthr_cs_init ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_1__* key_dtor_list ; 

int
___w64_mingwthr_add_key_dtor (DWORD key, void (*dtor)(void *))
{
  __mingwthr_key_t *new_key;

  if (__mingwthr_cs_init == 0)
    return 0;
  new_key = (__mingwthr_key_t *) calloc (1, sizeof (__mingwthr_key_t));
  if (new_key == NULL)
    return -1;

  new_key->key = key;
  new_key->dtor = dtor;

  EnterCriticalSection (&__mingwthr_cs);

  new_key->next = key_dtor_list;
  key_dtor_list = new_key;

  LeaveCriticalSection (&__mingwthr_cs);
  return 0;
}