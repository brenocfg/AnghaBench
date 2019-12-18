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
 char const* StringValuePtr (int /*<<< orphan*/ ) ; 
 int get_option_value (int /*<<< orphan*/ *,long*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rb_enc_find (char*) ; 
 int /*<<< orphan*/  rb_enc_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_eval_string_protect (char const*,int*) ; 
 int /*<<< orphan*/  rb_sprintf (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VALUE
eval_enc_string_protect(const char *str, int *state)
{
#ifdef RUBY19_OR_LATER
    int isnum;
    long lval;
    char_u *sval;
    rb_encoding *enc;
    VALUE v;

    isnum = get_option_value((char_u *)"enc", &lval, &sval, 0);
    if (isnum == 0)
    {
	enc = rb_enc_find((char *)sval);
	vim_free(sval);
	if (enc)
	{
	    v = rb_sprintf("#-*- coding:%s -*-\n%s", rb_enc_name(enc), str);
	    return rb_eval_string_protect(StringValuePtr(v), state);
	}
    }
#endif
    return rb_eval_string_protect(str, state);
}