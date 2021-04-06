#ifndef TRPIXEL_SAMPLER_H
#define TRPIXEL_SAMPLER_H

#include <array>
#include <vector>

#include "glm/glm.hpp"

namespace TinyRenderer
{
	template <typename T, size_t N>
	class TRIPixelSampler
	{
	public:
		std::array<T, N> samplers;

		static size_t getSamplingNum() { return N; }
		//virtual std::array<glm::vec2, N> getSamplingOffsets() const = 0;

		T& operator[](const int &index) { return samplers[index]; }
		const T& operator[](const int &index) const { return samplers[index]; }

	};

	//1x Sampling Point
	template <typename T>
	class TRPixelSampler1X : public TRIPixelSampler<T, 1>
	{
	public:

		TRPixelSampler1X(const T &value) { samplers.fill(value); }

		static const std::array<glm::vec2, 1> &getSamplingOffsets()
		{
			return { glm::vec2(0.0, 0.0) };
		}

	};

	//4x Sampling Point
	template <typename T>
	class TRPixelSampler4X : public TRIPixelSampler<T, 4>
	{
	public:

		TRPixelSampler4X(const T &value) { samplers.fill(value); }

		static const std::array<glm::vec2, 4> &getSamplingOffsets()
		{
			return
			{
				glm::vec2(-0.25, -0.25),
				glm::vec2(+0.25, -0.25),
				glm::vec2(+0.25, +0.25),
				glm::vec2(-0.25, +0.25)
			};
		}
	};

#define MSAA4X

#ifdef MSAA4X
	template<typename T>
	using TRPixelSampler = TRPixelSampler4X<T>;
#else 
	template<typename T>
	using TRPixelSampler = TRPixelSampler1X<T>;
#endif

	using TRPixelRGB = std::array<unsigned char, 3>;
	using TRPixelRGBA = std::array<unsigned char, 4>;
	using TRMaskPixelSampler = TRPixelSampler<unsigned char>;
	using TRDepthPixelSampler = TRPixelSampler<float>;
	using TRColorPixelSampler = TRPixelSampler<TRPixelRGBA>;

	using TRMaskBuffer = std::vector<TRMaskPixelSampler>;
	using TRDepthBuffer = std::vector<TRDepthPixelSampler>;
	using TRColorBuffer = std::vector<TRColorPixelSampler>;

	constexpr TRPixelRGBA trWhite = { 255, 255, 255 ,255 };
	constexpr TRPixelRGBA trBlack = { 0, 0, 0, 0 };
}

#endif