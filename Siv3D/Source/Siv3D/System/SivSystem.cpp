﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Include/Siv3D/Platform.hpp"
# if defined (SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include "../../../Include/Siv3D/Fwd.hpp"
# include "../../../Include/Siv3D/Utility.hpp"

namespace s3d
{
	namespace System
	{
		void Sleep(int32 milliseconds)
		{
			if (milliseconds < 0)
			{
				return;
			}

			::timeBeginPeriod(1);

			::Sleep(milliseconds);

			::timeEndPeriod(1);
		}
	}
}

# elif defined (SIV3D_TARGET_OSX)

# include <unistd.h>
# include "../../../Include/Siv3D/Fwd.hpp"
# include "../../../Include/Siv3D/Time.hpp"

namespace s3d
{
	namespace System
	{
        void Sleep(int32 milliseconds)
        {
            if (milliseconds < 0)
            {
                return;
            }

            ::usleep(static_cast<uint32>(milliseconds) * 1000);
        }
	}
}

# endif
