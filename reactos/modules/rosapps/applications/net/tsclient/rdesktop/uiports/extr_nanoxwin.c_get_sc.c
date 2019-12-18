#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ chs; scalar_t__ ch1; scalar_t__ ch2; scalar_t__ ch3; } ;
struct TYPE_4__ {int modifiers; scalar_t__ ch; } ;
typedef  TYPE_1__ GR_EVENT_KEYSTROKE ;

/* Variables and functions */
 TYPE_3__* g_keys ; 

__attribute__((used)) static int get_sc(GR_EVENT_KEYSTROKE * event_keystroke, int * sc, int * ec)
{
  int i;

  //printf("%d %d\n", event_keystroke->ch, event_keystroke->modifiers);
  *sc = 0;
  *ec = 0;
  for (i = 0; i < 256; i++)
  {
    if (event_keystroke->modifiers & 1) /* shift is down */
    {
      if (event_keystroke->ch == g_keys[i].chs)
      {
        *sc = i;
        break;
      }
    }
    if (event_keystroke->ch == g_keys[i].ch1 ||
        event_keystroke->ch == g_keys[i].ch2 ||
        event_keystroke->ch == g_keys[i].ch3)
    {
      *sc = i;
      break;
    }
  }
  if (*sc == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}