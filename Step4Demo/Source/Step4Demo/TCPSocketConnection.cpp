#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "TCPSocketConnection.h"
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <string>

#define PORT 8001
#define PACKET_SIZE 1024

DEFINE_LOG_CATEGORY_STATIC(MyNetworkLog, Log, All);

class NetworkClass {
public:
	bool performConversion(const FString& ip_str, ULONG& ip_long) {
		TArray<FString> tokens;
		ip_str.ParseIntoArray(tokens, TEXT("."));

		if (tokens.Num() != 4) return false; // we expect 4 tokens for an IP address

		uint32 bytes[4] = {};

		for (int32 i = 0; i < 4; i++) {

			if (tokens[i].IsNumeric()) { // Check if the string is a valid number
				bytes[i] = FCString::Atoi(*tokens[i]);
				if (bytes[i] < 0 || bytes[i] > 255) {
					return false; // not a valid IP address component
				}
			}
			else return false;
		}

		// Use htonl
		ip_long = (bytes[0] << 24) |
			(bytes[1] << 16) |
			(bytes[2] << 8) |
			(bytes[3]);
		ip_long = htonl(ip_long);

		return true;
	}
};


//클라이언트 TCP/IP 요청
FString UTCPSocketConnection::connectToServer(FString ipAddress)
{
	NetworkClass ipConverter;
	ULONG ipAddress_ULONG;

	UE_LOG(MyNetworkLog, Log, TEXT("Attempting connection to: %s"), *ipAddress);

	//일반 스트링 형 변환
	if (!ipConverter.performConversion(ipAddress, ipAddress_ULONG)) {
		UE_LOG(MyNetworkLog, Error, TEXT("Connection failed - Invalid IP address: %s"), *ipAddress);
		return TEXT("접속 실패 - 틀린 IP주소");
	}


	//TODO: disconnect existing connection. Then open port to make it avaiable to use.

	WSADATA wsaData; //Windows Socket data storage
	WSAStartup(((WORD)(((BYTE)(((DWORD_PTR)(2)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(2)) & 0xff))) << 8)), &wsaData); // initialize WSADATA Object address to store WSA data based on the socket version(MAKEWORD(2, 2))

	/**
	 * socket 초기화
	 * PF_INET - IPv4
	 * SOCK_STREAM  - Constant connection
	 * IPPROTO_TCP - TCP/IP Protocol
	 */
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//validity check
	if (hSocket == INVALID_SOCKET) {
		WSACleanup();
		UE_LOG(MyNetworkLog, Error, TEXT("Connection failed - Socket creation error"));
		return TEXT("접속 실패 - 소켓 생성 오류");
	}

	SOCKADDR_IN tAddress = {};
	tAddress.sin_family = AF_INET; //TCP 방식 선언
	tAddress.sin_port = htons(PORT); //host to network short - 빅에디안 프로토콜 전송방식
	tAddress.sin_addr.s_addr = htonl(ipAddress_ULONG); //목적지 ip설정


	int iResult = connect(hSocket, (SOCKADDR*)&tAddress, sizeof(tAddress)); //접속 시도
	if (iResult == SOCKET_ERROR) {
		int iResultError = WSAGetLastError();

		closesocket(hSocket);
		WSACleanup();

		char errorBuffer[256];
		sprintf_s(errorBuffer, "Connection failed - WSA Error Code: %d", iResultError);
		FString errorString = errorBuffer;

		UE_LOG(MyNetworkLog, Error, TEXT("%s"), *errorString);

		return TEXT("접속 실패 - 연결 거부");
	}

	//close connection on close - implement destructor?
	closesocket(hSocket);

	WSACleanup();
	UE_LOG(MyNetworkLog, Log, TEXT("Success connecting to: %s"), *ipAddress);
	return TEXT("접속 성공");
}
