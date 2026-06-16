#pragma once
#include <BRepExtrema_DistShapeShape.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>
#include <bindings_common.hxx>
#include <memory>

// BRepExtrema_DistShapeShape computes on construction. Wrap the constructor in
// a Result-returning bridge fn (declared in the .rs) so a Standard_Failure
// during the computation becomes a Rust Err via bindings_common.hxx's trycatch,
// rather than std::terminate. (Uncatchable aborts are contained one layer up by
// the cad-mcp --measure-worker subprocess.)
inline std::unique_ptr<BRepExtrema_DistShapeShape>
BRepExtrema_DistShapeShape_new(const TopoDS_Shape &shape1, const TopoDS_Shape &shape2) {
  return std::make_unique<BRepExtrema_DistShapeShape>(shape1, shape2);
}

// PointOnShape1/2(N) return a `const gp_Pnt&` into the dss's solution arrays.
// cxx can't hand back a borrow of an opaque C++ type tied to the dss lifetime,
// so copy the point into an owned unique_ptr (the new_point/construct_unique
// pattern). Safe because the caller keeps `dss` alive across this call.
inline std::unique_ptr<gp_Pnt>
BRepExtrema_DistShapeShape_point_on_shape1(const BRepExtrema_DistShapeShape &dss, int n) {
  return std::make_unique<gp_Pnt>(dss.PointOnShape1(n));
}

inline std::unique_ptr<gp_Pnt>
BRepExtrema_DistShapeShape_point_on_shape2(const BRepExtrema_DistShapeShape &dss, int n) {
  return std::make_unique<gp_Pnt>(dss.PointOnShape2(n));
}
