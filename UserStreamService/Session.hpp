#pragma once
#include <Windows.h>

struct SESSION_MESSAGE_HANDLERS
{
	LIST_ENTRY List;
};
typedef struct SESSION_MESSAGE_HANDLERS;

class Session
{
private:
	/// <summary>
	/// 認証の際に使用される文字列のうち、キーとなる文字列です。
	/// </summary>
	char ApiKey[32];
	/// <summary>
	/// 認証の際に使用される文字列のうち、シークレットとなる文字列です。
	/// </summary>
	char ApiSecret[64];
	/// <summary>
	/// 実際の通信で使用されるトークンです。次の形式で表されます。 (AccountID)-(TokenString)
	/// </summary>
	char AccessToken[128];
	/// <summary>
	/// 実際の通信で勝されるトークンです。
	/// </summary>
	char AccessTokenSecret[64];

	/// <summary>
	/// アカウントのIDです。
	/// </summary>
	unsigned long AccountId;

	//
	void * Buffer;
	//
	SESSION_MESSAGE_HANDLERS Handlers;

public:
	/// <summary>
	/// Sessionクラスのインスタンスを生成します。
	/// </summary>
	Session();
	/// <summary>
	/// トークンを指定してSessionクラスのインスタンスを生成します。
	/// </summary>
	Session(const char * const AccessToken, const char * const AccessTokenSecret);
	/// <summary>
	/// セッションを開始します。
	/// </summary>
	void Start();
	/// <summary>
	/// セッションを終了します。
	/// </summary>
	void Stop();
	/// <summary>
	/// セッションのストリームからイベントを受信した際に呼び出されるコールバックを追加します。
	/// </summary>
	void RegisterMessageHandler(void * const Handler);
	/// <summary>
	/// RegisterMessageHandlerメソッドで登録したコールバックを削除します。
	/// </summary>
	void UnregisterMessageHandler(void * const Handler);
	/// <summary>
	/// API Keyを変更します。
	/// </summary>
	void SetApiKey(const TCHAR * const ApiKey, const TCHAR * const ApiSecret);
	/// <summary>
	/// API Keyを送信する為のURIを生成します。
	/// </summary>
	void CreateAuthUri(TCHAR * const Uri, size_t const Size);
	/// <summary>
	/// 認証コードを入力します。
	/// </summary>
	bool SetAuthCode(unsigned int const Code);
private:
	void ClearAccessToken();
	void SetAccessToken(const TCHAR * const Token, const TCHAR * const Secret);
};
