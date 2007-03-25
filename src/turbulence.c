/*  Turbulence:  BEEP application server
 *  Copyright (C) 2007 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; version 2.1 of the
 *  License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *  
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are wellcome to
 *  develop propietary applications using this library withtout any
 *  royalty or fee but returning back any change, improvement or
 *  addition in the form of source code, project image, documentation
 *  patches, etc.
 *
 *  For comercial support on build BEEP enabled solutions, supporting
 *  turbulence based solutions, etc, contact us:
 *          
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         C/ Dr. Michavila N� 14
 *         Coslada 28820 Madrid
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://fact.aspl.es
 */
#include <turbulence.h>
#include <signal.h>

#define HELP_HEADER "Turbulence: BEEP application server\n\
Copyright (C) 2007  Advanced Software Production Line, S.L.\n\n"

#define POST_HEADER "\n\
If you have question, bugs to report, patches, you can reach us\n\
at <vortex@lists.aspl.es>."

/** 
 * @internal Controls if messages must be send to the console log.
 */
bool console_enabled = false;

/** 
 * Starts turbulence execution, initializing all libraries required by
 * the server application.
 *
 * A call to turbulence_exit is required before exit.
 */
bool turbulence_init (int argc, char ** argv)
{
	/*** init exarg library ***/

	/* install headers for help */
	exarg_add_usage_header  (HELP_HEADER);
	exarg_add_help_header   (HELP_HEADER);
	exarg_post_help_header  (POST_HEADER);
	exarg_post_usage_header (POST_HEADER);

	/* install exarg options */
	exarg_install_arg ("config", "f", EXARG_STRING, 
			   "Main server configuration location.");

	exarg_install_arg ("debug", "d", EXARG_NONE,
			   "Makes all log produced by the application, to be also dropped to the console");

	/* install default signal handling */
	signal (SIGINT,  turbulence_exit);
	signal (SIGTERM, turbulence_exit);
	signal (SIGKILL, turbulence_exit);
	signal (SIGQUIT, turbulence_exit);
	signal (SIGSEGV, turbulence_exit);
	signal (SIGABRT, turbulence_exit);
	signal (SIGHUP,  turbulence_reload_config);

	/* call to parse arguments */
	exarg_parse (argc, argv);

	/* check if the console is defined */
	console_enabled = exarg_is_defined ("debug");

	/*** init the vortex library ***/
	if (! vortex_init ()) {
		error ("unable to start vortex library, terminating turbulence execution..");
		return false;
	} /* end if */

	/*** not required to initialize axl library, already done by vortex ***/
	
	msg ("turbulence internal init");
	turbulence_module_init ();

	/* init ok */
	return true;
} /* end if */

/** 
 * @internal Function that performs a reload operation for the current
 * turbulence instance.
 * 
 * @param value The signal number caught.
 */
void turbulence_reload_config (int value)
{
	msg ("caught HUP signal, reloading configuration (FIXME!)");
	
	return;
} 

/** 
 * Terminates the turbulence excution, returing the exit value
 * provided as first parameter.
 * 
 * @param value The exit code to return.
 */
void turbulence_exit (int value)
{
	
	
	switch (value) {
	case SIGINT:
		msg ("caught SIGINT, terminating turbulence..");
		break;
	case SIGTERM:
		msg ("caught SIGTERM, terminating turbulence..");
		break;
	case SIGKILL:
		msg ("caught SIGKILL, terminating turbulence..");
		break;
	case SIGQUIT:
		msg ("caught SIGQUIT, terminating turbulence..");
		break;
	case SIGSEGV:
		msg ("caught SIGSEV, anomalous termination (this is an internal turbulence or module error)");
		break;
	case SIGABRT:
		msg ("caught SIGABRT, anomalous termination (this is an internal turbulence or module error)");
		break;
	default:
		msg ("terminating turbulence..");
		break;
	} /* end if */

	/* terminate all modules */
	turbulence_module_cleanup ();
	turbulence_config_cleanup ();
	

	/* terminate vortex */
	msg ("terminating vortex library..");
	vortex_exit ();
	
	/* terminate exarg */
	msg ("terminating exarg library..");
	exarg_end ();

	/* the last module to clean up */
	turbulence_log_cleanup ();

	/* terminate */
	exit (value);

	return;
}

/** 
 * @internal Simple macro to check if the console output is activated
 * or not.
 */
