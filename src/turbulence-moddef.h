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
#ifndef __TURBULENCE_MODDEF_H__
#define __TURBULENCE_MODDEF_H__

/** 
 * @brief Public definition for the init function that must implement
 * a turbulence module.
 *
 * The init function doesn't receive any thing, but it must return
 * true to signal that the modules was initialized and must be
 * registered.
 * 
 * @return true if the module is usable or false if not.
 */
typedef bool (*ModInitFunc)  ();

/** 
 * @brief Public definition for the close function that must implement
 * all operations required to unload module.
 * 
 * The function doesn't receive and return any data.
 */
typedef void (*ModCloseFunc) ();

/** 
 * @brief Public definition for the reconfiguration function that must
 * be implemented to receive notification if the turbulence server
 * configuration is reloaded.
 */
typedef void (*ModReconfFunc) ();


/**
 * @brief Public definition for the main entry point for all modules
 * developed for turbulence.
 * 
 * See mod-test module for an example.
 */
typedef struct _TurbulenceModDef {
	/**
	 * @brief The module name. This name is used by turbulence to
	 * refer to the module.
	 */
	char         * mod_name;

	/**
	 * @brief The module long description.
	 */
	char         * mod_description;

	/**
	 * @brief A reference to the init function associated to the module.
	 */
	ModInitFunc    init;

	/**
	 * @brief A reference to the close function associated to the
	 * module.
	 */
	ModCloseFunc   close;
	
	/**
	 * @brief A reference to the reconf function that must be
	 * implemented to get notifications about turbulence server
	 * configuration changes.
	 */
	ModReconfFunc  reconf;
} TurbulenceModDef;

#endif
