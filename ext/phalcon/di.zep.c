
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"


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
 |          Nikolaos Dimopoulos <nikos@niden.net>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Di
 *
 * Phalcon\Di is a component that implements Dependency Injection/Service Location
 * of services and it"s itself a container for them.
 *
 * Since Phalcon is highly decoupled, Phalcon\Di is essential to integrate the different
 * components of the framework. The developer can also use this component to inject dependencies
 * and manage global instances of the different classes used in the application.
 *
 * Basically, this component implements the `Inversion of Control` pattern. Applying this,
 * the objects do not receive their dependencies using setters or constructors, but requesting
 * a service dependency injector. This reduces the overall complexity, since there is only one
 * way to get the required dependencies within a component.
 *
 * Additionally, this pattern increases testability in the code, thus making it less prone to errors.
 *
 *<code>
 * $di = new \Phalcon\Di();
 *
 * //Using a string definition
 * $di->set("request", "Phalcon\Http\Request", true);
 *
 * //Using an anonymous function
 * $di->set("request", function(){
 *	  return new \Phalcon\Http\Request();
 * }, true);
 *
 * $request = $di->getRequest();
 *
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Di) {

	ZEPHIR_REGISTER_CLASS(Phalcon, Di, phalcon, di, phalcon_di_method_entry, 0);

	zend_declare_property_null(phalcon_di_ce, SL("_services"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_di_ce, SL("_sharedInstances"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(phalcon_di_ce, SL("_freshInstance"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Events Manager
	 *
	 * @var Phalcon\Events\ManagerInterface
	 */
	zend_declare_property_null(phalcon_di_ce, SL("_eventsManager"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_di_ce, SL("_default"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_class_implements(phalcon_di_ce TSRMLS_CC, 1, phalcon_diinterface_ce);
	zend_class_implements(phalcon_di_ce TSRMLS_CC, 1, phalcon_events_eventsawareinterface_ce);
	return SUCCESS;

}

/**
 * Phalcon\Di constructor
 */
PHP_METHOD(Phalcon_Di, __construct) {

	zval *di;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(di);
	zephir_read_static_property_ce(&di, phalcon_di_ce, SL("_default") TSRMLS_CC);
	if (!(zephir_is_true(di))) {
		zephir_update_static_property_ce(phalcon_di_ce, SL("_default"), &this_ptr TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Registers a service in the services container
 *
 * @param string name
 * @param mixed definition
 * @param boolean shared
 * @return Phalcon\Di\ServiceInterface
 */
PHP_METHOD(Phalcon_Di, set) {

	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool shared;
	zval *name_param = NULL, *definition, *shared_param = NULL, *service;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &name_param, &definition, &shared_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}
	if (!shared_param) {
		shared = 0;
	} else {
		shared = zephir_get_boolval(shared_param);
	}


	ZEPHIR_INIT_VAR(service);
	object_init_ex(service, phalcon_di_service_ce);
	ZEPHIR_CALL_METHOD(NULL, service, "__construct", &_0, name, definition, (shared ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("_services"), name, service TSRMLS_CC);
	RETURN_CCTOR(service);

}

/**
 * Registers an "always shared" service in the services container
 *
 * @param string name
 * @param mixed definition
 * @return Phalcon\Di\ServiceInterface
 */
PHP_METHOD(Phalcon_Di, setShared) {

	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *definition, *service, _0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &definition);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_INIT_VAR(service);
	object_init_ex(service, phalcon_di_service_ce);
	ZEPHIR_SINIT_VAR(_0);
	ZVAL_BOOL(&_0, 1);
	ZEPHIR_CALL_METHOD(NULL, service, "__construct", &_1, name, definition, &_0);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("_services"), name, service TSRMLS_CC);
	RETURN_CCTOR(service);

}

/**
 * Removes a service in the services container
 */
PHP_METHOD(Phalcon_Di, remove) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_services"), PH_NOISY_CC);
	zephir_array_unset(&_0, name, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Attempts to register a service in the services container
 * Only is successful if a service hasn"t been registered previously
 * with the same name
 *
 * @param string name
 * @param mixed definition
 * @param boolean shared
 * @return Phalcon\Di\ServiceInterface|false
 */
PHP_METHOD(Phalcon_Di, attempt) {

	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool shared;
	zval *name_param = NULL, *definition, *shared_param = NULL, *service, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &name_param, &definition, &shared_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}
	if (!shared_param) {
		shared = 0;
	} else {
		shared = zephir_get_boolval(shared_param);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_services"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, name))) {
		ZEPHIR_INIT_VAR(service);
		object_init_ex(service, phalcon_di_service_ce);
		ZEPHIR_CALL_METHOD(NULL, service, "__construct", &_1, name, definition, (shared ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("_services"), name, service TSRMLS_CC);
		RETURN_CCTOR(service);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Sets a service using a raw Phalcon\Di\Service definition
 */
PHP_METHOD(Phalcon_Di, setRaw) {

	zval *name_param = NULL, *rawDefinition;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &rawDefinition);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	zephir_update_property_array(this_ptr, SL("_services"), name, rawDefinition TSRMLS_CC);
	RETVAL_ZVAL(rawDefinition, 1, 0);
	RETURN_MM();

}

/**
 * Returns a service definition without resolving
 *
 * @param string name
 * @return mixed
 */
PHP_METHOD(Phalcon_Di, getRaw) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *service, *_0, *_1;
	zval *name = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_OBS_VAR(service);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_services"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&service, _0, name, 0 TSRMLS_CC)) {
		ZEPHIR_RETURN_CALL_METHOD(service, "getdefinition", NULL);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, phalcon_di_exception_ce);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVS(_2, "Service '", name, "' wasn't found in the dependency injection container");
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", &_3, _2);
	zephir_check_call_status();
	zephir_throw_exception_debug(_1, "phalcon/di.zep", 177 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Returns a Phalcon\Di\Service instance
 */
PHP_METHOD(Phalcon_Di, getService) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *service, *_0, *_1;
	zval *name = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_OBS_VAR(service);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_services"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&service, _0, name, 0 TSRMLS_CC)) {
		RETURN_CCTOR(service);
	}
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, phalcon_di_exception_ce);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVS(_2, "Service '", name, "' wasn't found in the dependency injection container");
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", &_3, _2);
	zephir_check_call_status();
	zephir_throw_exception_debug(_1, "phalcon/di.zep", 191 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Resolves the service based on its configuration
 *
 * @param string name
 * @param array parameters
 * @return mixed
 */
PHP_METHOD(Phalcon_Di, get) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_5 = NULL, *_6 = NULL, *_8 = NULL;
	zval *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *parameters = NULL, *service, *instance = NULL, *reflection = NULL, *eventsManager = NULL, *_0 = NULL, *_2 = NULL, *_3;
	zval *name = NULL, *_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &parameters);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}
	if (!parameters) {
		parameters = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "geteventsmanager", NULL);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(eventsManager, _0);
	if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(_1);
		zephir_create_array(_1, 2, 0 TSRMLS_CC);
		zephir_array_update_string(&_1, SL("name"), &name, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_1, SL("parameters"), &parameters, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "di:beforeServiceResolve", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, eventsManager, "fire", NULL, _2, this_ptr, _1);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
	}
	ZEPHIR_OBS_VAR(service);
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("_services"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&service, _3, name, 0 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&instance, service, "resolve", NULL, parameters, this_ptr);
		zephir_check_call_status();
	} else {
		if (zephir_class_exists(name, 1 TSRMLS_CC)) {
			if (Z_TYPE_P(parameters) == IS_ARRAY) {
				if (zephir_fast_count_int(parameters TSRMLS_CC)) {
					if (zephir_is_php_version(50600)) {
						ZEPHIR_INIT_VAR(reflection);
						object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionclass") TSRMLS_CC));
						ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", &_4, name);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&instance, reflection, "newinstanceargs", &_5, parameters);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_NVAR(instance);
						ZEPHIR_LAST_CALL_STATUS = zephir_create_instance_params(instance, name, parameters TSRMLS_CC);
						zephir_check_call_status();
					}
				} else {
					if (zephir_is_php_version(50600)) {
						ZEPHIR_INIT_NVAR(reflection);
						object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionclass") TSRMLS_CC));
						ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", &_4, name);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&instance, reflection, "newinstance", &_6);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_NVAR(instance);
						ZEPHIR_LAST_CALL_STATUS = zephir_create_instance(instance, name TSRMLS_CC);
						zephir_check_call_status();
					}
				}
			} else {
				if (zephir_is_php_version(50600)) {
					ZEPHIR_INIT_NVAR(reflection);
					object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionclass") TSRMLS_CC));
					ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", &_4, name);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&instance, reflection, "newinstance", &_6);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(instance);
					ZEPHIR_LAST_CALL_STATUS = zephir_create_instance(instance, name TSRMLS_CC);
					zephir_check_call_status();
				}
			}
		} else {
			ZEPHIR_INIT_NVAR(_2);
			object_init_ex(_2, phalcon_di_exception_ce);
			ZEPHIR_INIT_VAR(_7);
			ZEPHIR_CONCAT_SVS(_7, "Service '", name, "' wasn't found in the dependency injection container");
			ZEPHIR_CALL_METHOD(NULL, _2, "__construct", &_8, _7);
			zephir_check_call_status();
			zephir_throw_exception_debug(_2, "phalcon/di.zep", 246 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(instance) == IS_OBJECT) {
		if (zephir_instance_of_ev(instance, phalcon_di_injectionawareinterface_ce TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, instance, "setdi", NULL, this_ptr);
			zephir_check_call_status();
		}
	}
	if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
		if (Z_TYPE_P(instance) == IS_OBJECT) {
			if (zephir_instance_of_ev(instance, phalcon_events_eventsawareinterface_ce TSRMLS_CC)) {
				ZEPHIR_CALL_METHOD(NULL, instance, "seteventsmanager", NULL, eventsManager);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(_1);
		zephir_create_array(_1, 3, 0 TSRMLS_CC);
		zephir_array_update_string(&_1, SL("name"), &name, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_1, SL("parameters"), &parameters, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_1, SL("instance"), &instance, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "di:afterServiceResolve", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, eventsManager, "fire", NULL, _2, this_ptr, _1);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
	}
	RETURN_CCTOR(instance);

}

/**
 * Resolves a service, the resolved service is stored in the DI, subsequent requests for this service will return the same instance
 *
 * @param string name
 * @param array parameters
 * @return mixed
 */
PHP_METHOD(Phalcon_Di, getShared) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *parameters = NULL, *instance = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &parameters);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}
	if (!parameters) {
		parameters = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_OBS_VAR(instance);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_sharedInstances"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&instance, _0, name, 0 TSRMLS_CC)) {
		zephir_update_property_this(this_ptr, SL("_freshInstance"), (0) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	} else {
		ZEPHIR_CALL_METHOD(&instance, this_ptr, "get", NULL, name, parameters);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("_sharedInstances"), name, instance TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_freshInstance"), (1) ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	RETURN_CCTOR(instance);

}

/**
 * Check whether the DI contains a service by a name
 */
PHP_METHOD(Phalcon_Di, has) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_services"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_array_isset(_0, name));

}

/**
 * Check whether the last service obtained via getShared produced a fresh instance or an existing one
 */
PHP_METHOD(Phalcon_Di, wasFreshInstance) {


	RETURN_MEMBER(this_ptr, "_freshInstance");

}

/**
 * Return the services registered in the DI
 */
PHP_METHOD(Phalcon_Di, getServices) {


	RETURN_MEMBER(this_ptr, "_services");

}

/**
 * Check if a service is registered using the array syntax
 */
PHP_METHOD(Phalcon_Di, offsetExists) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "has", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Allows to register a shared service using the array syntax
 *
 *<code>
 *	$di["request"] = new \Phalcon\Http\Request();
 *</code>
 *
 * @param string name
 * @param mixed definition
 * @return boolean
 */
PHP_METHOD(Phalcon_Di, offsetSet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *definition;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &definition);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setshared", NULL, name, definition);
	zephir_check_call_status();
	RETURN_MM_BOOL(1);

}

/**
 * Allows to obtain a shared service using the array syntax
 *
 *<code>
 *	var_dump($di["request"]);
 *</code>
 *
 * @param string name
 * @return mixed
 */
PHP_METHOD(Phalcon_Di, offsetGet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getshared", NULL, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Removes a service from the services container using the array syntax
 */
PHP_METHOD(Phalcon_Di, offsetUnset) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	RETURN_MM_BOOL(0);

}

/**
 * Sets the event manager
 */
PHP_METHOD(Phalcon_Di, setEventsManager) {

	zval *eventsManager;

	zephir_fetch_params(0, 1, 0, &eventsManager);



	zephir_update_property_this(this_ptr, SL("_eventsManager"), eventsManager TSRMLS_CC);

}

/**
 * Returns the internal event manager
 */
PHP_METHOD(Phalcon_Di, getEventsManager) {


	RETURN_MEMBER(this_ptr, "_eventsManager");

}

/**
 * Magic method to get or set services using setters/getters
 *
 * @param string method
 * @param array arguments
 * @return mixed
 */
PHP_METHOD(Phalcon_Di, __call) {

	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_6 = NULL;
	zval *method_param = NULL, *arguments = NULL, *instance = NULL, *possibleService = NULL, *services, *definition, _0 = zval_used_for_init, *_1 = NULL, *_4 = NULL;
	zval *method = NULL, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &method_param, &arguments);

	if (unlikely(Z_TYPE_P(method_param) != IS_STRING && Z_TYPE_P(method_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'method' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(method_param) == IS_STRING)) {
		zephir_get_strval(method, method_param);
	} else {
		ZEPHIR_INIT_VAR(method);
		ZVAL_EMPTY_STRING(method);
	}
	if (!arguments) {
		arguments = ZEPHIR_GLOBAL(global_null);
	}


	if (zephir_start_with_str(method, SL("get"))) {
		ZEPHIR_OBS_VAR(services);
		zephir_read_property_this(&services, this_ptr, SL("_services"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_0);
		ZVAL_LONG(&_0, 3);
		ZEPHIR_INIT_VAR(_1);
		zephir_substr(_1, method, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_CALL_FUNCTION(&possibleService, "lcfirst", &_2, _1);
		zephir_check_call_status();
		if (zephir_array_isset(services, possibleService)) {
			if (zephir_fast_count_int(arguments TSRMLS_CC)) {
				ZEPHIR_CALL_METHOD(&instance, this_ptr, "get", &_3, possibleService, arguments);
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_METHOD(&instance, this_ptr, "get", &_3, possibleService);
				zephir_check_call_status();
			}
			RETURN_CCTOR(instance);
		}
	}
	if (zephir_start_with_str(method, SL("set"))) {
		ZEPHIR_OBS_VAR(definition);
		if (zephir_array_isset_long_fetch(&definition, arguments, 0, 0 TSRMLS_CC)) {
			ZEPHIR_SINIT_NVAR(_0);
			ZVAL_LONG(&_0, 3);
			ZEPHIR_INIT_NVAR(_1);
			zephir_substr(_1, method, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
			ZEPHIR_CALL_FUNCTION(&_4, "lcfirst", &_2, _1);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, _4, definition);
			zephir_check_call_status();
			RETURN_MM_NULL();
		}
	}
	ZEPHIR_INIT_NVAR(_1);
	object_init_ex(_1, phalcon_di_exception_ce);
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_CONCAT_SVS(_5, "Call to undefined method or service '", method, "'");
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", &_6, _5);
	zephir_check_call_status();
	zephir_throw_exception_debug(_1, "phalcon/di.zep", 436 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Set a default dependency injection container to be obtained into static methods
 */
PHP_METHOD(Phalcon_Di, setDefault) {

	zval *dependencyInjector;

	zephir_fetch_params(0, 1, 0, &dependencyInjector);



	zephir_update_static_property_ce(phalcon_di_ce, SL("_default"), &dependencyInjector TSRMLS_CC);

}

/**
 * Return the lastest DI created
 */
PHP_METHOD(Phalcon_Di, getDefault) {

	zval *_0;


	_0 = zephir_fetch_static_property_ce(phalcon_di_ce, SL("_default") TSRMLS_CC);
	RETURN_CTORW(_0);

}

/**
 * Resets the internal default DI
 */
PHP_METHOD(Phalcon_Di, reset) {


	zephir_update_static_property_ce(phalcon_di_ce, SL("_default"), &(ZEPHIR_GLOBAL(global_null)) TSRMLS_CC);

}

