#pragma once

// C++ standard
#include <cstdint>

namespace settings
{
	namespace detail
	{
		enum class BytesPerPixel
		{
			RGBA = 4
		};
	}

	const constexpr char* APPLICATION_NAME = "Software rasterizer | Tahar Meijs";
	
	const constexpr std::uint32_t WINDOW_WIDTH = 1280;
	const constexpr std::uint32_t WINDOW_HEIGHT = 720;

	const constexpr detail::BytesPerPixel BYTES_PER_PIXEL = detail::BytesPerPixel::RGBA;
}