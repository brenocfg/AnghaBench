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
typedef  int /*<<< orphan*/  pdf_obj ;

/* Variables and functions */
 int /*<<< orphan*/  CCF ; 
 int /*<<< orphan*/  CCITTFaxDecode ; 
 int /*<<< orphan*/  DCT ; 
 int /*<<< orphan*/  DCTDecode ; 
 int /*<<< orphan*/  JBIG2Decode ; 
 int /*<<< orphan*/  JPXDecode ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RL ; 
 int /*<<< orphan*/  RunLengthDecode ; 

__attribute__((used)) static int is_image_filter(pdf_obj *s)
{
	return
		s == PDF_NAME(CCITTFaxDecode) || s == PDF_NAME(CCF) ||
		s == PDF_NAME(DCTDecode) || s == PDF_NAME(DCT) ||
		s == PDF_NAME(RunLengthDecode) || s == PDF_NAME(RL) ||
		s == PDF_NAME(JBIG2Decode) ||
		s == PDF_NAME(JPXDecode);
}