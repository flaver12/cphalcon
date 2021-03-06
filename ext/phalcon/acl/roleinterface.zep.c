
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2015 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
*/
/**
 * Phalcon\Acl\RoleInterface
 *
 * Interface for Phalcon\Acl\Role
 */
ZEPHIR_INIT_CLASS(Phalcon_Acl_RoleInterface) {

	ZEPHIR_REGISTER_INTERFACE(Phalcon\\Acl, RoleInterface, phalcon, acl_roleinterface, phalcon_acl_roleinterface_method_entry);

	return SUCCESS;

}

/**
 * Phalcon\Acl\Role constructor
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_RoleInterface, __construct);

/**
 * Returns the role name
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_RoleInterface, getName);

/**
 * Returns role description
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_RoleInterface, getDescription);

/**
 * Magic method __toString
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_RoleInterface, __toString);

