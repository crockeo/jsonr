#include "json.hpp"

//////////
// Code //

namespace jsonr {
    // Constructing a JValue as a couple of different types.
    JValue::JValue(JObject jObject) {
        this->type = JOBJECT;
        this->jObject_value = jObject;
    }

    JValue::JValue(JArray jArray) {
        this->type = JARRAY;
        this->jArray_value = jArray;
    }

    JValue::JValue(JNumber jNumber) {
        this->type = JNUMBER;
        this->jNumber_value = jNumber;
    }

    JValue::JValue(JString jString) {
        this->type = JSTRING;
        this->jString_value = jString;
    }

    JValue::JValue(JBool jBool) {
        this->type = JBOOL;
        this->jBool_value = jBool;
    }

    // Constructing a JValue as null.
    JValue::JValue() {
        this->type = JNULL;
    }

    // Getting the type of the JValue.
    JType JValue::getType() const { return this->type; }

    // Checking specifically if this JValue represents something else.
    bool JValue::isObject() const { return this->getType() == JOBJECT; }
    bool JValue::isArray()  const { return this->getType() == JARRAY;  }
    bool JValue::isNumber() const { return this->getType() == JNUMBER; }
    bool JValue::isString() const { return this->getType() == JSTRING; }
    bool JValue::isBool()   const { return this->getType() == JBOOL;   }
    bool JValue::isNull()   const { return this->getType() == JNULL;   }

    // Getting the specific values of this JValue.
    JObject JValue::jObject() const { return this->jObject_value; }
    JArray  JValue::jArray()  const { return this->jArray_value;  }
    JNumber JValue::jNumber() const { return this->jNumber_value; }
    JString JValue::jString() const { return this->jString_value; }
    JBool   JValue::jBool()   const { return this->jBool_value;   }
}
