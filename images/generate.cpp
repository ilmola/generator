// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include <fstream>
#include <string>

#include "generator/generator.hpp"

using namespace generator;



static void generateAxis(SvgWriter& svg, Axis axis) {
	gml::dvec3 color{};
	color[static_cast<unsigned>(axis)] = 1.0;

	gml::dvec3 end{};
	end[static_cast<unsigned>(axis)] = 1.5;

	LinePath line{gml::dvec3{}, end, gml::dvec3{}, 15u};
	auto xx = line.vertices();
	auto prev = xx.generate().position;
	xx.next();
	while (!xx.done()) {
		auto current = xx.generate().position;
		svg.writeLine(prev, current, color);
		prev = current;
		xx.next();
	}
}

template <typename Shape>
void generateShape(const Shape& shape, const std::string& filename) {
	SvgWriter svg{400, 400};

	svg.ortho(-1.5, 1.5, -1.5, 1.5);

	generateAxis(svg, Axis::X);
	generateAxis(svg, Axis::Y);

	svg.writeShape(shape, true, true);

	std::ofstream file(filename+".svg");
	file << svg.str();
}


template <typename Path>
void generatePath(const Path& path, const std::string& filename) {
	SvgWriter svg{800, 400};

	svg.perspective(1.0, 1.0, 0.1, 10.0);

	svg.viewport(0, 0, 400, 400);
	svg.modelView(
		gml::translate(gml::dvec3{-0.0, 0.0, -4.0}) *
		gml::rotate(gml::dvec3{gml::radians(45.0), 0.0, 0.0}) *
		gml::rotate(gml::dvec3{0.0, gml::radians(-45.0), 0.0})
	);

	generateAxis(svg, Axis::X);
	generateAxis(svg, Axis::Y);
	generateAxis(svg, Axis::Z);

	svg.writePath(path, true, true);


	svg.viewport(400, 0, 400, 400);
	svg.modelView(
		gml::translate(gml::dvec3{0.0, 0.0, -4.0}) *
		gml::rotate(gml::dvec3{gml::radians(45.0), 0.0, 0.0}) *
		gml::rotate(gml::dvec3{0.0, gml::radians(-135.0), 0.0})
	);

	generateAxis(svg, Axis::X);
	generateAxis(svg, Axis::Y);
	generateAxis(svg, Axis::Z);

	svg.writePath(path, true, true);

	std::ofstream file(filename+".svg");
	file << svg.str();
}


template <typename Mesh>
void generateMesh(const Mesh& mesh, const std::string& filename) {

	SvgWriter svg{800, 400};

	svg.perspective(1.0, 1.0, 0.1, 10.0);

	svg.viewport(0, 0, 400, 400);
	svg.modelView(
		gml::translate(gml::dvec3{-0.0, 0.0, -4.0}) *
		gml::rotate(gml::dvec3{gml::radians(45.0), 0.0, 0.0}) *
		gml::rotate(gml::dvec3{0.0, gml::radians(-45.0), 0.0})
	);

	generateAxis(svg, Axis::X);
	generateAxis(svg, Axis::Y);
	generateAxis(svg, Axis::Z);

	svg.writeMesh(mesh, true, true);

	svg.viewport(400, 0, 400, 400);
	svg.modelView(
		gml::translate(gml::dvec3{0.0, 0.0, -4.0}) *
		gml::rotate(gml::dvec3{gml::radians(45.0), 0.0, 0.0}) *
		gml::rotate(gml::dvec3{0.0, gml::radians(-135.0), 0.0})
	);

	generateAxis(svg, Axis::X);
	generateAxis(svg, Axis::Y);
	generateAxis(svg, Axis::Z);

	svg.writeMesh(mesh, true, true);

	std::ofstream file(filename+".svg");
	file << svg.str();
}


