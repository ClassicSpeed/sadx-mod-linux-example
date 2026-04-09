#pragma once

// Load upstream header first, then patch only problematic macro glue for GCC/MinGW.
#include "../../lib/sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"

#if !defined(_MSC_VER)

#undef UsercallFunc
#undef UsercallFuncVoid
#undef UserpurgeFunc
#undef UserpurgeFuncVoid

#define UsercallFunc(RETURN_TYPE, NAME, ARGS, ARGNAMES, ADDRESS, RETURN_LOC, ...) \
class _##NAME##_t \
{ \
public: \
	typedef RETURN_TYPE(*PointerType)ARGS; \
 \
	RETURN_TYPE operator()ARGS \
	{ \
		return wrapper ARGNAMES; \
	} \
 \
	PointerType operator&() \
	{ \
		return wrapper; \
	} \
 \
	operator PointerType() \
	{ \
		return wrapper; \
	} \
 \
	void Hook(PointerType hookfunc) \
	{ \
		memcpy(origdata, getptr(), 5); \
		GenerateUsercallHook<PointerType>(hookfunc, RETURN_LOC, ADDRESS, __VA_ARGS__); \
		ishooked = true; \
	} \
 \
	RETURN_TYPE Original ARGS \
	{ \
		if (ishooked) \
		{ \
			uint8_t hookdata[5]; \
			memcpy(hookdata, getptr(), 5); \
			memcpy(getptr(), origdata, 5); \
			RETURN_TYPE retval = wrapper ARGNAMES; \
			memcpy(getptr(), hookdata, 5); \
			return retval; \
		} \
		else \
			return wrapper ARGNAMES; \
	} \
 \
private: \
	bool ishooked = false; \
	uint8_t origdata[5]{}; \
	const PointerType wrapper = GenerateUsercallWrapper<PointerType>(RETURN_LOC, ADDRESS, __VA_ARGS__); \
 \
	constexpr PointerType getptr() \
	{ \
		return reinterpret_cast<PointerType>(ADDRESS); \
	} \
}; \
static _##NAME##_t NAME

#define UsercallFuncVoid(NAME, ARGS, ARGNAMES, ADDRESS, ...) \
class _##NAME##_t \
{ \
public: \
	typedef void (*PointerType)ARGS; \
 \
	void operator()ARGS \
	{ \
		wrapper ARGNAMES; \
	} \
 \
	PointerType operator&() \
	{ \
		return wrapper; \
	} \
 \
	operator PointerType() \
	{ \
		return wrapper; \
	} \
 \
	void Hook(PointerType hookfunc) \
	{ \
		memcpy(origdata, getptr(), 5); \
		GenerateUsercallHook<PointerType>(hookfunc, noret, ADDRESS, __VA_ARGS__); \
		ishooked = true; \
	} \
 \
	void Original ARGS \
	{ \
		if (ishooked) \
		{ \
			uint8_t hookdata[5]; \
			memcpy(hookdata, getptr(), 5); \
			memcpy(getptr(), origdata, 5); \
			wrapper ARGNAMES; \
			memcpy(getptr(), hookdata, 5); \
		} \
		else \
			wrapper ARGNAMES; \
	} \
 \
private: \
	bool ishooked = false; \
	uint8_t origdata[5]{}; \
	const PointerType wrapper = GenerateUsercallWrapper<PointerType>(noret, ADDRESS, __VA_ARGS__); \
 \
	constexpr PointerType getptr() \
	{ \
		return reinterpret_cast<PointerType>(ADDRESS); \
	} \
}; \
static _##NAME##_t NAME

#define UserpurgeFunc(RETURN_TYPE, NAME, ARGS, ARGNAMES, ADDRESS, RETURN_LOC, ...) \
class _##NAME##_t \
{ \
public: \
	typedef RETURN_TYPE(*PointerType)ARGS; \
 \
	RETURN_TYPE operator()ARGS \
	{ \
		return wrapper ARGNAMES; \
	} \
 \
	PointerType operator&() \
	{ \
		return wrapper; \
	} \
 \
	operator PointerType() \
	{ \
		return wrapper; \
	} \
 \
	void Hook(PointerType hookfunc) \
	{ \
		memcpy(origdata, getptr(), 5); \
		GenerateUserpurgeHook<PointerType>(hookfunc, RETURN_LOC, ADDRESS, __VA_ARGS__); \
		ishooked = true; \
	} \
 \
	RETURN_TYPE Original ARGS \
	{ \
		if (ishooked) \
		{ \
			uint8_t hookdata[5]; \
			memcpy(hookdata, getptr(), 5); \
			memcpy(getptr(), origdata, 5); \
			RETURN_TYPE retval = wrapper ARGNAMES; \
			memcpy(getptr(), hookdata, 5); \
			return retval; \
		} \
		else \
			return wrapper ARGNAMES; \
	} \
 \
private: \
	bool ishooked = false; \
	uint8_t origdata[5]{}; \
	const PointerType wrapper = GenerateUserpurgeWrapper<PointerType>(RETURN_LOC, ADDRESS, __VA_ARGS__); \
 \
	constexpr PointerType getptr() \
	{ \
		return reinterpret_cast<PointerType>(ADDRESS); \
	} \
}; \
static _##NAME##_t NAME

#define UserpurgeFuncVoid(NAME, ARGS, ARGNAMES, ADDRESS, ...) \
class _##NAME##_t \
{ \
public: \
	typedef void (*PointerType)ARGS; \
 \
	void operator()ARGS \
	{ \
		wrapper ARGNAMES; \
	} \
 \
	PointerType operator&() \
	{ \
		return wrapper; \
	} \
 \
	operator PointerType() \
	{ \
		return wrapper; \
	} \
 \
	void Hook(PointerType hookfunc) \
	{ \
		memcpy(origdata, getptr(), 5); \
		GenerateUserpurgeHook<PointerType>(hookfunc, noret, ADDRESS, __VA_ARGS__); \
		ishooked = true; \
	} \
 \
	void Original ARGS \
	{ \
		if (ishooked) \
		{ \
			uint8_t hookdata[5]; \
			memcpy(hookdata, getptr(), 5); \
			memcpy(getptr(), origdata, 5); \
			wrapper ARGNAMES; \
			memcpy(getptr(), hookdata, 5); \
		} \
		else \
			wrapper ARGNAMES; \
	} \
 \
private: \
	bool ishooked = false; \
	uint8_t origdata[5]{}; \
	const PointerType wrapper = GenerateUserpurgeWrapper<PointerType>(noret, ADDRESS, __VA_ARGS__); \
 \
	constexpr PointerType getptr() \
	{ \
		return reinterpret_cast<PointerType>(ADDRESS); \
	} \
}; \
static _##NAME##_t NAME

#endif

