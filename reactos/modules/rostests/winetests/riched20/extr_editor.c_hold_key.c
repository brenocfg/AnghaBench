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
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int GetKeyboardState (int*) ; 
 int SetKeyboardState (int*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static BOOL hold_key(int vk)
{
  BYTE key_state[256];
  BOOL result;

  result = GetKeyboardState(key_state);
  ok(result, "GetKeyboardState failed.\n");
  if (!result) return FALSE;
  key_state[vk] |= 0x80;
  result = SetKeyboardState(key_state);
  ok(result, "SetKeyboardState failed.\n");
  return result != 0;
}