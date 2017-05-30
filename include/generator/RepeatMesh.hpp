#ifndef UUID_34107193C252FF8CC2A084B47CFB15D4
#define UUID_34107193C252FF8CC2A084B47CFB15D4

#include "utils.hpp"
#include "MeshVertex.hpp"
#include "Triangle.hpp"

namespace generator
{


/**
 * Repeats the same mesh a given number of time at given intervals.
 */
template <typename Mesh>
class RepeatMesh
{
public:

	class Triangles
	{
	public:

		bool done() const noexcept
		{
			return mIndex >= mRepeatMesh->mInstances;
		}

		Triangle generate() const
		{
			Triangle temp = mTriangles.generate();
			temp.vertices += mDelta;
			return temp;
		}

		void next() noexcept
		{
			mTriangles.next();

			if (mTriangles.done()) {
				++mIndex;
				mDelta += mRepeatMesh->mVertexCount;
				mTriangles = mRepeatMesh->mMesh.triangles();
			}
		}

	private:

		const RepeatMesh* mRepeatMesh;

		typename TriangleGeneratorType<Mesh>::Type mTriangles;

		int mIndex;

		int mDelta;

		explicit Triangles(const RepeatMesh* repeatMesh) noexcept :
			mRepeatMesh{repeatMesh},
			mTriangles{repeatMesh->mMesh.triangles()},
			mIndex{repeatMesh->mVertexCount > 0 ? 0 : repeatMesh->mInstances},
			mDelta{0}
		{ }

		int countTriangles() const noexcept
		{
			if (mRepeatMesh->mInstances < 1) return 0;

			return
				count(mRepeatMesh->mMesh.triangles()) *
				(mRepeatMesh->mInstances - mIndex - 1) +
				count(mTriangles);
		}

	friend
		int count(const Triangles& generator) noexcept
		{
			return generator.countTriangles();
		}

	friend class RepeatMesh;
	};


	class Vertices
	{
	public:

		bool done() const noexcept
		{
			return mIndex >= mRepeatMesh->mInstances;
		}

		MeshVertex generate() const
		{
			MeshVertex temp = mVertices.generate();
			temp.position += mDelta;
			return temp;
		}

		void next()
		{
			mVertices.next();

			if (mVertices.done()) {
				++mIndex;
				mDelta += mRepeatMesh->mDelta;
				mVertices = mRepeatMesh->mMesh.vertices();
			}
		}

	private:

		explicit Vertices(const RepeatMesh* repeatMesh) :
			mRepeatMesh{repeatMesh},
			mVertices{repeatMesh->mMesh.vertices()},
			mIndex{repeatMesh->mVertexCount > 0 ? 0 : repeatMesh->mInstances},
			mDelta{}
		{ }

		const RepeatMesh* mRepeatMesh;

		typename VertexGeneratorType<Mesh>::Type mVertices;

		int mIndex;

		gml::dvec3 mDelta;

		int countVertices() const noexcept
		{
			if (mRepeatMesh->mInstances < 1) return 0;

			return
				mRepeatMesh->mVertexCount *
				(mRepeatMesh->mInstances - mIndex - 1) +
				count(mVertices);
		}

	friend
		int count(const Vertices& generator) noexcept
		{
			return generator.countVertices();
		}

	friend class RepeatMesh;
	};


	/// @param mesh The mesh to repeat.
	/// @param instances Number of times to repeat. If <1 an empty mesh results.
	/// @param delta An offset aplied to each copy.
	explicit RepeatMesh(Mesh mesh, int instances, const gml::dvec3& delta) noexcept :
		mMesh{std::move(mesh)},
		mInstances{instances},
		mDelta{delta},
		mVertexCount{count(mMesh.vertices())}
	{ }

	Triangles triangles() const noexcept
	{
		return Triangles{this};
	}

	Vertices vertices() const noexcept
	{
		return Vertices{this};
	}

private:

	Mesh mMesh;

	int mInstances;

	gml::dvec3 mDelta;

	int mVertexCount;

};





template <typename Mesh>
RepeatMesh<Mesh> repeatMesh(Mesh mesh, int instances, const gml::dvec3& delta) noexcept
{
	return RepeatMesh<Mesh>{std::move(mesh), instances, delta};
}


}

#endif
