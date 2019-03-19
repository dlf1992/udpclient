// udpclient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;
int main()
{
	WSADATA wsadata;
	if (WSAStartup(WINSOCK_VERSION, &wsadata) != 0)
	{
		cout << "WSAStartup Failed" << endl;
		return 0;
	}
	SOCKET m_socket;
	m_socket = socket(AF_INET,SOCK_DGRAM,0);
	if (INVALID_SOCKET == m_socket)
	{
		cout << "socket create failed" << endl;
		return 0;
	}
	bool val = true;
	if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&val, sizeof(val)) != 0)
	{
		cout << "set reuseaddr failed" << endl;
		return 0;
	}
	bool bBroadcast = true;
	if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (const char*)&bBroadcast, sizeof(bBroadcast)) != 0)
	{
		cout << "set broadcast failed" << endl;
		return 0;
	}
	unsigned   long   maxsize = 65535;
	if (setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (const char*)&maxsize, sizeof(maxsize)) != 0)
	{
		cout << "set sendbufsize failed" << endl;
		return 0;
	}
	if (setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&maxsize, sizeof(maxsize)) != 0)
	{
		cout << "set rcvbufsize failed" << endl;
		return 0;
	}
	unsigned long arg = 1;
	if (ioctlsocket(m_socket, FIONBIO, &arg) != 0) //非阻塞方式
	{
		cout << "set nonblocking failed" << endl;
		return 0;
	}
	while (true)
	{
		const char sendbuf[] = "hello,world!";
		SOCKADDR_IN desaddr;
		desaddr.sin_family = AF_INET;
		//desaddr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");
		desaddr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
		desaddr.sin_port = htons(8000);
		if (sendto(m_socket, sendbuf, sizeof(sendbuf), 0, (sockaddr*)&desaddr, sizeof(sockaddr)) == 0)
		{
			cout << "send error" << endl;
		}
		Sleep(1000);
	}
	//std::cout << "Hello World!\n"; 
	system("pause");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
