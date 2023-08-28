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
		/// @brief パディング | Padding
		struct Padding
		{
			/// @brief 上辺のパディング（ピクセル） | The top padding in pixels
			double top = 0.0;

			/// @brief 右辺のパディング（ピクセル） | The right padding in pixels
			double right = 0.0;

			/// @brief 下辺のパディング（ピクセル） | The bottom padding in pixels
			double bottom = 0.0;

			/// @brief 左辺のパディング（ピクセル） | The left padding in pixels
			double left = 0.0;

			SIV3D_NODISCARD_CXX20
			Padding() = default;

			SIV3D_NODISCARD_CXX20
			constexpr Padding(double padding) noexcept;

			/// @brief パディングを作成します。 | Creates padding.
			/// @param _topBottom 上下のパディングの高さ（ピクセル） | The height of the top and bottom padding in pixels
			/// @param _rightLeft 左右のパディングの幅（ピクセル） | The width of the left and right padding in pixels
			SIV3D_NODISCARD_CXX20
			constexpr Padding(double _topBottom, double _rightLeft) noexcept;

			/// @brief　パディングを作成します。 | Creates padding.
			/// @param _top 上辺のパディング（ピクセル） | The top padding in pixels
			/// @param _rightLeft 右辺と左辺のパディング（ピクセル） | The right and left padding in pixels
			/// @param _bottom 下辺のパディング（ピクセル） | The bottom padding in pixels
			SIV3D_NODISCARD_CXX20
			constexpr Padding(double _top, double _rightLeft, double _bottom) noexcept;

			/// @brief パディングを作成します。 | Creates padding.
			/// @param _top 上辺のパディング（ピクセル） | The top padding in pixels
			/// @param _right 右辺のパディング（ピクセル） | The right padding in pixels
			/// @param _bottom 下辺のパディング（ピクセル） | The bottom padding in pixels
			/// @param _left 左辺のパディング（ピクセル） | The left padding in pixels
			SIV3D_NODISCARD_CXX20
			constexpr Padding(double _top, double _right, double _bottom, double _left) noexcept;

			[[nodiscard]]
			constexpr Vec2 topLeft() const noexcept;

			[[nodiscard]]
			constexpr Vec2 topRight() const noexcept;

			[[nodiscard]]
			constexpr Vec2 bottomRight() const noexcept;

			[[nodiscard]]
			constexpr Vec2 bottomLeft() const noexcept;

			/// @brief 左辺と右辺のパディングの合計を返します。 | Returns the sum of the left and right padding.
			/// @return 左辺と右辺のパディングの合計 | The sum of the left and right padding
			[[nodiscard]]
			constexpr double totalWidth() const noexcept;

			/// @brief 上辺と下辺のパディングの合計を返します。 | Returns the sum of the top and bottom padding.
			/// @return 上辺と下辺のパディングの合計 | The sum of the top and bottom padding
			[[nodiscard]]
			constexpr double totalHeight() const noexcept;

			/// @brief 2 つのパディングを線形補間します。 | Performs a linear interpolation between two paddings.
			/// @param other 他方のパディング | The other padding
			/// @param f 補間係数 | The interpolation coefficient
			/// @return 補間結果 | The result of interpolation
			[[nodiscard]]
			constexpr Padding lerp(const Padding& other, double f) const noexcept;

			/// @brief すべての値が 0 であるパディングを返します。 | Returns a padding with all values set to 0.
			/// @return すべての値が 0 であるパディング | A padding with all values set to 0
			[[nodiscard]]
			static constexpr Padding Zero() noexcept;

			/// @brief すべての値が value であるパディングを返します。 | Returns a padding with all values set to value.
			/// @param value すべての値 | The value
			/// @return すべての値が value であるパディング | A padding with all values set to value
			[[nodiscard]]
			static constexpr Padding All(double value) noexcept;
		};
	}
}

# include "detail/Padding.ipp"
