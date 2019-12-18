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
struct ident {char const* email; char const* name; } ;
typedef  enum author { ____Placeholder_author } author ;

/* Variables and functions */
 int AUTHOR_ABBREVIATED ; 
 int AUTHOR_EMAIL ; 
 int AUTHOR_EMAIL_USER ; 
 int AUTHOR_NO ; 
 int author_trim (int) ; 
 char const* get_author_initials (char const*) ; 
 char const* get_email_user (char const*) ; 

const char *
mkauthor(const struct ident *ident, int cols, enum author author)
{
	bool trim = author_trim(cols);
	bool abbreviate = author == AUTHOR_ABBREVIATED || !trim;

	if (author == AUTHOR_NO || !ident)
		return "";
	if (author == AUTHOR_EMAIL && ident->email)
		return ident->email;
	if (author == AUTHOR_EMAIL_USER && ident->email)
		return get_email_user(ident->email);
	if (abbreviate && ident->name)
		return get_author_initials(ident->name);
	return ident->name;
}