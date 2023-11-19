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

namespace s3d
{
	namespace OpenAI
	{
		namespace Speech
		{
			struct Request
			{
				String model = U"tts-1";

				String input;

				String voice = U"alloy";

				String responseFormat = U"mp3";

				double speed = 1.0;
			};

			bool Create(const Request& request, FilePathView path);
		}
	}
}
