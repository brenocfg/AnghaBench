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
typedef  int /*<<< orphan*/  rb_encoding ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int get_option_value (int /*<<< orphan*/ *,long*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rb_enc_find (char*) ; 
 int /*<<< orphan*/  rb_enc_str_new (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_str_new2 (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VALUE
vim_str2rb_enc_str(const char *s)
{
#ifdef RUBY19_OR_LATER
    int isnum;
    long lval;
    char_u *sval;
    rb_encoding *enc;

    isnum = get_option_value((char_u *)"enc", &lval, &sval, 0);
    if (isnum == 0)
    {
	enc = rb_enc_find((char *)sval);
	vim_free(sval);
	if (enc) {
	    return rb_enc_str_new(s, strlen(s), enc);
	}
    }
#endif
    return rb_str_new2(s);
}