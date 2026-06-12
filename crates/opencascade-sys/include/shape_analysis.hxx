#include <ShapeAnalysis.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <bindings_common.hxx>

// MSVC: Handle_X is a class derived from opencascade::handle<X>; binding
// ConnectEdgesToWires by function pointer with Handle_X parameters fails to
// match the handle<X> signature. A plain call converts fine.
inline void ShapeAnalysis_FreeBounds_ConnectEdgesToWires(Handle_TopTools_HSequenceOfShape &edges,
                                                         double tolerance, bool shared,
                                                         Handle_TopTools_HSequenceOfShape &wires) {
  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, tolerance, shared, wires);
}