int main() {

	// Shapes
	generateShape(
		BezierShape<4>{{{-1.0, -1.0}, {-0.5, 1.0}, {0.5, -1.0}, {1.0, 1.0}}},
		"BezierShape"
	);
	generateShape(CircleShape{}, "CircleShape");
	generateShape(EmptyShape{}, "EmptyShape");
	generateShape(LineShape{}, "LineShape");
	generateShape(RectangleShape{}, "RectangleShape");
	generateShape(RoundedRectangleShape{}, "RoundedRectangleShape");
	generateShape(GridShape{}, "GridShape");

	// Paths
	generatePath(EmptyPath{}, "EmptyPath");
	generatePath(HelixPath{}, "HelixPath");
	generatePath(KnotPath{}, "KnotPath");
	generatePath(LinePath{}, "LinePath");

	// Meshes
	const gml::dvec3 ctrlPoints[4][4] = {
		{{-1.00,-1.00, 2.66}, {-0.33,-1.00, 0.66}, {0.33,-1.00,-0.66}, {1.0,-1.00, 1.33}},
		{{-1.00,-0.33, 0.66}, {-0.33,-0.33, 2.00}, {0.33,-0.33, 0.00}, {1.0,-0.33,-0.66}},
		{{-1.00, 0.33, 2.66}, {-0.33, 0.33, 0.00}, {0.33, 0.33, 2.00}, {1.0, 0.33, 2.66}},
		{{-1.00, 1.00,-1.33}, {-0.33, 1.00,-1.33}, {0.33, 1.00, 0.00}, {1.0, 1.00,-0.66}}
	};
	generateMesh(BezierMesh<4, 4>{ctrlPoints, {8, 8}}, "BezierMesh");
	generateMesh(BoxMesh{}, "BoxMesh");
	generateMesh(CappedCylinderMesh{}, "CappedCylinderMesh");
	generateMesh(CappedConeMesh{}, "CappedConeMesh");
	generateMesh(CappedTubeMesh{}, "CappedTubeMesh");
	generateMesh(ConeMesh{}, "ConeMesh");
	generateMesh(CapsuleMesh{}, "CapsuleMesh");
	generateMesh(ConvexPolygonMesh{}, "ConvexPolygonMesh");
	generateMesh(CylinderMesh{}, "CylinderMesh");
	generateMesh(DodecahedronMesh{}, "DodecahedronMesh");
	generateMesh(DiskMesh{}, "DiskMesh");
	generateMesh(EmptyMesh{}, "EmptyMesh");
	generateMesh(IcosahedronMesh{}, "IcosahedronMesh");
	generateMesh(IcoSphereMesh{}, "IcoSphereMesh");
	generateMesh(PlaneMesh{}, "PlaneMesh");
	generateMesh(RoundedBoxMesh{}, "RoundedBoxMesh");
	generateMesh(SphereMesh{}, "SphereMesh");
	generateMesh(SphericalConeMesh{}, "SphericalConeMesh");
	generateMesh(SphericalTriangleMesh{}, "SphericalTriangleMesh");
	generateMesh(SpringMesh{}, "SpringMesh");
	generateMesh(scaleMesh(TeapotMesh{}, gml::dvec3{0.5, 0.5, 0.5}), "TeapotMesh");
	generateMesh(TorusKnotMesh{}, "TorusKnotMesh");
	generateMesh(TorusMesh{}, "TorusMesh");
	generateMesh(TriangleMesh{}, "TriangleMesh");
	generateMesh(TubeMesh{}, "TubeMesh");

	// Group picture

	SvgWriter svg{1000, 400};
	svg.perspective(1.0, 1.0, 0.1, 10.0);
	svg.modelView(
		gml::translate(gml::dvec3{-0.0, 0.0, -4.0}) *
		gml::rotate(gml::dvec3{gml::radians(45.0), 0.0, 0.0}) *
		gml::rotate(gml::dvec3{0.0, gml::radians(-45.0), 0.0})
	);


	svg.viewport(0, 200, 200, 200);
	svg.writeMesh(SphereMesh{});

	svg.viewport(200, 200, 200, 200);
	svg.writeMesh(TorusMesh{});

	svg.viewport(400, 200, 200, 200);
	svg.writeMesh(RoundedBoxMesh{});

	svg.viewport(600, 200, 200, 200);
	svg.writeMesh(CappedTubeMesh{});

	svg.viewport(800, 200, 200, 200);
	svg.writeMesh(TorusKnotMesh{});

	svg.viewport(0, 0, 200, 200);
	svg.writeMesh(IcoSphereMesh{});

	svg.viewport(200, 0, 200, 200);
	svg.writeMesh(CappedCylinderMesh{});

	svg.viewport(400, 0, 200, 200);
	svg.writeMesh(CapsuleMesh{});

	svg.viewport(600, 0, 200, 200);
	svg.writeMesh(SpringMesh{});

	svg.viewport(800, 0, 200, 200);
	svg.writeMesh(CappedConeMesh{});



	std::ofstream file("GroupPicture.svg");
	file << svg.str();

	return 0;
}
