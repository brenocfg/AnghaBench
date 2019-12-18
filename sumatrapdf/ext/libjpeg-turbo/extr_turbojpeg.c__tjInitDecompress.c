#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  err; } ;
struct TYPE_10__ {int /*<<< orphan*/  output_message; int /*<<< orphan*/  error_exit; } ;
struct TYPE_8__ {int /*<<< orphan*/  setjmp_buffer; TYPE_3__ pub; } ;
struct TYPE_9__ {int /*<<< orphan*/  init; TYPE_4__ dinfo; TYPE_1__ jerr; } ;
typedef  TYPE_2__ tjinstance ;
typedef  int /*<<< orphan*/ * tjhandle ;

/* Variables and functions */
 int /*<<< orphan*/  DECOMPRESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  jpeg_create_decompress (TYPE_4__*) ; 
 int /*<<< orphan*/  jpeg_mem_src_tj (TYPE_4__*,unsigned char*,int) ; 
 int /*<<< orphan*/  jpeg_std_error (TYPE_3__*) ; 
 int /*<<< orphan*/  my_error_exit ; 
 int /*<<< orphan*/  my_output_message ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tjhandle _tjInitDecompress(tjinstance *this)
{
	unsigned char buffer[1];

	/* This is also straight out of example.c */
	this->dinfo.err=jpeg_std_error(&this->jerr.pub);
	this->jerr.pub.error_exit=my_error_exit;
	this->jerr.pub.output_message=my_output_message;

	if(setjmp(this->jerr.setjmp_buffer))
	{
		/* If we get here, the JPEG code has signaled an error. */
		if(this) free(this);  return NULL;
	}

	jpeg_create_decompress(&this->dinfo);
	/* Make an initial call so it will create the source manager */
	jpeg_mem_src_tj(&this->dinfo, buffer, 1);

	this->init|=DECOMPRESS;
	return (tjhandle)this;
}