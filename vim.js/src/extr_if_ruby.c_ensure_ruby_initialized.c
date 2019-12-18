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

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtInitialize (int*,char***) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ ruby_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ruby_init () ; 
 int /*<<< orphan*/  ruby_init_loadpath () ; 
 int /*<<< orphan*/  ruby_init_stack (int /*<<< orphan*/ ) ; 
 int ruby_initialized ; 
 int /*<<< orphan*/  ruby_io_init () ; 
 int /*<<< orphan*/  ruby_process_options (int,char**) ; 
 int /*<<< orphan*/  ruby_script (char*) ; 
 int /*<<< orphan*/  ruby_stack_start ; 
 int /*<<< orphan*/  ruby_vim_init () ; 

__attribute__((used)) static int ensure_ruby_initialized(void)
{
    if (!ruby_initialized)
    {
#ifdef DYNAMIC_RUBY
	if (ruby_enabled(TRUE))
	{
#endif
#ifdef _WIN32
	    /* suggested by Ariya Mizutani */
	    int argc = 1;
	    char *argv[] = {"gvim.exe"};
	    NtInitialize(&argc, &argv);
#endif
	    {
#if defined(RUBY19_OR_LATER) || defined(RUBY_INIT_STACK)
		ruby_init_stack(ruby_stack_start);
#endif
		ruby_init();
	    }
#ifdef RUBY19_OR_LATER
	    {
		int dummy_argc = 2;
		char *dummy_argv[] = {"vim-ruby", "-e0"};
		ruby_process_options(dummy_argc, dummy_argv);
	    }
	    ruby_script("vim-ruby");
#else
	    ruby_init_loadpath();
#endif
	    ruby_io_init();
	    ruby_vim_init();
	    ruby_initialized = 1;
#ifdef DYNAMIC_RUBY
	}
	else
	{
	    EMSG(_("E266: Sorry, this command is disabled, the Ruby library could not be loaded."));
	    return 0;
	}
#endif
    }
    return ruby_initialized;
}