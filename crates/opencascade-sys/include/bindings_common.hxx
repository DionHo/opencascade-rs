#pragma once
#include "rust/cxx.h"
#include <NCollection_List.hxx>
#include <memory>

// Generic template constructor
template <typename T, typename... Args> std::unique_ptr<T> construct_unique(Args... args) {
  return std::unique_ptr<T>(new T(args...));
}

// Type casting
template <typename T, typename U> inline U upcast(T src) { return src; }
template <typename T, typename U> inline const U &upcast_ref(const T &src) { return src; }

// Generic List
template <typename T> std::unique_ptr<std::vector<T>> list_to_vector(const NCollection_List<T> &list) {
  return std::unique_ptr<std::vector<T>>(new std::vector<T>(list.begin(), list.end()));
}

template <typename T> const T &handle_try_deref(const opencascade::handle<T> &handle) {
  if (handle.IsNull()) {
    throw std::runtime_error("null handle dereference");
  }
  return *handle;
}

// cxx's default trycatch only catches std::exception. OCCT's exception
// hierarchy (Standard_Failure: StdFail_NotDone, Standard_DomainError, ...)
// derives from Standard_Transient instead, so kernel exceptions crossing a
// Result-returning bridge fn would otherwise std::terminate. This is the
// cxx-documented customization point; it converts them to Rust Err values.
#include <Standard_Failure.hxx>

namespace rust {
namespace behavior {
template <typename Try, typename Fail> static void trycatch(Try &&func, Fail &&fail) noexcept try {
  func();
} catch (const Standard_Failure &failure) {
  const char *msg = failure.GetMessageString();
  fail((msg != nullptr && msg[0] != '\0') ? msg : failure.DynamicType()->Name());
} catch (const std::exception &e) {
  fail(e.what());
}
} // namespace behavior
} // namespace rust
