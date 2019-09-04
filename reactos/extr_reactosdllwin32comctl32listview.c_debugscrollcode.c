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
typedef  char* LPCSTR ;

/* Variables and functions */
#define  SB_ENDSCROLL 135 
#define  SB_INTERNAL 134 
#define  SB_LINELEFT 133 
#define  SB_LINERIGHT 132 
#define  SB_PAGELEFT 131 
#define  SB_PAGERIGHT 130 
#define  SB_THUMBPOSITION 129 
#define  SB_THUMBTRACK 128 

__attribute__((used)) static inline LPCSTR debugscrollcode(int nScrollCode)
{
  switch(nScrollCode)
  {
  case SB_LINELEFT: return "SB_LINELEFT";
  case SB_LINERIGHT: return "SB_LINERIGHT";
  case SB_PAGELEFT: return "SB_PAGELEFT";
  case SB_PAGERIGHT: return "SB_PAGERIGHT";
  case SB_THUMBPOSITION: return "SB_THUMBPOSITION";
  case SB_THUMBTRACK: return "SB_THUMBTRACK";
  case SB_ENDSCROLL: return "SB_ENDSCROLL";
  case SB_INTERNAL: return "SB_INTERNAL";
  default: return "unknown";
  }
}