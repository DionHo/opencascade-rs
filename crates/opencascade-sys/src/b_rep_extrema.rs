pub use inner::*;

#[cxx::bridge]
mod inner {
    unsafe extern "C++" {
        include!("opencascade-sys/include/b_rep_extrema.hxx");

        type TopoDS_Shape = crate::topo_ds::TopoDS_Shape;
        type gp_Pnt = crate::gp::gp_Pnt;

        type BRepExtrema_DistShapeShape;

        // Result-returning: trycatch converts a Standard_Failure to Err.
        pub fn BRepExtrema_DistShapeShape_new(
            shape1: &TopoDS_Shape,
            shape2: &TopoDS_Shape,
        ) -> Result<UniquePtr<BRepExtrema_DistShapeShape>>;

        pub fn IsDone(self: &BRepExtrema_DistShapeShape) -> bool;
        pub fn NbSolution(self: &BRepExtrema_DistShapeShape) -> i32;
        pub fn Value(self: &BRepExtrema_DistShapeShape) -> Result<f64>;

        pub fn BRepExtrema_DistShapeShape_point_on_shape1(
            dss: &BRepExtrema_DistShapeShape,
            n: i32,
        ) -> UniquePtr<gp_Pnt>;
        pub fn BRepExtrema_DistShapeShape_point_on_shape2(
            dss: &BRepExtrema_DistShapeShape,
            n: i32,
        ) -> UniquePtr<gp_Pnt>;
    }
}

// Single-threaded use (created/read/dropped within one measure call), but match
// the fork's convention (BRepFilletAPI_MakeChamfer is Send) for safety.
unsafe impl Send for inner::BRepExtrema_DistShapeShape {}
