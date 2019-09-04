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
typedef  int BOOL ;

/* Variables and functions */
 int diParagraph ; 
#define  diParagraphOrEnd 133 
 int diRun ; 
#define  diRunOrParagraph 132 
#define  diRunOrParagraphOrEnd 131 
#define  diRunOrStartRow 130 
 int diStartRow ; 
#define  diStartRowOrParagraph 129 
#define  diStartRowOrParagraphOrEnd 128 
 int diTextEnd ; 

__attribute__((used)) static BOOL ME_DITypesEqual(ME_DIType type, ME_DIType nTypeOrClass)
{
  switch (nTypeOrClass)
  {
    case diRunOrParagraph:
      return type == diRun || type == diParagraph;
    case diRunOrStartRow:
      return type == diRun || type == diStartRow;
    case diParagraphOrEnd:
      return type == diTextEnd || type == diParagraph;
    case diStartRowOrParagraph:
      return type == diStartRow || type == diParagraph;
    case diStartRowOrParagraphOrEnd:
      return type == diStartRow || type == diParagraph || type == diTextEnd;
    case diRunOrParagraphOrEnd:
      return type == diRun || type == diParagraph || type == diTextEnd;
    default:
      return type == nTypeOrClass;
  }
}