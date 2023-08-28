//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "../Common.hpp"

namespace s3d
{
	inline namespace UI1
	{
		/// @brief マージン | Margin
		struct Margin
		{
			/// @brief 上辺のマージン（ピクセル） | The top margin in pixels
			double top = 0.0;

			/// @brief 右辺のマージン（ピクセル） | The right margin in pixels
			double right = 0.0;

			/// @brief 下辺のマージン（ピクセル） | The bottom margin in pixels
			double bottom = 0.0;

			/// @brief 左辺のマージン（ピクセル） | The left margin in pixels
			double left = 0.0;
		};
	}
}
