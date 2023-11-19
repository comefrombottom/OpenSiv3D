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
# include "../Array.hpp"
# include "../AsyncHTTPTask.hpp"

namespace s3d
{
	namespace OpenAI
	{
		namespace Chat
		{
			namespace Model
			{
				/// @brief GPT-3.5 モデル | GPT-3.5 model
				/// @see https://platform.openai.com/docs/models/gpt-3-5
				/// @remark Chat API 用のモデルです。 | This is a model for the Chat API.
				inline constexpr StringView GPT3_5_Turbo{ U"gpt-3.5-turbo" };

				/// @brief GPT-3.5 モデル（16k トークン） | GPT-3.5 model (16k tokens)
				/// @see https://platform.openai.com/docs/models/gpt-3-5
				/// @remark Chat API 用のモデルです。 | This is a model for the Chat API.
				inline constexpr StringView GPT3_5_Turbo_16K{ U"gpt-3.5-turbo-16k" };

				/// @brief GPT-4 モデル | GPT-4 model
				/// @see https://platform.openai.com/docs/models/gpt-4
				/// @remark Chat API 用のモデルです。 | This is a model for the Chat API.
				inline constexpr StringView GPT4{ U"gpt-4" };

				/// @brief GPT-4 モデル（32k トークン） | GPT-4 model (32k tokens)
				/// @see https://platform.openai.com/docs/models/gpt-4
				/// @remark Chat API 用のモデルです。 | This is a model for the Chat API.
				inline constexpr StringView GPT4_32K{ U"gpt-4-32k" };
			}

			/// @brief ChatGPT にメッセージを送り、その返答メッセージを取得します。 | Sends a message to ChatGPT and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param message メッセージ | Message
			/// @param model 使用するモデル | The model to be used (default: Model::GPT3_5_Turbo)
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, StringView message, StringView model = Model::GPT3_5_Turbo);

			/// @brief ChatGPT にメッセージを送り、その返答メッセージを取得します。 | Sends a message to ChatGPT and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param message メッセージ | Message
			/// @param error エラーメッセージの格納先。エラーが無い場合は空の文字列になる | Destination for the error message. Will be an empty string if no error occurs.
			/// @param model 使用するモデル | The model to be used (default: Model::GPT3_5_Turbo)
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, StringView message, String& error, StringView model = Model::GPT3_5_Turbo);

			/// @brief ChatGPT にメッセージを送り、その返答メッセージを取得します。 | Sends messages to ChatGPT and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param messages メッセージ（ロールとメッセージのペアの配列） | Array of message pairs (role and message)
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @param model 使用するモデル | The model to be used (default: Model::GPT3_5_Turbo)
			/// @remark ロールは U"system", U"user", U"assistant" の 3 種類です。 | Roles are U"system", U"user", and U"assistant".
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, const Array<std::pair<String, String>>& messages, StringView model = Model::GPT3_5_Turbo);

			/// @brief ChatGPT にメッセージを送り、その返答メッセージを取得します。 | Sends messages to ChatGPT and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param messages メッセージ（ロールとメッセージのペアの配列） | Array of message pairs (role and message)
			/// @param error エラーメッセージの格納先。エラーが無い場合は空の文字列になる | Destination for the error message. Will be an empty string if no error occurs.
			/// @param model 使用するモデル | The model to be used (default: Model::GPT3_5_Turbo)
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark ロールは U"system", U"user", U"assistant" の 3 種類です。 | Roles are U"system", U"user", and U"assistant".
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, const Array<std::pair<String, String>>& messages, String& error, StringView model = Model::GPT3_5_Turbo);

			/// @brief ChatGPT にメッセージを送り、レスポンス（JSON）を取得する非同期タスクを返します。 | Returns an asynchronous task for sending a message to ChatGPT and retrieving the response (JSON).
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param message メッセージ | Message
			/// @param model 使用するモデル | The model to be used (default: Model::GPT3_5_Turbo)
			/// @return 非同期タスク | Asynchronous task
			/// @remark 戻り値の task が `(task.isReady() == true) && (task.getResponse().isOK() == true)` になれば結果を取得できます。 | The result can be retrieved if `(task.isReady() == true) && (task.getResponse().isOK() == true)`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncHTTPTask CompleteAsync(StringView apiKey, StringView message, StringView model = Model::GPT3_5_Turbo);

			/// @brief ChatGPT にメッセージを送り、レスポンス（JSON）を取得する非同期タスクを返します。 | Returns an asynchronous task for sending messages to ChatGPT and retrieving the response (JSON).
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param messages メッセージ（ロールとメッセージのペアの配列） | Array of message pairs (role and message)
			/// @param model 使用するモデル | The model to be used (default: Model::GPT3_5_Turbo)
			/// @return 非同期タスク | Asynchronous task
			/// @remark ロールは U"system", U"user", U"assistant" の 3 種類です。 | Roles are U"system", U"user", and U"assistant".
			/// @remark 戻り値の task が `(task.isReady() == true) && (task.getResponse().isOK() == true)` になれば結果を取得できます。 | The result can be retrieved if `(task.isReady() == true) && (task.getResponse().isOK() == true)`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncHTTPTask CompleteAsync(StringView apiKey, const Array<std::pair<String, String>>& messages, StringView model = Model::GPT3_5_Turbo);

			/// @brief ChatGPT のレスポンス（JSON）から、返答メッセージを抽出して返します。 | Extracts and returns the response message from the ChatGPT response (JSON).
			/// @param response JSON レスポンス | JSON response
			/// @return 返答メッセージ。抽出に失敗した場合は空の文字列 | Response message. An empty string if extraction fails.
			/// @remark 通常は `AsyncHTTPTask::getAsJSON()` の戻り値を渡します。 | Typically, pass the return value of `AsyncHTTPTask::getAsJSON()`.
			[[nodiscard]]
			String GetContent(const JSON& response);
		}
	}
}
