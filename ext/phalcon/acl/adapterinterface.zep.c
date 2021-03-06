
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
 * Phalcon\Acl\AdapterInterface
 *
 * Interface for Phalcon\Acl adapters
 */
ZEPHIR_INIT_CLASS(Phalcon_Acl_AdapterInterface) {

	ZEPHIR_REGISTER_INTERFACE(Phalcon\\Acl, AdapterInterface, phalcon, acl_adapterinterface, phalcon_acl_adapterinterface_method_entry);

	return SUCCESS;

}

/**
 * Sets the default access level (Phalcon\Acl::ALLOW or Phalcon\Acl::DENY)
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, setDefaultAction);

/**
 * Returns the default ACL access level
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getDefaultAction);

/**
 * Adds a role to the ACL list. Second parameter lets to inherit access data from other existing role
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addRole);

/**
 * Do a role inherit from another existing role
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addInherit);

/**
 * Check whether role exist in the roles list
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, isRole);

/**
 * Check whether resource exist in the resources list
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, isResource);

/**
 * Adds a resource to the ACL list
 *
 * Access names can be a particular action, by example
 * search, update, delete, etc or a list of them
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addResource);

/**
 * Adds access to resources
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addResourceAccess);

/**
 * Removes an access from a resource
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, dropResourceAccess);

/**
 * Allow access to a role on a resource
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, allow);

/**
 * Deny access to a role on a resource
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, deny);

/**
 * Check whether a role is allowed to access an action from a resource
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, isAllowed);

/**
 * Returns the role which the list is checking if it's allowed to certain resource/access
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getActiveRole);

/**
 * Returns the resource which the list is checking if some role can access it
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getActiveResource);

/**
 * Returns the access which the list is checking if some role can access it
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getActiveAccess);

/**
 * Return an array with every role registered in the list
 *
 * @return Phalcon\Acl\RoleInterface[]
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getRoles);

/**
 * Return an array with every resource registered in the list
 *
 * @return Phalcon\Acl\ResourceInterface[]
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getResources);

