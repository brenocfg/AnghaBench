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
typedef  char* LPVOID ;
typedef  char* LPTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_PIPE_BUSY ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MyErrExit (char*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ PIPE_READMODE_MESSAGE ; 
 scalar_t__ ReadFile (scalar_t__,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 scalar_t__ SetNamedPipeHandleState (scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitNamedPipe (char*,int) ; 
 scalar_t__ WriteFile (scalar_t__,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

int main(int argc, char *argv[])
{
   HANDLE hPipe;
   LPVOID lpvMessage;
   CHAR chBuf[512];
   BOOL fSuccess;
   DWORD cbRead, cbWritten, dwMode;
   LPTSTR lpszPipename = "\\\\.\\pipe\\mynamedpipe";

// Try to open a named pipe; wait for it, if necessary.

   while (1)
   {
      hPipe = CreateFile(
         lpszPipename,   // pipe name
         GENERIC_READ |  // read and write access
         GENERIC_WRITE,
         0,              // no sharing
         NULL,           // no security attributes
         OPEN_EXISTING,  // opens existing pipe
         0,              // default attributes
         NULL);          // no template file

   // Break if the pipe handle is valid.

      if (hPipe != INVALID_HANDLE_VALUE)
         break;

      // Exit if an error other than ERROR_PIPE_BUSY occurs.

      if (GetLastError() != ERROR_PIPE_BUSY)
         MyErrExit("Could not open pipe");

      // All pipe instances are busy, so wait for 20 seconds.

      if (! WaitNamedPipe(lpszPipename, 20000) )
         MyErrExit("Could not open pipe");
   }

// The pipe connected; change to message-read mode.

   dwMode = PIPE_READMODE_MESSAGE;
   fSuccess = SetNamedPipeHandleState(
      hPipe,    // pipe handle
      &dwMode,  // new pipe mode
      NULL,     // don't set maximum bytes
      NULL);    // don't set maximum time
   if (!fSuccess)
      MyErrExit("SetNamedPipeHandleState");

// Send a message to the pipe server.

   lpvMessage = (argc > 1) ? argv[1] : "default message";

   fSuccess = WriteFile(
      hPipe,                  // pipe handle
      lpvMessage,             // message
      strlen(lpvMessage) + 1, // message length
      &cbWritten,             // bytes written
      NULL);                  // not overlapped
   if (! fSuccess)
      MyErrExit("WriteFile");

   do
   {
   // Read from the pipe.

      fSuccess = ReadFile(
         hPipe,    // pipe handle
         chBuf,    // buffer to receive reply
         512,      // size of buffer
         &cbRead,  // number of bytes read
         NULL);    // not overlapped

      if (! fSuccess && GetLastError() != ERROR_MORE_DATA)
         break;

      // Reply from the pipe is written to STDOUT.

      if (! WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),
         chBuf, cbRead, &cbWritten, NULL))
      {
         break;
      }

   } while (! fSuccess);  // repeat loop if ERROR_MORE_DATA

   CloseHandle(hPipe);

   return 0;
}