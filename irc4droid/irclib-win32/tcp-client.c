

//Client
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6667"


int __cdecl main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    char buf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    char *tempbuf;
	char host[100] = "localhost";
    // Validate the parameters
    /*if (argc != 2) {
        printf("usage: %s server-namen", argv[0]);
        return 1;
    }*/
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %dn", iResult);
        return 1;
    }
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    iResult = getaddrinfo(host, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %dn", iResult);
        WSACleanup();
        return 1;
    }
    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ldn", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!n");
        WSACleanup();
        return 1;
    }
    
	//printf("nEnter something: ");
	//scanf("%s",buf);
    // Send an initial buffer
    /*
    iResult = send( ConnectSocket, buf, (int)strlen(buf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %dn", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    printf("Bytes Sent: %ldn", iResult);
    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %dn", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    */
    // Receive until the peer closes the connection
    strcpy(buf, "NICK daniels\n");
    send(ConnectSocket, buf, strlen(buf), 0);
    strcpy(buf, "USER username hostname servername\n");
    send(ConnectSocket, buf, strlen(buf), 0);
    strcpy(buf, "JOIN #imbalance\n");
    //send(ConnectSocket, buf, strlen(buf), 0);
    
    /*
    do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ) {
		//printf("Bytes received: %d\n", iResult);
		tempbuf = (char*)malloc(iResult+1);
		memcpy(tempbuf,recvbuf,iResult);
		//For display reasons
		tempbuf[iResult] = '\0';
		//printf("Buffer received: %s\n", tempbuf);
	}
        else if ( iResult == 0 )
            printf("Connection closedn");
        else
            printf("recv failed with error: %dn", WSAGetLastError());
    } while( iResult > 0 );
    */
    
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}



