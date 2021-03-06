
#ifdef HAVE_CONFIG_H
#include "../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../php_ext.h"
#include "../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/hash.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/object.h"


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
 * Phalcon\Mvc\Model\Validator\Uniqueness
 *
 * Validates that a field or a combination of a set of fields are not
 * present more than once in the existing records of the related table
 *
 *<code>
 *use Phalcon\Mvc\Model\Validator\Uniqueness as Uniqueness;
 *
 *class Subscriptors extends \Phalcon\Mvc\Model
 *{
 *
 *  public function validation()
 *  {
 *      $this->validate(new Uniqueness(array(
 *          "field" => 'email'
 *      )));
 *      if ($this->validationHasFailed() == true) {
 *          return false;
 *      }
 *  }
 *
 *}
 *</code>
 *
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_Validator_Uniqueness) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc\\Model\\Validator, Uniqueness, phalcon, mvc_model_validator_uniqueness, phalcon_mvc_model_validator_ce, phalcon_mvc_model_validator_uniqueness_method_entry, 0);

	zend_class_implements(phalcon_mvc_model_validator_uniqueness_ce TSRMLS_CC, 1, phalcon_mvc_model_validatorinterface_ce);
	return SUCCESS;

}

/**
 * Executes the validator
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator_Uniqueness, validate) {

	zephir_nts_static zephir_fcall_cache_entry *_18 = NULL;
	zend_class_entry *_16;
	zephir_fcall_cache_entry *_5 = NULL, *_9 = NULL;
	HashTable *_2, *_12;
	HashPosition _1, _11;
	int number, ZEPHIR_LAST_CALL_STATUS;
	zval *record, *field = NULL, *dependencyInjector = NULL, *metaData = NULL, *message = NULL, *bindTypes, *bindDataTypes = NULL, *columnMap = NULL, *conditions, *bindParams, *composeField = NULL, *columnField = NULL, *bindType = NULL, *primaryField = NULL, *attributeField = NULL, *params, *className, *replacePairs = NULL, *_0 = NULL, **_3, *_4 = NULL, _6 = zval_used_for_init, *_7 = NULL, *_8 = NULL, *_10 = NULL, **_13, *_14 = NULL, *_15 = NULL, *_17 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &record);



	ZEPHIR_CALL_METHOD(&dependencyInjector, record, "getdi", NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "modelsMetadata", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&metaData, dependencyInjector, "getshared", NULL, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(bindTypes);
	array_init(bindTypes);
	ZEPHIR_CALL_METHOD(&bindDataTypes, metaData, "getbindtypes", NULL, record);
	zephir_check_call_status();
	if (ZEPHIR_GLOBAL(orm).column_renaming) {
		ZEPHIR_CALL_METHOD(&columnMap, metaData, "getreversecolumnmap", NULL, record);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(columnMap);
		ZVAL_NULL(columnMap);
	}
	ZEPHIR_INIT_VAR(conditions);
	array_init(conditions);
	ZEPHIR_INIT_VAR(bindParams);
	array_init(bindParams);
	number = 0;
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "field", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&field, this_ptr, "getoption", NULL, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	if (Z_TYPE_P(field) == IS_ARRAY) {
		zephir_is_iterable(field, &_2, &_1, 0, 0, "phalcon/mvc/model/validator/uniqueness.zep", 121);
		for (
		  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HVALUE(composeField, _3);
			if (Z_TYPE_P(columnMap) == IS_ARRAY) {
				ZEPHIR_OBS_NVAR(columnField);
				if (!(zephir_array_isset_fetch(&columnField, columnMap, composeField, 0 TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_0);
					object_init_ex(_0, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_4);
					ZEPHIR_CONCAT_SVS(_4, "Column '", composeField, "' isn't part of the column map");
					ZEPHIR_CALL_METHOD(NULL, _0, "__construct", &_5, _4);
					zephir_check_call_status();
					zephir_throw_exception_debug(_0, "phalcon/mvc/model/validator/uniqueness.zep", 98 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(columnField, composeField);
			}
			ZEPHIR_OBS_NVAR(bindType);
			if (!(zephir_array_isset_fetch(&bindType, bindDataTypes, columnField, 0 TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_0);
				object_init_ex(_0, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_4);
				ZEPHIR_CONCAT_SVS(_4, "Column '", columnField, "' isn't part of the table columns");
				ZEPHIR_CALL_METHOD(NULL, _0, "__construct", &_5, _4);
				zephir_check_call_status();
				zephir_throw_exception_debug(_0, "phalcon/mvc/model/validator/uniqueness.zep", 108 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_SINIT_NVAR(_6);
			ZVAL_LONG(&_6, number);
			ZEPHIR_INIT_LNVAR(_7);
			ZEPHIR_CONCAT_SVSV(_7, "[", composeField, "] = ?", &_6);
			zephir_array_append(&conditions, _7, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 114);
			ZEPHIR_CALL_METHOD(&_8, record, "readattribute", &_9, composeField);
			zephir_check_call_status();
			zephir_array_append(&bindParams, _8, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 115);
			zephir_array_append(&bindTypes, bindType, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 116);
			number++;
		}
	} else {
		if (Z_TYPE_P(columnMap) == IS_ARRAY) {
			ZEPHIR_OBS_NVAR(columnField);
			if (!(zephir_array_isset_fetch(&columnField, columnMap, field, 0 TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_0);
				object_init_ex(_0, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_7);
				ZEPHIR_CONCAT_SVS(_7, "Column '", field, "' isn't part of the column map");
				ZEPHIR_CALL_METHOD(NULL, _0, "__construct", &_5, _7);
				zephir_check_call_status();
				zephir_throw_exception_debug(_0, "phalcon/mvc/model/validator/uniqueness.zep", 128 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(columnField, field);
		}
		ZEPHIR_OBS_NVAR(bindType);
		if (!(zephir_array_isset_fetch(&bindType, bindDataTypes, columnField, 0 TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(_0);
			object_init_ex(_0, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_LNVAR(_7);
			ZEPHIR_CONCAT_SVS(_7, "Column '", columnField, "' isn't part of the table columns");
			ZEPHIR_CALL_METHOD(NULL, _0, "__construct", &_5, _7);
			zephir_check_call_status();
			zephir_throw_exception_debug(_0, "phalcon/mvc/model/validator/uniqueness.zep", 138 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_INIT_LNVAR(_7);
		ZEPHIR_CONCAT_SVS(_7, "[", field, "] = ?0");
		zephir_array_append(&conditions, _7, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 144);
		ZEPHIR_CALL_METHOD(&_8, record, "readattribute", &_9, field);
		zephir_check_call_status();
		zephir_array_append(&bindParams, _8, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 145);
		zephir_array_append(&bindTypes, bindType, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 146);
		number++;
	}
	ZEPHIR_CALL_METHOD(&_10, record, "getoperationmade", NULL);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG(_10, 2)) {
		if (ZEPHIR_GLOBAL(orm).column_renaming) {
			ZEPHIR_CALL_METHOD(&columnMap, metaData, "getcolumnmap", NULL, record);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(columnMap);
			ZVAL_NULL(columnMap);
		}
		ZEPHIR_CALL_METHOD(&_8, metaData, "getprimarykeyattributes", NULL, record);
		zephir_check_call_status();
		zephir_is_iterable(_8, &_12, &_11, 0, 0, "phalcon/mvc/model/validator/uniqueness.zep", 191);
		for (
		  ; zephir_hash_get_current_data_ex(_12, (void**) &_13, &_11) == SUCCESS
		  ; zephir_hash_move_forward_ex(_12, &_11)
		) {
			ZEPHIR_GET_HVALUE(primaryField, _13);
			ZEPHIR_OBS_NVAR(bindType);
			if (!(zephir_array_isset_fetch(&bindType, bindDataTypes, primaryField, 0 TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_0);
				object_init_ex(_0, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_7);
				ZEPHIR_CONCAT_SVS(_7, "Column '", primaryField, "' isn't part of the table columns");
				ZEPHIR_CALL_METHOD(NULL, _0, "__construct", &_5, _7);
				zephir_check_call_status();
				zephir_throw_exception_debug(_0, "phalcon/mvc/model/validator/uniqueness.zep", 168 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (Z_TYPE_P(columnMap) == IS_ARRAY) {
				ZEPHIR_OBS_NVAR(attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, columnMap, primaryField, 0 TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_0);
					object_init_ex(_0, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_14);
					ZEPHIR_CONCAT_SVS(_14, "Column '", primaryField, "' isn't part of the column map");
					ZEPHIR_CALL_METHOD(NULL, _0, "__construct", &_5, _14);
					zephir_check_call_status();
					zephir_throw_exception_debug(_0, "phalcon/mvc/model/validator/uniqueness.zep", 176 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(attributeField, primaryField);
			}
			ZEPHIR_SINIT_NVAR(_6);
			ZVAL_LONG(&_6, number);
			ZEPHIR_INIT_LNVAR(_4);
			ZEPHIR_CONCAT_SVSV(_4, "[", attributeField, "] <> ?", &_6);
			zephir_array_append(&conditions, _4, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 185);
			ZEPHIR_CALL_METHOD(&_15, record, "readattribute", &_9, primaryField);
			zephir_check_call_status();
			zephir_array_append(&bindParams, _15, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 186);
			zephir_array_append(&bindTypes, bindType, PH_SEPARATE, "phalcon/mvc/model/validator/uniqueness.zep", 187);
			number++;
		}
	}
	ZEPHIR_INIT_VAR(params);
	array_init(params);
	zephir_array_update_string(&params, SL("di"), &dependencyInjector, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_0);
	zephir_fast_join_str(_0, SL(" AND "), conditions TSRMLS_CC);
	zephir_array_update_string(&params, SL("conditions"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&params, SL("bind"), &bindParams, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&params, SL("bindTypes"), &bindTypes, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(className);
	zephir_get_class(className, record, 0 TSRMLS_CC);
	_16 = zephir_fetch_class(className TSRMLS_CC);
	ZEPHIR_CALL_CE_STATIC(&_8, _16, "count", NULL, params);
	zephir_check_call_status();
	if (!ZEPHIR_IS_LONG(_8, 0)) {
		ZEPHIR_INIT_VAR(_17);
		ZVAL_STRING(_17, "message", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&message, this_ptr, "getoption", NULL, _17);
		zephir_check_temp_parameter(_17);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(replacePairs);
		zephir_create_array(replacePairs, 1, 0 TSRMLS_CC);
		zephir_array_update_string(&replacePairs, SL(":field"), &field, PH_COPY | PH_SEPARATE);
		if (ZEPHIR_IS_EMPTY(message)) {
			ZEPHIR_INIT_NVAR(message);
			if (Z_TYPE_P(field) == IS_ARRAY) {
				ZEPHIR_INIT_NVAR(replacePairs);
				zephir_create_array(replacePairs, 1, 0 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(_17);
				zephir_fast_join_str(_17, SL(", "), field TSRMLS_CC);
				zephir_array_update_string(&replacePairs, SL(":fields"), &_17, PH_COPY | PH_SEPARATE);
				ZVAL_STRING(message, "Value of fields: :fields are already present in another record", 1);
			} else {
				ZVAL_STRING(message, "Value of field: ':field' is already present in another record", 1);
			}
		}
		ZEPHIR_CALL_FUNCTION(&_8, "strtr", &_18, message, replacePairs);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_17);
		ZVAL_STRING(_17, "Unique", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "appendmessage", NULL, _8, field, _17);
		zephir_check_temp_parameter(_17);
		zephir_check_call_status();
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}

