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

namespace s3d
{
	inline namespace UI1
	{
		inline constexpr Padding::Padding(const double padding) noexcept
			: top{ padding }
			, right{ padding }
			, bottom{ padding }
			, left{ padding } {}

		inline constexpr Padding::Padding(const double _topBottom, const double _rightLeft) noexcept
			: top{ _topBottom }
			, right{ _rightLeft }
			, bottom{ _topBottom }
			, left{ _rightLeft } {}

		inline constexpr Padding::Padding(const double _top, const double _rightLeft, const double _bottom) noexcept
			: top{ _top }
			, right{ _rightLeft }
			, bottom{ _bottom }
			, left{ _rightLeft } {}

		inline constexpr Padding::Padding(const double _top, const double _right, const double _bottom, const double _left) noexcept
			: top{ _top }
			, right{ _right }
			, bottom{ _bottom }
			, left{ _left } {}

		inline constexpr Vec2 Padding::topLeft() const noexcept
		{
			return{ left, top };
		}

		inline constexpr Vec2 Padding::topRight() const noexcept
		{
			return{ right, top };
		}

		inline constexpr Vec2 Padding::bottomRight() const noexcept
		{
			return{ right, bottom };
		}

		inline constexpr Vec2 Padding::bottomLeft() const noexcept
		{
			return{ left, bottom };
		}

		inline constexpr double Padding::totalWidth() const noexcept
		{
			return (left + right);
		}

		inline constexpr double Padding::totalHeight() const noexcept
		{
			return (top + bottom);
		}

		inline constexpr Padding Padding::lerp(const Padding& other, const double f) const noexcept
		{
			return{
				Math::Lerp(top, other.top, f),
				Math::Lerp(right, other.right, f),
				Math::Lerp(bottom, other.bottom, f),
				Math::Lerp(left, other.left, f)
			};
		}

		inline constexpr Padding Padding::Zero() noexcept
		{
			return{ 0, 0, 0, 0 };
		}

		inline constexpr Padding Padding::All(const double value) noexcept
		{
			return{ value, value, value, value };
		}
	}
}
