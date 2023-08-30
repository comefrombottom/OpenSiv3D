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
# include "../Interpolation.hpp"

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

			SIV3D_NODISCARD_CXX20
			Margin() = default;

			SIV3D_NODISCARD_CXX20
			constexpr Margin(double margin) noexcept;

			/// @brief マージンを作成します。 | Creates margin.
			/// @param _topBottom 上下のマージンの高さ（ピクセル） | The height of the top and bottom margin in pixels
			/// @param _rightLeft 左右のマージンの幅（ピクセル） | The width of the left and right margin in pixels
			SIV3D_NODISCARD_CXX20
			constexpr Margin(double _topBottom, double _rightLeft) noexcept;

			/// @brief　マージンを作成します。 | Creates margin.
			/// @param _top 上辺のマージン（ピクセル） | The top margin in pixels
			/// @param _rightLeft 右辺と左辺のマージン（ピクセル） | The right and left margin in pixels
			/// @param _bottom 下辺のマージン（ピクセル） | The bottom margin in pixels
			SIV3D_NODISCARD_CXX20
			constexpr Margin(double _top, double _rightLeft, double _bottom) noexcept;

			/// @brief マージンを作成します。 | Creates margin.
			/// @param _top 上辺のマージン（ピクセル） | The top margin in pixels
			/// @param _right 右辺のマージン（ピクセル） | The right margin in pixels
			/// @param _bottom 下辺のマージン（ピクセル） | The bottom margin in pixels
			/// @param _left 左辺のマージン（ピクセル） | The left margin in pixels
			SIV3D_NODISCARD_CXX20
			constexpr Margin(double _top, double _right, double _bottom, double _left) noexcept;

			[[nodiscard]]
			constexpr Vec2 topLeft() const noexcept;

			[[nodiscard]]
			constexpr Vec2 topRight() const noexcept;

			[[nodiscard]]
			constexpr Vec2 bottomRight() const noexcept;

			[[nodiscard]]
			constexpr Vec2 bottomLeft() const noexcept;

			/// @brief 左辺と右辺のマージンの合計を返します。 | Returns the sum of the left and right margin.
			/// @return 左辺と右辺のマージンの合計 | The sum of the left and right margin
			[[nodiscard]]
			constexpr double totalWidth() const noexcept;

			/// @brief 上辺と下辺のマージンの合計を返します。 | Returns the sum of the top and bottom margin.
			/// @return 上辺と下辺のマージンの合計 | The sum of the top and bottom margin
			[[nodiscard]]
			constexpr double totalHeight() const noexcept;

			/// @brief 2 つのマージンを線形補間します。 | Performs a linear interpolation between two margins.
			/// @param other 他方のマージン | The other margin
			/// @param f 補間係数 | The interpolation coefficient
			/// @return 補間結果 | The result of interpolation
			[[nodiscard]]
			constexpr Margin lerp(const Margin& other, double f) const noexcept;

			[[nodiscard]]
			static constexpr Margin Zero() noexcept;

			[[nodiscard]]
			static constexpr Margin All(double value) noexcept;
		};
	}
}

# include "detail/Margin.ipp"
