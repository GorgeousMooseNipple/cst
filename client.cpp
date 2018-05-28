#include "netinet/in.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	// Cоздание сокета клиента
	
	int clientSocket;
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket < 0)
	{
		//perror("clientSocket");
		return 1;
	}

	std::cout << "Socket created" << std::endl;
	

	// Адрес сервера
	sockaddr_in connectionAddress;
	connectionAddress.sin_family = AF_INET;
	connectionAddress.sin_port = htons(56789);
	inet_aton("192.168.56.1", &connectionAddress.sin_addr);
	//inet_pton(AF_INET,"192.168.56.1", &connectionAddress.sin_addr);
	
	socklen_t connectionSize = sizeof(connectionAddress);
	
	
	int connect;
	// Количество байт ответа от сервера 
	int response;
	// Буфер дя записи ответа от сервера
	char buf[11];
	


	// Клиент ожидает ответ от сервера, данные с сервера выводятся в консоль
	while (true)
	{

                 std::string pas;
	         std::cout << "Input password: " << std::endl;
	         std::cin >> pas;
	         std::cout << std::endl;

	         //клиент посылает серверу пароль, одновременно оповещая его о подключении
	         connect = sendto(clientSocket, pas.c_str(), pas.length(), 0, (struct sockaddr*) &connectionAddress, sizeof(connectionAddress));

		int response = recvfrom(clientSocket, buf, 11, 0, (struct sockaddr*) &connectionAddress, &connectionSize);
		if (response > 0)
			std::cout << buf << std::endl;
	}

	return 0;
}
