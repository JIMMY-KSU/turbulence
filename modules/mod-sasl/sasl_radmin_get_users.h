/**
 * C server skel to implement services exported by the XML-RPC
 * component: sasl-radmin.
 *
 * This file was generated by xml-rpc-gen tool, from Vortex Library
 * project. 
 *
 * Vortex Library homepage:           http://vortex.aspl.es
 * Axl Library homepage:              http://xml.aspl.es
 * Advanced Software Production Line: http://www.aspl.es
 */
#ifndef __SERVER_SASL_RADMIN_GET_USERS_XML_RPC_H__
#define __SERVER_SASL_RADMIN_GET_USERS_XML_RPC_H__

/* include base library */
#include <vortex.h>
/* include xml-rpc library */
#include <vortex_xml_rpc.h>
#include <sasl_radmin_types.h>

SaslUserArray * get_users_0 (char ** fault_error, int * fault_code, VortexChannel * channel);

XmlRpcMethodResponse * __get_users_0 (XmlRpcMethodCall * method_call, VortexChannel * channel);

#endif
