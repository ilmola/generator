#ifndef UUID_D7746018E901B4EE35CEDC635307152F
#define UUID_D7746018E901B4EE35CEDC635307152F

#include "Edge.hpp"
#include "ShapeVertex.hpp"
#include "MergeShape.hpp"
#include "RepeatShape.hpp"
#include "LineShape.hpp"


namespace generator
{


/**
 * A 2d regular grid.
 */
class GridShape
{
private:

	using Impl = MergeShape<RepeatShape<LineShape>, RepeatShape<LineShape>>;

	Impl mImpl;

public:

	using Edges = Impl::Edges;

	using Vertices = Impl::Vertices;

	/// @param size A half of the side length of the grid.
	/// @param segments The Number of cells in the grid.
	/// If <1 an empty shape results.
	/// @param subSegments The number of segment along each cell edge.
	/// If <1 an empty shape results.
	explicit GridShape(
		const gml::dvec2& size = {1.0, 1.0},
		const gml::ivec2& segments = {4, 4},
		const gml::ivec2& subSegments = {2, 2}
	) noexcept;

	Edges edges() const noexcept;

	Vertices vertices() const noexcept;

};

}

#endif
