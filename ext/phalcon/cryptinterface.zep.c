
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

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
 * Phalcon\CryptInterface
 *
 * Interface for Phalcon\Crypt
 */
ZEPHIR_INIT_CLASS(Phalcon_CryptInterface) {

	ZEPHIR_REGISTER_INTERFACE(Phalcon, CryptInterface, phalcon, cryptinterface, phalcon_cryptinterface_method_entry);

	return SUCCESS;

}

/**
 * Sets the cipher algorithm
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, setCipher);

/**
 * Returns the current cipher
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, getCipher);

/**
 * Sets the encrypt/decrypt mode
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, setMode);

/**
 * Returns the current encryption mode
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, getMode);

/**
 * Sets the encryption key
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, setKey);

/**
 * Returns the encryption key
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, getKey);

/**
 * Encrypts a text
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, encrypt);

/**
 * Decrypts a text
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, decrypt);

/**
 * Encrypts a text returning the result as a base64 string
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, encryptBase64);

/**
 * Decrypt a text that is coded as a base64 string
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, decryptBase64);

/**
 * Returns a list of available cyphers
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, getAvailableCiphers);

/**
 * Returns a list of available modes
 */
ZEPHIR_DOC_METHOD(Phalcon_CryptInterface, getAvailableModes);

