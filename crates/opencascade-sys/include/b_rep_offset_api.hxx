#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <Law_Function.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <bindings_common.hxx>

// MSVC: Handle_X is a class derived from opencascade::handle<X>; binding
// SetLaw by member pointer with a Handle_Law_Function signature fails to
// match the handle<Law_Function> overload. A plain call converts fine.
inline void BRepOffsetAPI_MakePipeShell_SetLaw(BRepOffsetAPI_MakePipeShell &make_pipe_shell,
                                               const TopoDS_Shape &profile, const Handle_Law_Function &law,
                                               bool with_contact, bool with_correction) {
  make_pipe_shell.SetLaw(profile, law, with_contact, with_correction);
}