#define CONSOLE if (console_enabled) fprintf

/** 
 * @internal Simple macro to check if the console output is activated
 * or not.
 */
#define CONSOLEV if (console_enabled) vfprintf
    

/** 
 * @internal function that actually handles the console error.
 */
void __error (const char * file, int line, const char * format, ...)
{
	va_list args;
	
	CONSOLE (stderr, "[ error ] (%s:%d) ", file, line);
	
	va_start (args, format);

	/* report to the console */
	CONSOLEV (stderr, format, args);

	/* report to log */
	turbulence_log_report (LOG_REPORT_ERROR | LOG_REPORT_GENERAL, format, args, file, line);
	
	va_end (args);

	CONSOLE (stderr, "\n");
	
	fflush (stderr);
	
	return;
}

/** 
 * @internal function that actually handles the console msg.
 */
void __msg (const char * file, int line, const char * format, ...)
{
	va_list args;
	
	CONSOLE (stdout, "[  msg  ] (%s:%d) ", file, line);
	
	va_start (args, format);
	
	/* report to console */
	CONSOLEV (stdout, format, args);

	/* report to log */
	turbulence_log_report (LOG_REPORT_GENERAL, format, args, file, line);

	va_end (args);

	CONSOLE (stdout, "\n");
	
	fflush (stdout);
	
	return;
}

/** 
 * @internal function that actually handles the console wrn.
 */
void __wrn (const char * file, int line, const char * format, ...)
{
	va_list args;
	
	CONSOLE (stdout, "[  !!!  ] (%s:%d) ", file, line);
	
	va_start (args, format);

	CONSOLEV (stdout, format, args);

	/* report to log */
	turbulence_log_report (LOG_REPORT_ERROR | LOG_REPORT_GENERAL, format, args, file, line);

	va_end (args);

	CONSOLE (stdout, "\n");
	
	fflush (stdout);
	
	return;
}

/** 
 * @brief Provides the same functionality like \ref turbulence_file_test,
 * but allowing to provide the file path as a printf like argument.
 * 
 * @param format The path to be checked.
 * @param test The test to be performed. 
 * 
 * @return true if all test returns true. Otherwise false is returned.
 */
bool turbulence_file_test_v (const char * format, FileTest test, ...)
{
	va_list   args;
	char    * path;
	bool      result;

	/* open arguments */
	va_start (args, test);

	/* get the path */
	path = axl_strdup_printfv (format, args);

	/* close args */
	va_end (args);

	/* do the test */
	result = turbulence_file_test (path, test);
	axl_free (path);

	/* return the test */
	return result;
}


/** 
 * @brief Allows to perform a set of test for the provided path.
 * 
 * @param path The path that will be checked.
 *
 * @param test The set of test to be performed. Separate each test
 * with "|" to perform several test at the same time.
 * 
 * @return true if all test returns true. Otherwise false is returned.
 */
bool   turbulence_file_test (const char * path, FileTest test)
{
	bool result = false;
	struct stat file_info;

	/* perform common checks */
	axl_return_val_if_fail (path, false);

	/* call to get status */
	result = (stat (path, &file_info) == 0);
	if (! result) {
		/* check that it is requesting for not file exists */
		if (errno == ENOENT && (test & FILE_EXISTS) == FILE_EXISTS)
			return false;

		error ("filed to check test on %s, stat call has failed (result=%d, error=%s)", path, result, strerror (errno));
		return false;
	} /* end if */

	/* check for file exists */
	if ((test & FILE_EXISTS) == FILE_EXISTS) {
		/* check result */
		if (result == false)
			return false;
		
		/* reached this point the file exists */
		result = true;
	}

	/* check if the file is a link */
	if ((test & FILE_IS_LINK) == FILE_IS_LINK) {
		if (! S_ISLNK (file_info.st_mode))
			return false;

		/* reached this point the file is link */
		result = true;
	}

	/* check if the file is a regular */
	if ((test & FILE_IS_REGULAR) == FILE_IS_REGULAR) {
		if (! S_ISREG (file_info.st_mode))
			return false;

		/* reached this point the file is link */
		result = true;
	}

	/* check if the file is a directory */
	if ((test & FILE_IS_DIR) == FILE_IS_DIR) {
		if (! S_ISDIR (file_info.st_mode)) {
			return false;
		}

		/* reached this point the file is link */
		result = true;
	}

	/* return current result */
	return result;
}
