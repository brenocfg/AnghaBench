#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t fill; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ mpg123_string ;

/* Variables and functions */
 int /*<<< orphan*/  debug1 (char*,unsigned long) ; 
 int /*<<< orphan*/  mpg123_free_string (TYPE_1__*) ; 
 int /*<<< orphan*/  mpg123_resize_string (TYPE_1__*,size_t) ; 

__attribute__((used)) static void convert_latin1(mpg123_string *sb, const unsigned char* s, size_t l, const int noquiet)
{
	size_t length = l;
	size_t i;
	unsigned char *p;
	/* determine real length, a latin1 character can at most take 2  in UTF8 */
	for(i=0; i<l; ++i)
	if(s[i] >= 0x80) ++length;

	debug1("UTF-8 length: %lu", (unsigned long)length);
	/* one extra zero byte for paranoia */
	if(!mpg123_resize_string(sb, length+1)){ mpg123_free_string(sb); return ; }

	p = (unsigned char*) sb->p; /* Signedness doesn't matter but it shows I thought about the non-issue */
	for(i=0; i<l; ++i)
	if(s[i] < 0x80){ *p = s[i]; ++p; }
	else /* two-byte encoding */
	{
		*p     = 0xc0 | (s[i]>>6);
		*(p+1) = 0x80 | (s[i] & 0x3f);
		p+=2;
	}

	sb->p[length] = 0;
	sb->fill = length+1;
}