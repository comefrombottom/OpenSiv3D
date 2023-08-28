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
		/// @brief ボックスシャドウ | Box shadow
		struct BoxShadow
		{
			Vec2 offset{ 0, 0 };

			double blur = 0.0;

			double spread = 0.0;

			ColorF color = ColorF{ 0.0, 0.5 };
		};
	}
}
