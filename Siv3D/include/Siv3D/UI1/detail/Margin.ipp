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
		inline constexpr Margin::Margin(const double margin) noexcept
			: top{ margin }
			, right{ margin }
			, bottom{ margin }
			, left{ margin } {}

		inline constexpr Margin::Margin(const double _topBottom, const double _rightLeft) noexcept
			: top{ _topBottom }
			, right{ _rightLeft }
			, bottom{ _topBottom }
			, left{ _rightLeft } {}

		inline constexpr Margin::Margin(const double _top, const double _rightLeft, const double _bottom) noexcept
			: top{ _top }
			, right{ _rightLeft }
			, bottom{ _bottom }
			, left{ _rightLeft } {}

		inline constexpr Margin::Margin(const double _top, const double _right, const double _bottom, const double _left) noexcept
			: top{ _top }
			, right{ _right }
			, bottom{ _bottom }
			, left{ _left } {}

		inline constexpr Margin Margin::Zero() noexcept
		{
			return{ 0, 0, 0, 0 };
		}

		inline constexpr Margin Margin::All(const double value) noexcept
		{
			return{ value, value, value, value };
		}
	}
}
