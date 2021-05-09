﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/AudioFormat/OggVorbisEncoder.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/BlobWriter.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/vorbis/vorbisenc.h>
#	include <ThirdParty-prebuilt/vorbis/vorbisfile.h>
# else
#	include <vorbis/vorbisenc.h>
#	include <vorbis/vorbisfile.h>
# endif

namespace s3d
{
	//StringView WAVEEncoder::name() const
	//{
	//	return U"WAVE"_sv;
	//}

	//const Array<String>& WAVEEncoder::possibleExtensions() const
	//{
	//	static const Array<String> extensions = { U"wav" };

	//	return extensions;
	//}

	//bool WAVEEncoder::save(const Wave& wave, const FilePathView path) const
	//{
	//	return save(wave, path, WAVEFormat::Default);
	//}

	//bool WAVEEncoder::save(const Wave& wave, const FilePathView path, const WAVEFormat format) const
	//{
	//	BinaryWriter writer{ path };

	//	if (not writer)
	//	{
	//		return false;
	//	}

	//	return encode(wave, writer, format);
	//}

	//bool WAVEEncoder::encode(const Wave& wave, IWriter& writer) const
	//{
	//	return encode(wave, writer, WAVEFormat::Default);
	//}

	//bool WAVEEncoder::encode(const Wave& wave, IWriter& writer, const WAVEFormat format) const
	//{
	//	if (!wave || !writer.isOpen())
	//	{
	//		return false;
	//	}

	//	const uint16 bitsWidth = format == WAVEFormat::StereoUint8 ? 1
	//		: format == WAVEFormat::StereoSint16 ? 2 : 4;
	//	const uint16 channels = 2;
	//	const uint32 sampleRate = wave.samplingRate();
	//	const size_t waveSize = wave.size() * channels * bitsWidth;

	//	const uint32 headerSize = sizeof(RiffHeader) + sizeof(ChunkHeader) + sizeof(FormatHeader) + sizeof(ChunkHeader);

	//	const RiffHeader riffHeader
	//	{
	//		{ 'R', 'I', 'F', 'F' },
	//		static_cast<uint32>(waveSize + headerSize - 8),
	//		{ 'W', 'A', 'V', 'E' },
	//	};

	//	const ChunkHeader chunkHeader1
	//	{
	//		{ 'f', 'm', 't', ' ' },
	//		sizeof(FormatHeader),
	//	};

	//	const FormatHeader formatHeader
	//	{
	//		uint16((format == WAVEFormat::StereoFloat32) ? WAVE_FORMAT_IEEE_FLOAT : 1),
	//		channels,
	//		sampleRate,
	//		sampleRate * bitsWidth * channels,
	//		uint16(bitsWidth * channels),
	//		uint16(bitsWidth * 8),
	//	};

	//	const ChunkHeader chunkHeader2
	//	{
	//		{ 'd', 'a', 't', 'a' },
	//		static_cast<uint32>(waveSize),
	//	};

	//	writer.write(&riffHeader, sizeof(riffHeader));
	//	writer.write(&chunkHeader1, sizeof(chunkHeader1));
	//	writer.write(&formatHeader, sizeof(formatHeader));
	//	writer.write(&chunkHeader2, sizeof(chunkHeader2));

	//	if (format == WAVEFormat::StereoUint8)
	//	{
	//		size_t samplesToWrite = wave.size();

	//		const uint32 bufferSize = 16384;
	//		Array<WS8bit> buffer(bufferSize);

	//		const WaveSample* pSrc = &wave[0];

	//		for (;;)
	//		{
	//			WS8bit* pDst = buffer.data();

	//			if (samplesToWrite > bufferSize)
	//			{
	//				for (uint32 i = 0; i < bufferSize; ++i)
	//				{
	//					pDst->left = static_cast<uint8>((pSrc->left + 1.0f) * 127.999f);
	//					pDst->right = static_cast<uint8>((pSrc->right + 1.0f) * 127.999f);
	//					++pDst;
	//					++pSrc;
	//				}

	//				writer.write(buffer.data(), bufferSize * sizeof(WS8bit));

	//				samplesToWrite -= bufferSize;
	//			}
	//			else
	//			{
	//				for (uint32 i = 0; i < samplesToWrite; ++i)
	//				{
	//					pDst->left = static_cast<uint8>((pSrc->left + 1.0f) * 127.999f);
	//					pDst->right = static_cast<uint8>((pSrc->right + 1.0f) * 127.999f);
	//					++pDst;
	//					++pSrc;
	//				}

	//				writer.write(buffer.data(), samplesToWrite * sizeof(WS8bit));

	//				break;
	//			}
	//		}
	//	}
	//	else if (format == WAVEFormat::StereoSint16)
	//	{
	//		size_t samplesToWrite = wave.size();

	//		const uint32 bufferCount = 16384;
	//		Array<WaveSampleS16> buffer(bufferCount);

	//		const WaveSample* pSrc = &wave[0];

	//		for (;;)
	//		{
	//			WaveSampleS16* pDst = buffer.data();

	//			if (samplesToWrite > bufferCount)
	//			{
	//				for (uint32 i = 0; i < bufferCount; ++i)
	//				{
	//					pDst->left = static_cast<int16>(pSrc->left * 32767.0f);
	//					pDst->right = static_cast<int16>(pSrc->right * 32767.0f);
	//					++pDst;
	//					++pSrc;
	//				}

	//				writer.write(buffer.data(), bufferCount * sizeof(WaveSampleS16));

	//				samplesToWrite -= bufferCount;
	//			}
	//			else
	//			{
	//				for (uint32 i = 0; i < samplesToWrite; ++i)
	//				{
	//					pDst->left = static_cast<int16>(pSrc->left * 32767.0f);
	//					pDst->right = static_cast<int16>(pSrc->right * 32767.0f);
	//					++pDst;
	//					++pSrc;
	//				}

	//				writer.write(buffer.data(), samplesToWrite * sizeof(WaveSampleS16));

	//				break;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		writer.write(wave.data(), waveSize);
	//	}

	//	return true;
	//}

	//Blob WAVEEncoder::encode(const Wave& wave) const
	//{
	//	return encode(wave, WAVEFormat::Default);
	//}

	//Blob WAVEEncoder::encode(const Wave& wave, const WAVEFormat format) const
	//{
	//	BlobWriter writer;

	//	if (not encode(wave, writer, format))
	//	{
	//		return{};
	//	}

	//	return writer.retrieve();
	//}
}
