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
# include "../String.hpp"
# include "UIElement.hpp"

namespace s3d
{
	inline namespace UI1
	{
		using UIContainerName = String;
		using UIContainerNameView = StringView;

		class UIContainer : public UIElement, public std::enable_shared_from_this<UIContainer>
		{
		public:

			const UIContainerName& name() const noexcept;

		private:

		};
	}
}
