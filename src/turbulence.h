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
 *         info@aspl.es - http://www.turbulence.ws
 */
#ifndef __TURBULENCE_H__
#define __TURBULENCE_H__

/* system includes */
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>

/* BEEP support */
#include <vortex.h>

/* XML support */
#include <axl.h>

/* command line argument parsing support */
#include <exarg.h>

/* local includes */
#include <turbulence-ctx.h>
#include <turbulence-handlers.h>
#include <turbulence-moddef.h>
#include <turbulence-config.h>
#include <turbulence-run.h>
#include <turbulence-module.h>
#include <turbulence-log.h>
#include <turbulence-ppath.h>
#include <turbulence-db-list.h>
#include <turbulence-conn-mgr.h>


/**
 * \addtogroup turbulence
 * @{
 */

bool turbulence_log_enabled  ();

void turbulence_log_enable   (TurbulenceCtx * ctx, 
			      bool value);

bool turbulence_log2_enabled ();

void turbulence_log2_enable  (TurbulenceCtx * ctx,
			      bool value);

void turbulence_color_log_enable (TurbulenceCtx * ctx,
				  bool            value);

/** 
 * Drop an error msg to the console stderr.
 *
 * To drop an error message use:
 * \code
 *   error ("unable to open file: %s", file);
 * \endcode
 * 
 * @param m The error message to output.
 */
#define error(m,...) do{turbulence_error (__AXL_FILE__, __AXL_LINE__, m, ##__VA_ARGS__);}while(0)
void  turbulence_error (const char * file, int line, const char * format, ...);

/** 
 * Drop a msg to the console stdout.
 *
 * To drop a message use:
 * \code
 *   msg ("module loaded: %s", module);
 * \endcode
 * 
 * @param m The console message to output.
 */
#define msg(m,...)   do{turbulence_msg (__AXL_FILE__, __AXL_LINE__, m, ##__VA_ARGS__);}while(0)
void  turbulence_msg   (const char * file, int line, const char * format, ...);

/** 
 * Drop a second level msg to the console stdout.
 *
 * To drop a message use:
 * \code
 *   msg2 ("module loaded: %s", module);
 * \endcode
 * 
 * @param m The console message to output.
 */
#define msg2(m,...)   do{turbulence_msg2 (__AXL_FILE__, __AXL_LINE__, m, ##__VA_ARGS__);}while(0)
void  turbulence_msg2   (const char * file, int line, const char * format, ...);



/** 
 * Drop a warning msg to the console stdout.
 *
 * To drop a message use:
 * \code
 *   wrn ("module loaded: %s", module);
 * \endcode
 * 
 * @param m The warning message to output.
 */
#define wrn(m,...)   do{turbulence_wrn (__AXL_FILE__, __AXL_LINE__, m, ##__VA_ARGS__);}while(0)
void  turbulence_wrn   (const char * file, int line, const char * format, ...);

/** 
 * Drops to the console stdout a warning, placing the content prefixed
 * with the file and the line that caused the message, without
 * introducing a new line.
 *
 * To drop a message use:
 * \code
 *   wrn_sl ("module loaded: %s", module);
 * \endcode
 * 
 * @param m The warning message to output.
 */
#define wrn_sl(m,...)   do{turbulence_wrn_sl (__AXL_FILE__, __AXL_LINE__, m, ##__VA_ARGS__);}while(0)
void  turbulence_wrn_sl   (const char * file, int line, const char * format, ...);

/** 
 * Reports an access message, a message that is sent to the access log
 * file. The message must contain access to the server information.
 *
 * To drop a message use:
 * \code
 *   access ("module loaded: %s", module);
 * \endcode
 * 
 * @param m The console message to output.
 */
#define access(m,...)   do{turbulence_access (__AXL_FILE__, __AXL_LINE__, m, ##__VA_ARGS__);}while(0)
void  turbulence_access   (const char * file, int line, const char * format, ...);

bool turbulence_init (TurbulenceCtx * ctx);

void turbulence_exit (int value); 

void turbulence_cleanup (TurbulenceCtx * ctx);

void turbulence_reload_config (int value);

bool     turbulence_file_test_v (const char * format, 
				 VortexFileTest test, ...);

bool     turbulence_create_dir  (const char * path);

long int turbulence_last_modification (const char * file);

bool     turbulence_file_is_fullpath (const char * file);

char   * turbulence_base_dir            (const char * path);

char   * turbulence_file_name           (const char * path);

typedef enum {
	DISABLE_STDIN_ECHO = 1 << 0,
} TurbulenceIoFlags;

char *   turbulence_io_get (char * prompt, TurbulenceIoFlags flags);


#endif

/* @} */
