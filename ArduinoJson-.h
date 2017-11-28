// Copyright Benoit Blanchon 2014-2017
// MIT License
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!

#pragma once

#include <stddef.h>  // for size_t
#include <stdint.h>  // for uint8_t
#include <string.h>
namespace ArduinoJson {
namespace Internals {
class NonCopyable {
 protected:
  NonCopyable() {}
 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable&);
};
}
}
#ifndef ARDUINOJSON_EMBEDDED_MODE
#if defined(ARDUINO) || defined(__IAR_SYSTEMS_ICC__)
#define ARDUINOJSON_EMBEDDED_MODE 1
#else
#define ARDUINOJSON_EMBEDDED_MODE 0
#endif
#endif
#if ARDUINOJSON_EMBEDDED_MODE
#ifndef ARDUINOJSON_USE_DOUBLE
#define ARDUINOJSON_USE_DOUBLE 0
#endif
#ifndef ARDUINOJSON_USE_LONG_LONG
#define ARDUINOJSON_USE_LONG_LONG 0
#endif
#ifndef ARDUINOJSON_USE_INT64
#define ARDUINOJSON_USE_INT64 0
#endif
#ifndef ARDUINOJSON_ENABLE_STD_STRING
#define ARDUINOJSON_ENABLE_STD_STRING 0
#endif
#ifndef ARDUINOJSON_ENABLE_STD_STREAM
#define ARDUINOJSON_ENABLE_STD_STREAM 0
#endif
#ifndef ARDUINOJSON_DEFAULT_NESTING_LIMIT
#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 10
#endif
#else  // ARDUINOJSON_EMBEDDED_MODE
#ifndef ARDUINOJSON_USE_DOUBLE
#define ARDUINOJSON_USE_DOUBLE 1
#endif
#ifndef ARDUINOJSON_USE_LONG_LONG
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
#define ARDUINOJSON_USE_LONG_LONG 1
#else
#define ARDUINOJSON_USE_LONG_LONG 0
#endif
#endif
#ifndef ARDUINOJSON_USE_INT64
#if defined(_MSC_VER) && _MSC_VER <= 1700
#define ARDUINOJSON_USE_INT64 1
#else
#define ARDUINOJSON_USE_INT64 0
#endif
#endif
#ifndef ARDUINOJSON_ENABLE_STD_STRING
#define ARDUINOJSON_ENABLE_STD_STRING 1
#endif
#ifndef ARDUINOJSON_ENABLE_STD_STREAM
#define ARDUINOJSON_ENABLE_STD_STREAM 1
#endif
#ifndef ARDUINOJSON_DEFAULT_NESTING_LIMIT
#define ARDUINOJSON_DEFAULT_NESTING_LIMIT 50
#endif
#endif  // ARDUINOJSON_EMBEDDED_MODE
#ifdef ARDUINO
#ifndef ARDUINOJSON_ENABLE_ARDUINO_STRING
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#endif
#ifndef ARDUINOJSON_ENABLE_ARDUINO_STREAM
#define ARDUINOJSON_ENABLE_ARDUINO_STREAM 1
#endif
#else  // ARDUINO
#ifndef ARDUINOJSON_ENABLE_ARDUINO_STRING
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 0
#endif
#ifndef ARDUINOJSON_ENABLE_ARDUINO_STREAM
#define ARDUINOJSON_ENABLE_ARDUINO_STREAM 0
#endif
#endif  // ARDUINO
#ifndef ARDUINOJSON_ENABLE_PROGMEM
#ifdef PROGMEM
#define ARDUINOJSON_ENABLE_PROGMEM 1
#else
#define ARDUINOJSON_ENABLE_PROGMEM 0
#endif
#endif
#ifndef ARDUINOJSON_ENABLE_ALIGNMENT
#ifdef ARDUINO_ARCH_AVR
#define ARDUINOJSON_ENABLE_ALIGNMENT 0
#else
#define ARDUINOJSON_ENABLE_ALIGNMENT 1
#endif
#endif
#ifndef ARDUINOJSON_ENABLE_DEPRECATED
#define ARDUINOJSON_ENABLE_DEPRECATED 1
#endif
#ifndef ARDUINOJSON_POSITIVE_EXPONENTIATION_THRESHOLD
#define ARDUINOJSON_POSITIVE_EXPONENTIATION_THRESHOLD 1e7
#endif
#ifndef ARDUINOJSON_NEGATIVE_EXPONENTIATION_THRESHOLD
#define ARDUINOJSON_NEGATIVE_EXPONENTIATION_THRESHOLD 1e-5
#endif
#if ARDUINOJSON_USE_LONG_LONG && ARDUINOJSON_USE_INT64
#error ARDUINOJSON_USE_LONG_LONG and ARDUINOJSON_USE_INT64 cannot be set together
#endif
namespace ArduinoJson {
namespace Internals {
#if ARDUINOJSON_USE_DOUBLE
typedef double JsonFloat;
#else
typedef float JsonFloat;
#endif
}
}
namespace ArduinoJson {
namespace Internals {
#if ARDUINOJSON_USE_LONG_LONG
typedef long long JsonInteger;
typedef unsigned long long JsonUInt;
#elif ARDUINOJSON_USE_INT64
typedef __int64 JsonInteger;
typedef unsigned _int64 JsonUInt;
#else
typedef long JsonInteger;
typedef unsigned long JsonUInt;
#endif
}
}
namespace ArduinoJson {
class JsonArray;
class JsonObject;
namespace Internals {
union JsonVariantContent {
  JsonFloat asFloat;     // used for double and float
  JsonUInt asInteger;    // used for bool, char, short, int and longs
  const char* asString;  // asString can be null
  JsonArray* asArray;    // asArray cannot be null
  JsonObject* asObject;  // asObject cannot be null
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename T>
struct JsonVariantDefault {
  static T get() {
    return T();
  }
};
template <typename T>
struct JsonVariantDefault<const T> : JsonVariantDefault<T> {};
template <typename T>
struct JsonVariantDefault<T&> : JsonVariantDefault<T> {};
}
}
namespace ArduinoJson {
class JsonArray;
class JsonObject;
namespace Internals {
enum JsonVariantType {
  JSON_UNDEFINED,         // JsonVariant has not been initialized
  JSON_UNPARSED,          // JsonVariant contains an unparsed string
  JSON_STRING,            // JsonVariant stores a const char*
  JSON_BOOLEAN,           // JsonVariant stores a bool
  JSON_POSITIVE_INTEGER,  // JsonVariant stores an JsonUInt
  JSON_NEGATIVE_INTEGER,  // JsonVariant stores an JsonUInt that must be negated
  JSON_ARRAY,             // JsonVariant stores a pointer to a JsonArray
  JSON_OBJECT,            // JsonVariant stores a pointer to a JsonObject
  JSON_FLOAT              // JsonVariant stores a JsonFloat
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename T>
struct JsonVariantAs {
  typedef T type;
};
template <>
struct JsonVariantAs<char*> {
  typedef const char* type;
};
template <>
struct JsonVariantAs<JsonArray> {
  typedef JsonArray& type;
};
template <>
struct JsonVariantAs<const JsonArray> {
  typedef const JsonArray& type;
};
template <>
struct JsonVariantAs<JsonObject> {
  typedef JsonObject& type;
};
template <>
struct JsonVariantAs<const JsonObject> {
  typedef const JsonObject& type;
};
}
}
#ifdef _MSC_VER  // Visual Studio
#define FORCE_INLINE __forceinline
#define NO_INLINE __declspec(noinline)
#define DEPRECATED(msg) __declspec(deprecated(msg))
#elif defined(__GNUC__)  // GCC or Clang
#define FORCE_INLINE __attribute__((always_inline))
#define NO_INLINE __attribute__((noinline))
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#define DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
#define DEPRECATED(msg) __attribute__((deprecated))
#endif
#else  // Other compilers
#define FORCE_INLINE
#define NO_INLINE
#define DEPRECATED(msg)
#endif
namespace ArduinoJson {
namespace TypeTraits {
template <bool Condition, typename T = void>
struct EnableIf {};
template <typename T>
struct EnableIf<true, T> {
  typedef T type;
};
}
}
namespace ArduinoJson {
namespace Internals {
class DummyPrint {
 public:
  size_t print(char) {
    return 1;
  }
  size_t print(const char* s) {
    return strlen(s);
  }
};
}
}
namespace ArduinoJson {
namespace TypeTraits {
template <typename TBase, typename TDerived>
class IsBaseOf {
 protected:  // <- to avoid GCC's "all member functions in class are private"
  typedef char Yes[1];
  typedef char No[2];
  static Yes &probe(const TBase *);
  static No &probe(...);
 public:
  enum {
    value = sizeof(probe(reinterpret_cast<TDerived *>(0))) == sizeof(Yes)
  };
};
}
}
namespace ArduinoJson {
namespace TypeTraits {
template <typename T, typename U>
struct IsSame {
  static const bool value = false;
};
template <typename T>
struct IsSame<T, T> {
  static const bool value = true;
};
}
}
namespace ArduinoJson {
namespace TypeTraits {
template <typename T>
struct IsChar {
  static const bool value = IsSame<T, char>::value ||
                            IsSame<T, signed char>::value ||
                            IsSame<T, unsigned char>::value;
};
template <typename T>
struct IsChar<const T> : IsChar<T> {};
}
}
namespace ArduinoJson {
namespace TypeTraits {
template <typename T>
struct RemoveReference {
  typedef T type;
};
template <typename T>
struct RemoveReference<T&> {
  typedef T type;
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename TString, typename Enable = void>
struct StringTraits {};
template <typename TString>
struct StringTraits<const TString, void> : StringTraits<TString> {};
template <typename TString>
struct StringTraits<TString&, void> : StringTraits<TString> {};
}
}
#if ARDUINOJSON_ENABLE_ARDUINO_STREAM
#include <Stream.h>
namespace ArduinoJson {
namespace Internals {
struct ArduinoStreamTraits {
  class Reader {
    Stream& _stream;
    char _current, _next;
   public:
    Reader(Stream& stream) : _stream(stream), _current(0), _next(0) {}
    void move() {
      _current = _next;
      _next = 0;
    }
    char current() {
      if (!_current) _current = read();
      return _current;
    }
    char next() {
      if (!_next) _next = read();
      return _next;
    }
   private:
    char read() {
      char c = 0;
      _stream.readBytes(&c, 1);
      return c;
    }
  };
};
template <typename TStream>
struct StringTraits<TStream,
                    typename TypeTraits::EnableIf<TypeTraits::IsBaseOf<
                        Stream, typename TypeTraits::RemoveReference<
                                    TStream>::type>::value>::type>
    : ArduinoStreamTraits {};
}
}
#endif
namespace ArduinoJson {
namespace Internals {
template <typename TChar>
struct CharPointerTraits {
  class Reader {
    const TChar* _ptr;
   public:
    Reader(const TChar* ptr)
        : _ptr(ptr ? ptr : reinterpret_cast<const TChar*>("")) {}
    void move() {
      ++_ptr;
    }
    char current() const {
      return char(_ptr[0]);
    }
    char next() const {
      return char(_ptr[1]);
    }
  };
  static bool equals(const TChar* str, const char* expected) {
    return strcmp(reinterpret_cast<const char*>(str), expected) == 0;
  }
  template <typename Buffer>
  static char* duplicate(const TChar* str, Buffer* buffer) {
    if (!str) return NULL;
    size_t size = strlen(reinterpret_cast<const char*>(str)) + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy(dup, str, size);
    return static_cast<char*>(dup);
  }
  static const bool has_append = false;
  static const bool has_equals = true;
  static const bool should_duplicate = false;
};
template <typename TChar>
struct StringTraits<TChar*, typename TypeTraits::EnableIf<
                                TypeTraits::IsChar<TChar>::value>::type>
    : CharPointerTraits<TChar> {};
}
}
#if ARDUINOJSON_ENABLE_PROGMEM
namespace ArduinoJson {
namespace Internals {
template <>
struct StringTraits<const __FlashStringHelper*, void> {
  class Reader {
    const char* _ptr;
   public:
    Reader(const __FlashStringHelper* ptr)
        : _ptr(reinterpret_cast<const char*>(ptr)) {}
    void move() {
      _ptr++;
    }
    char current() const {
      return pgm_read_byte_near(_ptr);
    }
    char next() const {
      return pgm_read_byte_near(_ptr + 1);
    }
  };
  static bool equals(const __FlashStringHelper* str, const char* expected) {
    return strcmp_P(expected, (const char*)str) == 0;
  }
  template <typename Buffer>
  static char* duplicate(const __FlashStringHelper* str, Buffer* buffer) {
    if (!str) return NULL;
    size_t size = strlen_P((const char*)str) + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy_P(dup, (const char*)str, size);
    return static_cast<char*>(dup);
  }
  static const bool has_append = false;
  static const bool has_equals = true;
  static const bool should_duplicate = true;
};
}
}
#endif
#if ARDUINOJSON_ENABLE_STD_STREAM
#include <istream>
namespace ArduinoJson {
namespace Internals {
struct StdStreamTraits {
  class Reader {
    std::istream& _stream;
    char _current, _next;
   public:
    Reader(std::istream& stream) : _stream(stream), _current(0), _next(0) {}
    void move() {
      _current = _next;
      _next = 0;
    }
    char current() {
      if (!_current) _current = read();
      return _current;
    }
    char next() {
      if (!_next) _next = read();
      return _next;
    }
   private:
    Reader& operator=(const Reader&);  // Visual Studio C4512
    char read() {
      return _stream.eof() ? '\0' : static_cast<char>(_stream.get());
    }
  };
};
template <typename TStream>
struct StringTraits<TStream,
                    typename TypeTraits::EnableIf<TypeTraits::IsBaseOf<
                        std::istream, typename TypeTraits::RemoveReference<
                                          TStream>::type>::value>::type>
    : StdStreamTraits {};
}
}
#endif
#if ARDUINOJSON_ENABLE_STD_STRING || ARDUINOJSON_ENABLE_ARDUINO_STRING
#if ARDUINOJSON_ENABLE_ARDUINO_STRING
#include <WString.h>
#endif
#if ARDUINOJSON_ENABLE_STD_STRING
#include <string>
#endif
namespace ArduinoJson {
namespace Internals {
template <typename TString>
struct StdStringTraits {
  template <typename Buffer>
  static char* duplicate(const TString& str, Buffer* buffer) {
    if (!str.c_str()) return NULL;  // <- Arduino string can return NULL
    size_t size = str.length() + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy(dup, str.c_str(), size);
    return static_cast<char*>(dup);
  }
  struct Reader : CharPointerTraits<char>::Reader {
    Reader(const TString& str) : CharPointerTraits<char>::Reader(str.c_str()) {}
  };
  static bool equals(const TString& str, const char* expected) {
    return 0 == strcmp(str.c_str(), expected);
  }
  static void append(TString& str, char c) {
    str += c;
  }
  static void append(TString& str, const char* s) {
    str += s;
  }
  static const bool has_append = true;
  static const bool has_equals = true;
  static const bool should_duplicate = true;
};
#if ARDUINOJSON_ENABLE_ARDUINO_STRING
template <>
struct StringTraits<String, void> : StdStringTraits<String> {};
template <>
struct StringTraits<StringSumHelper, void> : StdStringTraits<StringSumHelper> {
};
#endif
#if ARDUINOJSON_ENABLE_STD_STRING
template <>
struct StringTraits<std::string, void> : StdStringTraits<std::string> {};
#endif
}
}
#endif
namespace ArduinoJson {
namespace TypeTraits {
template <typename T, typename Enable = void>
struct IsString {
  static const bool value = false;
};
template <typename T>
struct IsString<T, typename TypeTraits::EnableIf<
                       Internals::StringTraits<T>::has_equals>::type> {
  static const bool value = Internals::StringTraits<T>::has_equals;
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename TString>
class DynamicStringBuilder {
 public:
  DynamicStringBuilder(TString &str) : _str(str) {}
  size_t print(char c) {
    StringTraits<TString>::append(_str, c);
    return 1;
  }
  size_t print(const char *s) {
    size_t initialLen = _str.length();
    StringTraits<TString>::append(_str, s);
    return _str.length() - initialLen;
  }
 private:
  DynamicStringBuilder &operator=(const DynamicStringBuilder &);
  TString &_str;
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename Print>
class IndentedPrint {
 public:
  explicit IndentedPrint(Print &p) : sink(&p) {
    level = 0;
    tabSize = 2;
    isNewLine = true;
  }
  size_t print(char c) {
    size_t n = 0;
    if (isNewLine) n += writeTabs();
    n += sink->print(c);
    isNewLine = c == '\n';
    return n;
  }
  size_t print(const char *s) {
    size_t n = 0;
    while (*s) n += print(*s++);
    return n;
  }
  void indent() {
    if (level < MAX_LEVEL) level++;
  }
  void unindent() {
    if (level > 0) level--;
  }
  void setTabSize(uint8_t n) {
    if (n < MAX_TAB_SIZE) tabSize = n & MAX_TAB_SIZE;
  }
 private:
  Print *sink;
  uint8_t level : 4;
  uint8_t tabSize : 3;
  bool isNewLine : 1;
  size_t writeTabs() {
    size_t n = 0;
    for (int i = 0; i < level * tabSize; i++) n += sink->print(' ');
    return n;
  }
  static const int MAX_LEVEL = 15;    // because it's only 4 bits
  static const int MAX_TAB_SIZE = 7;  // because it's only 3 bits
};
}
}
namespace ArduinoJson {
namespace Internals {
class Encoding {
 public:
  static char escapeChar(char c) {
    const char *p = escapeTable(false);
    while (p[0] && p[1] != c) {
      p += 2;
    }
    return p[0];
  }
  static char unescapeChar(char c) {
    const char *p = escapeTable(true);
    for (;;) {
      if (p[0] == '\0') return c;
      if (p[0] == c) return p[1];
      p += 2;
    }
  }
 private:
  static const char *escapeTable(bool excludeIdenticals) {
    return &"\"\"\\\\b\bf\fn\nr\rt\t"[excludeIdenticals ? 4 : 0];
  }
};
}
}
namespace ArduinoJson {
namespace Polyfills {
template <typename T>
bool isNaN(T x) {
  return x != x;
}
template <typename T>
bool isInfinity(T x) {
  return x != 0.0 && x * 2 == x;
}
}
}
#include <stdlib.h>  // for size_t
namespace ArduinoJson {
namespace TypeTraits {
template <typename T, size_t = sizeof(T)>
struct FloatTraits {};
template <typename T>
struct FloatTraits<T, 8 /*64bits*/> {
  typedef int64_t mantissa_type;
  static const short mantissa_bits = 52;
  static const mantissa_type mantissa_max =
      (static_cast<mantissa_type>(1) << mantissa_bits) - 1;
  typedef int16_t exponent_type;
  static const exponent_type exponent_max = 308;
  template <typename TExponent>
  static T make_float(T m, TExponent e) {
    if (e > 0) {
      for (uint8_t index = 0; e != 0; index++) {
        if (e & 1) m *= positiveBinaryPowerOfTen(index);
        e >>= 1;
      }
    } else {
      e = TExponent(-e);
      for (uint8_t index = 0; e != 0; index++) {
        if (e & 1) m *= negativeBinaryPowerOfTen(index);
        e >>= 1;
      }
    }
    return m;
  }
  static T positiveBinaryPowerOfTen(int index) {
    static T factors[] = {
        1e1, 1e2, 1e4, 1e8, 1e16, 1e32,
        forge(0x4D384F03, 0xE93FF9F5), forge(0x5A827748, 0xF9301D32),
        forge(0x75154FDD, 0x7F73BF3C)};
    return factors[index];
  }
  static T negativeBinaryPowerOfTen(int index) {
    static T factors[] = {
        1e-1, 1e-2, 1e-4, 1e-8, 1e-16, 1e-32,
        forge(0x32A50FFD, 0x44F4A73D), forge(0x255BBA08, 0xCF8C979D),
        forge(0x0AC80628, 0x64AC6F43)};
    return factors[index];
  }
  static T negativeBinaryPowerOfTenPlusOne(int index) {
    static T factors[] = {
        1e0, 1e-1, 1e-3, 1e-7, 1e-15, 1e-31,
        forge(0x32DA53FC, 0x9631D10D), forge(0x25915445, 0x81B7DEC2),
        forge(0x0AFE07B2, 0x7DD78B14)};
    return factors[index];
  }
  static T nan() {
    return forge(0x7ff80000, 0x00000000);
  }
  static T inf() {
    return forge(0x7ff00000, 0x00000000);
  }
  static T forge(uint32_t msb, uint32_t lsb) {
    union {
      uint64_t integerBits;
      T floatBits;
    };
    integerBits = (uint64_t(msb) << 32) | lsb;
    return floatBits;
  }
};
template <typename T>
struct FloatTraits<T, 4 /*32bits*/> {
  typedef int32_t mantissa_type;
  static const short mantissa_bits = 23;
  static const mantissa_type mantissa_max =
      (static_cast<mantissa_type>(1) << mantissa_bits) - 1;
  typedef int8_t exponent_type;
  static const exponent_type exponent_max = 38;
  template <typename TExponent>
  static T make_float(T m, TExponent e) {
    if (e > 0) {
      for (uint8_t index = 0; e != 0; index++) {
        if (e & 1) m *= positiveBinaryPowerOfTen(index);
        e >>= 1;
      }
    } else {
      e = -e;
      for (uint8_t index = 0; e != 0; index++) {
        if (e & 1) m *= negativeBinaryPowerOfTen(index);
        e >>= 1;
      }
    }
    return m;
  }
  static T positiveBinaryPowerOfTen(int index) {
    static T factors[] = {1e1f, 1e2f, 1e4f, 1e8f, 1e16f, 1e32f};
    return factors[index];
  }
  static T negativeBinaryPowerOfTen(int index) {
    static T factors[] = {1e-1f, 1e-2f, 1e-4f, 1e-8f, 1e-16f, 1e-32f};
    return factors[index];
  }
  static T negativeBinaryPowerOfTenPlusOne(int index) {
    static T factors[] = {1e0f, 1e-1f, 1e-3f, 1e-7f, 1e-15f, 1e-31f};
    return factors[index];
  }
  static T forge(uint32_t bits) {
    union {
      uint32_t integerBits;
      T floatBits;
    };
    integerBits = bits;
    return floatBits;
  }
  static T nan() {
    return forge(0x7fc00000);
  }
  static T inf() {
    return forge(0x7f800000);
  }
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename TFloat>
struct FloatParts {
  uint32_t integral;
  uint32_t decimal;
  int16_t exponent;
  int8_t decimalPlaces;
  FloatParts(TFloat value) {
    const uint32_t maxDecimalPart = sizeof(TFloat) >= 8 ? 1000000000 : 1000000;
    exponent = normalize(value);
    integral = uint32_t(value);
    TFloat remainder = value - TFloat(integral);
    remainder *= maxDecimalPart;
    decimal = uint32_t(remainder);
    remainder = remainder - TFloat(decimal);
    decimal += uint32_t(remainder * 2);
    if (decimal >= maxDecimalPart) {
      decimal = 0;
      integral++;
      if (exponent && integral >= 10) {
        exponent++;
        integral = 1;
      }
    }
    decimalPlaces = sizeof(TFloat) >= 8 ? 9 : 6;
    for (uint32_t tmp = integral; tmp >= 10; tmp /= 10) {
      decimal /= 10;
      decimalPlaces--;
    }
    while (decimal % 10 == 0 && decimalPlaces > 0) {
      decimal /= 10;
      decimalPlaces--;
    }
  }
  static int16_t normalize(TFloat& value) {
    typedef TypeTraits::FloatTraits<TFloat> traits;
    int16_t powersOf10 = 0;
    int8_t index = sizeof(TFloat) == 8 ? 8 : 5;
    int bit = 1 << index;
    if (value >= ARDUINOJSON_POSITIVE_EXPONENTIATION_THRESHOLD) {
      for (; index >= 0; index--) {
        if (value >= traits::positiveBinaryPowerOfTen(index)) {
          value *= traits::negativeBinaryPowerOfTen(index);
          powersOf10 = int16_t(powersOf10 + bit);
        }
        bit >>= 1;
      }
    }
    if (value > 0 && value <= ARDUINOJSON_NEGATIVE_EXPONENTIATION_THRESHOLD) {
      for (; index >= 0; index--) {
        if (value < traits::negativeBinaryPowerOfTenPlusOne(index)) {
          value *= traits::positiveBinaryPowerOfTen(index);
          powersOf10 = int16_t(powersOf10 - bit);
        }
        bit >>= 1;
      }
    }
    return powersOf10;
  }
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename Print>
class JsonWriter {
 public:
  explicit JsonWriter(Print &sink) : _sink(sink), _length(0) {}
  size_t bytesWritten() const {
    return _length;
  }
  void beginArray() {
    writeRaw('[');
  }
  void endArray() {
    writeRaw(']');
  }
  void beginObject() {
    writeRaw('{');
  }
  void endObject() {
    writeRaw('}');
  }
  void writeColon() {
    writeRaw(':');
  }
  void writeComma() {
    writeRaw(',');
  }
  void writeBoolean(bool value) {
    writeRaw(value ? "true" : "false");
  }
  void writeString(const char *value) {
    if (!value) {
      writeRaw("null");
    } else {
      writeRaw('\"');
      while (*value) writeChar(*value++);
      writeRaw('\"');
    }
  }
  void writeChar(char c) {
    char specialChar = Encoding::escapeChar(c);
    if (specialChar) {
      writeRaw('\\');
      writeRaw(specialChar);
    } else {
      writeRaw(c);
    }
  }
  template <typename TFloat>
  void writeFloat(TFloat value) {
    if (Polyfills::isNaN(value)) return writeRaw("NaN");
    if (value < 0.0) {
      writeRaw('-');
      value = -value;
    }
    if (Polyfills::isInfinity(value)) return writeRaw("Infinity");
    FloatParts<TFloat> parts(value);
    writeInteger(parts.integral);
    if (parts.decimalPlaces) writeDecimals(parts.decimal, parts.decimalPlaces);
    if (parts.exponent < 0) {
      writeRaw("e-");
      writeInteger(-parts.exponent);
    }
    if (parts.exponent > 0) {
      writeRaw('e');
      writeInteger(parts.exponent);
    }
  }
  template <typename UInt>
  void writeInteger(UInt value) {
    char buffer[22];
    char *end = buffer + sizeof(buffer) - 1;
    char *ptr = end;
    *ptr = 0;
    do {
      *--ptr = char(value % 10 + '0');
      value = UInt(value / 10);
    } while (value);
    writeRaw(ptr);
  }
  void writeDecimals(uint32_t value, int8_t width) {
    char buffer[16];
    char *ptr = buffer + sizeof(buffer) - 1;
    *ptr = 0;
    while (width--) {
      *--ptr = char(value % 10 + '0');
      value /= 10;
    }
    *--ptr = '.';
    writeRaw(ptr);
  }
  void writeRaw(const char *s) {
    _length += _sink.print(s);
  }
  void writeRaw(char c) {
    _length += _sink.print(c);
  }
 protected:
  Print &_sink;
  size_t _length;
 private:
  JsonWriter &operator=(const JsonWriter &);  // cannot be assigned
};
}
}
namespace ArduinoJson {
class JsonArray;
class JsonArraySubscript;
class JsonObject;
template <typename TKey>
class JsonObjectSubscript;
class JsonVariant;
namespace Internals {
template <typename Writer>
class JsonSerializer {
 public:
  static void serialize(const JsonArray &, Writer &);
  static void serialize(const JsonArraySubscript &, Writer &);
  static void serialize(const JsonObject &, Writer &);
  template <typename TKey>
  static void serialize(const JsonObjectSubscript<TKey> &, Writer &);
  static void serialize(const JsonVariant &, Writer &);
};
}
}
namespace ArduinoJson {
namespace Internals {
template <typename Print>
class Prettyfier {
 public:
  explicit Prettyfier(IndentedPrint<Print>& p) : _sink(p) {
    _previousChar = 0;
    _inString = false;
  }
  size_t print(char c) {
    size_t n = _inString ? handleStringChar(c) : handleMarkupChar(c);
    _previousChar = c;
    return n;
  }
  size_t print(const char* s) {
    size_t n = 0;
    while (*s) n += print(*s++);
    return n;
  }
 private:
  Prettyfier& operator=(const Prettyfier&);  // cannot be assigned
  bool inEmptyBlock() {
    return _previousChar == '{' || _previousChar == '[';
  }
  size_t handleStringChar(char c) {
    bool isQuote = c == '"' && _previousChar != '\\';
    if (isQuote) _inString = false;
    return _sink.print(c);
  }
  size_t handleMarkupChar(char c) {
    switch (c) {
      case '{':
      case '[':
        return writeBlockOpen(c);
      case '}':
      case ']':
        return writeBlockClose(c);
      case ':':
        return writeColon();
      case ',':
        return writeComma();
      case '"':
        return writeQuoteOpen();
      default:
        return writeNormalChar(c);
    }
  }
  size_t writeBlockClose(char c) {
    size_t n = 0;
    n += unindentIfNeeded();
    n += _sink.print(c);
    return n;
  }
  size_t writeBlockOpen(char c) {
    size_t n = 0;
    n += indentIfNeeded();
    n += _sink.print(c);
    return n;
  }
  size_t writeColon() {
    size_t n = 0;
    n += _sink.print(": ");
    return n;
  }
  size_t writeComma() {
    size_t n = 0;
    n += _sink.print(",\r\n");
    return n;
  }
  size_t writeQuoteOpen() {
    _inString = true;
    size_t n = 0;
    n += indentIfNeeded();
    n += _sink.print('"');
    return n;
  }
  size_t writeNormalChar(char c) {
    size_t n = 0;
    n += indentIfNeeded();
    n += _sink.print(c);
    return n;
  }
  size_t indentIfNeeded() {
    if (!inEmptyBlock()) return 0;
    _sink.indent();
    return _sink.print("\r\n");
  }
  size_t unindentIfNeeded() {
    if (inEmptyBlock()) return 0;
    _sink.unindent();
    return _sink.print("\r\n");
  }
  char _previousChar;
  IndentedPrint<Print>& _sink;
  bool _inString;
};
}
}
namespace ArduinoJson {
namespace Internals {
class StaticStringBuilder {
 public:
  StaticStringBuilder(char *buf, size_t size) : end(buf + size - 1), p(buf) {
    *p = '\0';
  }
  size_t print(char c) {
    if (p >= end) return 0;
    *p++ = c;
    *p = '\0';
    return 1;
  }
  size_t print(const char *s) {
    char *begin = p;
    while (p < end && *s) *p++ = *s++;
    *p = '\0';
    return size_t(p - begin);
  }
 private:
  char *end;
  char *p;
};
}
}
#if ARDUINOJSON_ENABLE_STD_STREAM
#if ARDUINOJSON_ENABLE_STD_STREAM
#include <ostream>
namespace ArduinoJson {
namespace Internals {
class StreamPrintAdapter {
 public:
  explicit StreamPrintAdapter(std::ostream& os) : _os(os) {}
  size_t print(char c) {
    _os << c;
    return 1;
  }
  size_t print(const char* s) {
    _os << s;
    return strlen(s);
  }
 private:
  StreamPrintAdapter& operator=(const StreamPrintAdapter&);
  std::ostream& _os;
};
}
}
#endif  // ARDUINOJSON_ENABLE_STD_STREAM
#endif
namespace ArduinoJson {
namespace Internals {
template <typename T>
class JsonPrintable {
 public:
  template <typename Print>
  typename TypeTraits::EnableIf<!TypeTraits::IsString<Print>::value,
                                size_t>::type
  printTo(Print &print) const {
    JsonWriter<Print> writer(print);
    JsonSerializer<JsonWriter<Print> >::serialize(downcast(), writer);
    return writer.bytesWritten();
  }
#if ARDUINOJSON_ENABLE_STD_STREAM
  std::ostream &printTo(std::ostream &os) const {
    StreamPrintAdapter adapter(os);
    printTo(adapter);
    return os;
  }
#endif
  size_t printTo(char *buffer, size_t bufferSize) const {
    StaticStringBuilder sb(buffer, bufferSize);
    return printTo(sb);
  }
  template <size_t N>
  size_t printTo(char (&buffer)[N]) const {
    return printTo(buffer, N);
  }
  template <typename TString>
  typename TypeTraits::EnableIf<StringTraits<TString>::has_append, size_t>::type
  printTo(TString &str) const {
    DynamicStringBuilder<TString> sb(str);
    return printTo(sb);
  }
  template <typename Print>
  size_t prettyPrintTo(IndentedPrint<Print> &print) const {
    Prettyfier<Print> p(print);
    return printTo(p);
  }
  size_t prettyPrintTo(char *buffer, size_t bufferSize) const {
    StaticStringBuilder sb(buffer, bufferSize);
    return prettyPrintTo(sb);
  }
  template <size_t N>
  size_t prettyPrintTo(char (&buffer)[N]) const {
    return prettyPrintTo(buffer, N);
  }
  template <typename Print>
  typename TypeTraits::EnableIf<!TypeTraits::IsString<Print>::value,
                                size_t>::type
  prettyPrintTo(Print &print) const {
    IndentedPrint<Print> indentedPrint(print);
    return prettyPrintTo(indentedPrint);
  }
  template <typename TString>
  typename TypeTraits::EnableIf<StringTraits<TString>::has_append, size_t>::type
  prettyPrintTo(TString &str) const {
    DynamicStringBuilder<TString> sb(str);
    return prettyPrintTo(sb);
  }
  size_t measureLength() const {
    DummyPrint dp;
    return printTo(dp);
  }
  size_t measurePrettyLength() const {
    DummyPrint dp;
    return prettyPrintTo(dp);
  }
 private:
  const T &downcast() const {
    return *static_cast<const T *>(this);
  }
};
#if ARDUINOJSON_ENABLE_STD_STREAM
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const JsonPrintable<T> &v) {
  return v.printTo(os);
}
#endif
}
}
namespace ArduinoJson {
class JsonArraySubscript;
template <typename TKey>
class JsonObjectSubscript;
template <typename TImpl>
class JsonVariantBase : public Internals::JsonPrintable<TImpl> {
 public:
#if ARDUINOJSON_ENABLE_DEPRECATED
  DEPRECATED("use as<JsonArray>() instead")
  FORCE_INLINE JsonArray &asArray() const {
    return as<JsonArray>();
  }
  DEPRECATED("use as<JsonObject>() instead")
  FORCE_INLINE JsonObject &asObject() const {
    return as<JsonObject>();
  }
  DEPRECATED("use as<char*>() instead")
  FORCE_INLINE const char *asString() const {
    return as<const char *>();
  }
#endif
  FORCE_INLINE operator JsonArray &() const {
    return as<JsonArray &>();
  }
  FORCE_INLINE operator JsonObject &() const {
    return as<JsonObject &>();
  }
  template <typename T>
  FORCE_INLINE operator T() const {
    return as<T>();
  }
  template <typename T>
  FORCE_INLINE const typename Internals::JsonVariantAs<T>::type as() const {
    return impl()->template as<T>();
  }
  template <typename T>
  FORCE_INLINE bool is() const {
    return impl()->template is<T>();
  }
  size_t size() const {
    return as<JsonArray>().size() + as<JsonObject>().size();
  }
  FORCE_INLINE const JsonArraySubscript operator[](size_t index) const;
  FORCE_INLINE JsonArraySubscript operator[](size_t index);
  template <typename TString>
  FORCE_INLINE typename TypeTraits::EnableIf<
      Internals::StringTraits<TString>::has_equals,
      const JsonObjectSubscript<const TString &> >::type
  operator[](const TString &key) const {
    return as<JsonObject>()[key];
  }
  template <typename TString>
  FORCE_INLINE typename TypeTraits::EnableIf<
      Internals::StringTraits<TString>::has_equals,
      JsonObjectSubscript<const TString &> >::type
  operator[](const TString &key) {
    return as<JsonObject>()[key];
  }
  template <typename TString>
  FORCE_INLINE typename TypeTraits::EnableIf<
      Internals::StringTraits<const TString *>::has_equals,
      JsonObjectSubscript<const TString *> >::type
  operator[](const TString *key) {
    return as<JsonObject>()[key];
  }
  template <typename TString>
  FORCE_INLINE typename TypeTraits::EnableIf<
      Internals::StringTraits<TString *>::has_equals,
      const JsonObjectSubscript<const TString *> >::type
  operator[](const TString *key) const {
    return as<JsonObject>()[key];
  }
 private:
  const TImpl *impl() const {
    return static_cast<const TImpl *>(this);
  }
};
namespace TypeTraits {
template <typename T>
struct IsVariant : IsBaseOf<JsonVariantBase<T>, T> {};
}
}
namespace ArduinoJson {
class RawJson {
 public:
  explicit RawJson(const char* str) : _str(str) {}
  operator const char*() const {
    return _str;
  }
 private:
  const char* _str;
};
}
namespace ArduinoJson {
namespace TypeTraits {
template <typename T>
struct IsFloatingPoint {
  static const bool value = IsSame<T, float>::value || IsSame<T, double>::value;
};
}
}
namespace ArduinoJson {
namespace TypeTraits {
template <typename T>
struct IsSignedIntegral {
  static const bool value = TypeTraits::IsSame<T, signed char>::value ||
                            TypeTraits::IsSame<T, signed short>::value ||
                            TypeTraits::IsSame<T, signed int>::value ||
