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
struct TYPE_5__ {int size; int fill; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ mpg123_string ;

/* Variables and functions */
 unsigned long FULLPOINT (unsigned long,unsigned short) ; 
 scalar_t__ UTF8LEN (unsigned long) ; 
 int check_bom (unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  debug1 (char*,int) ; 
 int /*<<< orphan*/  error2 (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mpg123_free_string (TYPE_1__*) ; 
 int /*<<< orphan*/  mpg123_resize_string (TYPE_1__*,size_t) ; 

__attribute__((used)) static void convert_utf16bom(mpg123_string *sb, const unsigned char* s, size_t l, const int noquiet)
{
	size_t i;
	size_t n; /* number bytes that make up full pairs */
	unsigned char *p;
	size_t length = 0; /* the resulting UTF-8 length */
	/* Determine real length... extreme case can be more than utf-16 length. */
	size_t high = 0;
	size_t low  = 1;
	int bom_endian;

	debug1("convert_utf16 with length %lu", (unsigned long)l);

	bom_endian = check_bom(&s, &l);
	debug1("UTF16 endianness check: %i", bom_endian);

	if(bom_endian == -1) /* little-endian */
	{
		high = 1; /* The second byte is the high byte. */
		low  = 0; /* The first byte is the low byte. */
	}

	n = (l/2)*2; /* number bytes that make up full pairs */

	/* first: get length, check for errors -- stop at first one */
	for(i=0; i < n; i+=2)
	{
		unsigned long point = ((unsigned long) s[i+high]<<8) + s[i+low];
		if((point & 0xfc00) == 0xd800) /* lead surrogate */
		{
			unsigned short second = (i+3 < l) ? (s[i+2+high]<<8) + s[i+2+low] : 0;
			if((second & 0xfc00) == 0xdc00) /* good... */
			{
				point = FULLPOINT(point,second);
				length += UTF8LEN(point); /* possibly 4 bytes */
				i+=2; /* We overstepped one word. */
			}
			else /* if no valid pair, break here */
			{
				if(noquiet) error2("Invalid UTF16 surrogate pair at %li (0x%04lx).", (unsigned long)i, point);
				n = i; /* Forget the half pair, END! */
				break;
			}
		}
		else length += UTF8LEN(point); /* 1,2 or 3 bytes */
	}

	if(!mpg123_resize_string(sb, length+1)){ mpg123_free_string(sb); return ; }

	/* Now really convert, skip checks as these have been done just before. */
	p = (unsigned char*) sb->p; /* Signedness doesn't matter but it shows I thought about the non-issue */
	for(i=0; i < n; i+=2)
	{
		unsigned long codepoint = ((unsigned long) s[i+high]<<8) + s[i+low];
		if((codepoint & 0xfc00) == 0xd800) /* lead surrogate */
		{
			unsigned short second = (s[i+2+high]<<8) + s[i+2+low];
			codepoint = FULLPOINT(codepoint,second);
			i+=2; /* We overstepped one word. */
		}
		if(codepoint < 0x80) *p++ = (unsigned char) codepoint;
		else if(codepoint < 0x800)
		{
			*p++ = (unsigned char) (0xc0 | (codepoint>>6));
			*p++ = (unsigned char) (0x80 | (codepoint & 0x3f));
		}
		else if(codepoint < 0x10000)
		{
			*p++ = (unsigned char) (0xe0 | (codepoint>>12));
			*p++ = 0x80 | ((codepoint>>6) & 0x3f);
			*p++ = 0x80 | (codepoint & 0x3f);
		}
		else if (codepoint < 0x200000)
		{
			*p++ = (unsigned char) (0xf0 | codepoint>>18);
			*p++ = (unsigned char) (0x80 | ((codepoint>>12) & 0x3f));
			*p++ = (unsigned char) (0x80 | ((codepoint>>6) & 0x3f));
			*p++ = (unsigned char) (0x80 | (codepoint & 0x3f));
		} /* ignore bigger ones (that are not possible here anyway) */
	}
	sb->p[sb->size-1] = 0; /* paranoia... */
	sb->fill = sb->size;
}