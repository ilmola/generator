// Copyright 2015 Markus Ilmola
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#ifndef GENERATOR_OBJWRITER_HPP
#define GENERATOR_OBJWRITER_HPP

#include <sstream>

#include "MeshVertex.hpp"
#include "Triangle.hpp"


namespace generator {


/// A class for generating obj files for preview and debug purposes.
class ObjWriter {
public:

	ObjWriter();

	template <typename Mesh>
	void writeMesh(const Mesh& mesh) {
		int newBase = base_;

		for (const MeshVertex& vertex : mesh.vertices()) {
			++newBase;

			ss_
			<< "v "
			<< vertex.position[0] << " "
			<< vertex.position[1] << " "
			<< vertex.position[2] << "\n";

			ss_
			<< "vn "
			<< vertex.normal[0] << " "
			<< vertex.normal[1] << " "
			<< vertex.normal[2] << "\n";

			ss_
			<< "vt "
			<< vertex.texCoord[0] << " "
			<< vertex.texCoord[1] << "\n";
		}

		for (const Triangle& triangle : mesh.triangles()) {
			auto t = triangle.vertices + base_;
			ss_
			<< "f "
			<< t[0] << "/" << t[0] << "/" << t[0] << " "
			<< t[1] << "/" << t[1] << "/" << t[1] << " "
			<< t[2] << "/" << t[2] << "/" << t[2] << "\n";
		}

		base_ = newBase;
	}

	std::string str() { return ss_.str(); }

private:

	int base_;

	std::stringstream ss_;

};

}


#endif
