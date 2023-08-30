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
		struct Padding;
		struct Margin;
		struct BoxShadow;
	
		class UICanvas;
		
		using UIElementName = String;
		using UIElementNameView = StringView;
		class UIElement;

		using UIContainerName = String;
		using UIContainerNameView = StringView;
		class UIContainer;
		
		class UIPanel;
		class UIWindow;

		class ColorRect;
	}
}
