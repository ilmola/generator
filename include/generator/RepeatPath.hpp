#ifndef UUID_580A4434BBE9A17A6302CC90C22DE898
#define UUID_580A4434BBE9A17A6302CC90C22DE898

#include "utils.hpp"
#include "PathVertex.hpp"
#include "Edge.hpp"

namespace generator
{


/**
 * Repeats the same path a given number of time at given intervals.
 */
template <typename Path>
class RepeatPath
{
public:

	class Edges
	{
	public:

		bool done() const noexcept
		{
			return mIndex >= mRepeatPath->mInstances;
		}

		Edge generate() const
		{
			Edge temp = mEdges.generate();
			temp.vertices += mDelta;
			return temp;
		}

		void next() noexcept
		{
			mEdges.next();

			if (mEdges.done()) {
				++mIndex;
				mDelta += mRepeatPath->mVertexCount;
				mEdges = mRepeatPath->mPath.edges();
			}
		}

	private:

		const RepeatPath* mRepeatPath;

		typename EdgeGeneratorType<Path>::Type mEdges;

		int mIndex;

		int mDelta;

		explicit Edges(const RepeatPath* repeatPath) noexcept :
			mRepeatPath{repeatPath},
			mEdges{repeatPath->mPath.edges()},
			mIndex{repeatPath->mVertexCount > 0 ? 0 : repeatPath->mInstances},
			mDelta{0}
		{

		}

	friend class RepeatPath;
	};


	class Vertices
	{
	public:

		bool done() const noexcept
		{
			return mIndex >= mRepeatPath->mInstances;
		}

		PathVertex generate() const
		{
			PathVertex temp = mVertices.generate();
			temp.position += mDelta;
			return temp;
		}

		void next()
		{
			mVertices.next();

			if (mVertices.done()) {
				++mIndex;
				mDelta += mRepeatPath->mDelta;
				mVertices = mRepeatPath->mPath.vertices();
			}
		}

	private:

		explicit Vertices(const RepeatPath* repeatPath) :
			mRepeatPath{repeatPath},
			mVertices{repeatPath->mPath.vertices()},
			mIndex{repeatPath->mVertexCount > 0 ? 0 : repeatPath->mInstances},
			mDelta{}
		{ }

		const RepeatPath* mRepeatPath;

		typename VertexGeneratorType<Path>::Type mVertices;

		int mIndex;

		gml::dvec3 mDelta;

		int countVertices() const noexcept
		{
			if (mRepeatPath->mInstances < 1) return 0;

			return
				mRepeatPath->mVertexCount *
				(mRepeatPath->mInstances - mIndex - 1) +
				count(mVertices);
		}

	friend
		int count(const Vertices& generator) noexcept
		{
			return generator.countVertices();
		}

	friend class RepeatPath;
	};


	/// @param path The path to repeat.
	/// @param instances Number of times to repeat. If <1 an empty path results.
	/// @param delta An offset aplied to each copy.
	explicit RepeatPath(Path path, int instances, const gml::dvec3& delta) noexcept :
		mPath{std::move(path)},
		mInstances{instances},
		mDelta{delta},
		mVertexCount{count(mPath.vertices())}
	{ }

	Edges edges() const noexcept
	{
		return Edges{this};
	}

	Vertices vertices() const noexcept
	{
		return Vertices{this};
	}

private:

	Path mPath;

	int mInstances;

	gml::dvec3 mDelta;

	int mVertexCount;

};


template <typename Path>
RepeatPath<Path> repeatPath(Path path, int instances, const gml::dvec3& delta) noexcept
{
	return RepeatPath<Path>{std::move(path), instances, delta};
}


}

#endif
