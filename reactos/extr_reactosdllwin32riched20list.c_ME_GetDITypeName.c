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
typedef  int ME_DIType ;

/* Variables and functions */
#define  diCell 133 
#define  diParagraph 132 
#define  diRun 131 
#define  diStartRow 130 
#define  diTextEnd 129 
#define  diTextStart 128 

__attribute__((used)) static const char *ME_GetDITypeName(ME_DIType type)
{
  switch(type)
  {
    case diParagraph: return "diParagraph";
    case diRun: return "diRun";
    case diCell: return "diCell";
    case diTextStart: return "diTextStart";
    case diTextEnd: return "diTextEnd";
    case diStartRow: return "diStartRow";
    default: return "?";
  }
}