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
struct TYPE_9__ {int /*<<< orphan*/ * recv_seal_key; int /*<<< orphan*/ * recv_sign_key; int /*<<< orphan*/ * send_seal_key; int /*<<< orphan*/ * send_sign_key; int /*<<< orphan*/ * recv_a4i; int /*<<< orphan*/ * send_a4i; } ;
struct TYPE_8__ {int /*<<< orphan*/ * a4i; } ;
struct TYPE_10__ {TYPE_2__ ntlm2; TYPE_1__ ntlm; } ;
struct TYPE_11__ {int helper_pid; int major; int minor; int micro; int pipe_in; int pipe_out; TYPE_3__ crypt; scalar_t__ neg_flags; int /*<<< orphan*/ * session_key; scalar_t__ com_buf_offset; scalar_t__ com_buf_size; int /*<<< orphan*/ * com_buf; } ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  TYPE_4__* PNegoHelper ;
typedef  int /*<<< orphan*/  NegoHelper ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SEC_E_INSUFFICIENT_MEMORY ; 
 int /*<<< orphan*/  SEC_E_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debugstr_a (char* const) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execvp (char const*,char* const*) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fork () ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

SECURITY_STATUS fork_helper(PNegoHelper *new_helper, const char *prog,
        char* const argv[])
{
    int pipe_in[2];
    int pipe_out[2];
#ifdef __REACTOS__
    HANDLE hPipe;
    PROCESS_INFORMATION pi;
    STARTUPINFOA si;
    char* cmdline;
#endif
    int i;
    PNegoHelper helper;

    TRACE("%s ", debugstr_a(prog));
    for(i = 0; argv[i] != NULL; ++i)
    {
        TRACE("%s ", debugstr_a(argv[i]));
    }
    TRACE("\n");

#ifndef __REACTOS__

#ifdef HAVE_PIPE2
    if (pipe2( pipe_in, O_CLOEXEC ) < 0 )
#endif
    {
        if( pipe(pipe_in) < 0 ) return SEC_E_INTERNAL_ERROR;
        fcntl( pipe_in[0], F_SETFD, FD_CLOEXEC );
        fcntl( pipe_in[1], F_SETFD, FD_CLOEXEC );
    }
#ifdef HAVE_PIPE2
    if (pipe2( pipe_out, O_CLOEXEC ) < 0 )
#endif
    {
        if( pipe(pipe_out) < 0 )
        {
            close(pipe_in[0]);
            close(pipe_in[1]);
            return SEC_E_INTERNAL_ERROR;
        }
        fcntl( pipe_out[0], F_SETFD, FD_CLOEXEC );
        fcntl( pipe_out[1], F_SETFD, FD_CLOEXEC );
    }

#else

    if (_pipe(pipe_in, 0, _O_BINARY /* _O_TEXT */ | _O_NOINHERIT) < 0)
    {
        return SEC_E_INTERNAL_ERROR;
    }

    if (_pipe(pipe_out, 0, _O_BINARY /* _O_TEXT */ | _O_NOINHERIT) < 0)
    {
        close(pipe_in[0]);
        close(pipe_in[1]);
        return SEC_E_INTERNAL_ERROR;
    }

#endif

    if (!(helper = HeapAlloc(GetProcessHeap(),0, sizeof(NegoHelper))))
    {
        close(pipe_in[0]);
        close(pipe_in[1]);
        close(pipe_out[0]);
        close(pipe_out[1]);
        return SEC_E_INSUFFICIENT_MEMORY;
    }

#ifndef __REACTOS__
    helper->helper_pid = fork();
#else

    cmdline = flatten_cmdline(prog, argv);
    if (!cmdline)
    {
        close(pipe_in[0]);
        close(pipe_in[1]);
        close(pipe_out[0]);
        close(pipe_out[1]);
        HeapFree( GetProcessHeap(), 0, helper );
        return SEC_E_INSUFFICIENT_MEMORY;
    }

    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    si.dwFlags |= STARTF_USESTDHANDLES;

    /* The reading side of the pipe is STDIN for this process */
    hPipe = (HANDLE)_get_osfhandle(pipe_out[0]);
    SetHandleInformation(hPipe, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    si.hStdInput = hPipe;

    /* The writing side of the pipe is STDOUT for this process */
    hPipe = (HANDLE)_get_osfhandle(pipe_in[1]);
    SetHandleInformation(hPipe, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    si.hStdOutput = hPipe;
    si.hStdError  = hPipe;

    if (!CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
        /* We fail just afterwards */
        helper->helper_pid = (HANDLE)-1;
    }
    else
    {
        helper->helper_pid = pi.hProcess;
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    HeapFree( GetProcessHeap(), 0, cmdline );

#endif

#ifndef __REACTOS__
    if(helper->helper_pid == -1)
#else
    if(helper->helper_pid == (HANDLE)-1)
#endif
    {
        close(pipe_in[0]);
        close(pipe_in[1]);
        close(pipe_out[0]);
        close(pipe_out[1]);
        HeapFree( GetProcessHeap(), 0, helper );
        return SEC_E_INTERNAL_ERROR;
    }

#ifndef __REACTOS__
    if(helper->helper_pid == 0)
    {
        /* We're in the child now */
        dup2(pipe_out[0], 0);
        close(pipe_out[0]);
        close(pipe_out[1]);

        dup2(pipe_in[1], 1);
        close(pipe_in[0]);
        close(pipe_in[1]);

        execvp(prog, argv);

        /* Whoops, we shouldn't get here. Big badaboom.*/
        write(STDOUT_FILENO, "BH\n", 3);
        _exit(1);
    }
    else
#endif
    {
        *new_helper = helper;
        helper->major = helper->minor = helper->micro = -1;
        helper->com_buf = NULL;
        helper->com_buf_size = 0;
        helper->com_buf_offset = 0;
        helper->session_key = NULL;
        helper->neg_flags = 0;
        helper->crypt.ntlm.a4i = NULL;
        helper->crypt.ntlm2.send_a4i = NULL;
        helper->crypt.ntlm2.recv_a4i = NULL;
        helper->crypt.ntlm2.send_sign_key = NULL;
        helper->crypt.ntlm2.send_seal_key = NULL;
        helper->crypt.ntlm2.recv_sign_key = NULL;
        helper->crypt.ntlm2.recv_seal_key = NULL;
        helper->pipe_in = pipe_in[0];   // Keep in(read)
        close(pipe_in[1]);              // Close in(write)
        helper->pipe_out = pipe_out[1]; // Keep out(write)
        close(pipe_out[0]);             // Close out(read)
    }

    return SEC_E_OK;
}