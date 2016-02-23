file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/generator/*.hpp")

add_library(generator STATIC
	AnyMesh.cpp
	AnyPath.cpp
	AnyShape.cpp
	BoxMesh.cpp
	CappedConeMesh.cpp
	CappedCylinderMesh.cpp
	CappedTubeMesh.cpp
	CapsuleMesh.cpp
	CircleShape.cpp
	ConeMesh.cpp
	CylinderMesh.cpp
	DiskMesh.cpp
	EmptyMesh.cpp
	EmptyPath.cpp
	EmptyShape.cpp
	HelixPath.cpp
	IcosahedronMesh.cpp
	IcoSphereMesh.cpp
	KnotPath.cpp
	LinePath.cpp
	LineShape.cpp
	ObjWriter.cpp
	RectangleShape.cpp
	SphereMesh.cpp
	SphericalConeMesh.cpp
	SphericalTriangleMesh.cpp
	SpringMesh.cpp
	SvgWriter.cpp
	ParametricMesh.cpp
	ParametricPath.cpp
	ParametricShape.cpp
	PlaneMesh.cpp
	RoundedBoxMesh.cpp
	RoundedRectangleShape.cpp
	TorusKnotMesh.cpp
	TorusMesh.cpp
	TriangleMesh.cpp
	TubeMesh.cpp
)

target_include_directories (generator PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_custom_target(headers SOURCES)
