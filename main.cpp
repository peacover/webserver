/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:36:44 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/11 03:19:52 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

int main()
{
	// The function returns -1 if there was an error. Otherwise, it will return the file descriptor assigned to the socket.
		// A socket can be seen as a file descriptor that can be used for communication.
		// int socket(int domain, int type, int protocol);
	
	
	// domain refers to the protocol the socket will use for communication. Some possible values are:
		// AF_UNIX, AF_LOCAL - Local communication
		// AF_INET - IPv4 Internet protocols
		// AF_INET6 - IPv6 Internet protocols
		// AF_IPX - IPX Novell protocols
		
	// type specifies if the communication will be conectionless, or persistent. Not all types are compatible with all domains. Some examples are:
		// SOCK_STREAM - Two-way reliable communication (TCP)
		// SOCK_DGRAM - Connectionless, unreliable (UDP)
		
	// protocol: Protocol value for Internet Protocol(IP), which is 0.
		// This is the same number which appears on protocol field in the IP header of a packet.

	// i need only port and host
	// struct sockaddr_in {
	//     sa_family_t    sin_family; /* address family: AF_INET */
	//     in_port_t      sin_port;   /* port in network byte order */
	//     struct in_addr sin_addr;   /* internet address */
	// };
	// The htons() function translates a short integer from host byte order to network byte order.
	// htons is host-to-network short
	// htonl Host TO Network translation

	// int bind(int socket, const struct sockaddr *address, socklen_t address_len);
		// After creation of the socket, bind function binds the socket
			// to the address and port number specified in addr(custom data structure).
	// int listen(int sockfd, int backlog);
		// It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection.
		// backlog is the maximum number of connections that will be queued before connections start being refused.
	// int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
		// The accept system call grabs the first connection request on the queue of pending
			// connections (set up in listen) and creates a new socket for that connection.
		
	// int port = 3030;
	// std::string host = "127.0.0.1";
	// int socket_fd;
	// int client_socket_fd;
	// struct sockaddr_in serv_addr;
	// int addr_len = sizeof(serv_addr);
	
	// if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // 0 == use TCP
	// {
	// 	perror("ERROR : CREATION OF SOCKET!");
	// 	exit(EXIT_FAILURE);
	// }
	// bzero(&serv_addr, addr_len);
	// serv_addr.sin_family = AF_INET;
	// serv_addr.sin_port = htons(port);
	// // serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // The address for this socket we are using our machine's ip address 0.0.0.0 so we can use INADDR_ANY
	// serv_addr.sin_addr.s_addr = inet_addr(host.c_str());
	
	// // not handling clients with same port, we should skip the after first one's
	// if (bind(socket_fd, (struct sockaddr *)&serv_addr, addr_len) < 0)
	// {
	// 	perror("ERROR : BIND ERROR!");
	// 	exit(EXIT_FAILURE);
	// }
	// if (listen(socket_fd, 3) < 0)
	// {
	// 	perror("ERROR : LISTEN ERROR!");
	// 	exit(EXIT_FAILURE);
	// }
	
	// while (1)
	// {
	// 	if ((client_socket_fd = accept(socket_fd, (struct sockaddr *)&serv_addr, (socklen_t *)&addr_len)) < 0)
	// 	{
	// 		perror("ERROR : ACCEPT ERROR!");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	close(client_socket_fd);
	// }

	Socket s;

	s.handling_socket();
	
}