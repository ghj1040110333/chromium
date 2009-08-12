// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// When possible, we implement allocator functions on top of the basic
// low-level functions malloc() and free().  This way, including a new
// allocator is as simple as providing just a small interface.
//
// As such, this file should not contain any allocator-specific code.

// Implement a C++ style allocation, which always calls the new_handler
// on failure.
inline void* generic_cpp_alloc(size_t size, bool nothrow) {
  void* ptr;
  for (;;) {
    ptr = malloc(size);
    if (ptr)
      return ptr;
    if (!call_new_handler(nothrow))
      break;
  }
  return ptr;
}

extern "C++" {

void* __cdecl operator new(size_t size) {
  return generic_cpp_alloc(size, false);
}

void operator delete(void* p) __THROW {
  free(p);
}

void* operator new[](size_t size) {
  return generic_cpp_alloc(size, false);
}

void operator delete[](void* p) __THROW {
  free(p);
}

void* operator new(size_t size, const std::nothrow_t& nt) __THROW {
  return generic_cpp_alloc(size, true);
}

void* operator new[](size_t size, const std::nothrow_t& nt) __THROW {
  return generic_cpp_alloc(size, true);
}

}  // extern "C++"

extern "C" {

// This function behaves similarly to MSVC's _set_new_mode.
// If flag is 0 (default), calls to malloc will behave normally.
// If flag is 1, calls to malloc will behave like calls to new,
// and the std_new_handler will be invoked on failure.
// Returns the previous mode.
int _set_new_mode(int flag) __THROW {
  int old_mode = new_mode;
  new_mode = flag;
  return old_mode;
}

void* calloc(size_t n, size_t elem_size) __THROW {
  // Overflow check
  const size_t size = n * elem_size;
  if (elem_size != 0 && size / elem_size != n) return NULL;

  void* result = malloc(size);
  if (result != NULL) {
    memset(result, 0, size);
  }
  return result;
}

void cfree(void* p) __THROW {
  free(p);
}

#ifdef WIN32

void* _recalloc(void* p, size_t n, size_t elem_size) {
  const size_t size = n * elem_size;
  if (elem_size != 0 && size / elem_size != n) return NULL;

  void* result = realloc(p, size);
  memset(result, 0, size);
  return result;
}

void* _calloc_impl(size_t n, size_t size) {
  return calloc(n, size);
}

#ifndef NDEBUG
#undef malloc
#undef free
#undef calloc
int _CrtDbgReport(int, const char*, int, const char*, const char*, ...) {
  return 0;
}

int _CrtDbgReportW(int, const wchar_t*, int, const wchar_t*,
                   const wchar_t*, ...) {
  return 0;
}

int _CrtSetReportMode(int, int) {
  return 0;
}

void* _malloc_dbg(size_t size, int , const char*, int) {
  return malloc(size);
}

void _free_dbg(void* ptr, int) {
  free(ptr);
}

void* _calloc_dbg(size_t n, size_t size, int, const char*, int) {
  return calloc(n, size);
}
#endif  // NDEBUG

#endif  // WIN32

}  // extern C  

