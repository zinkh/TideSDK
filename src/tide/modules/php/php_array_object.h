/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PHP_ARRAY_OBJECT_H_
#define _PHP_ARRAY_OBJECT_H_

#include "php_module.h"

namespace tide
{
	class KPHPArrayObject : public List
	{
		public:
		KPHPArrayObject(zval *list);
		virtual ~KPHPArrayObject();

		ValueRef Get(const char *name);
		void Set(const char *name, ValueRef value);
		virtual bool Equals(ObjectRef);
		SharedStringList GetPropertyNames();

		unsigned int Size();
		void Append(ValueRef value);
		virtual void SetAt(unsigned int index, ValueRef value);
		bool Remove(unsigned int index);
		ValueRef At(unsigned int index);

		zval* ToPHP();

		protected:
		zval *list;

		static void AddKrollValueToPHPArray(ValueRef value, zval *phpArray, const char *key);
		static void AddKrollValueToPHPArray(ValueRef value, zval *phpArray, unsigned int index);
		static void AddKrollValueToPHPArray(ValueRef value, zval *phpArray);
		DISALLOW_EVIL_CONSTRUCTORS(KPHPArrayObject);
	};
}
#endif