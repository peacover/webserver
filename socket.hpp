/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:04:11 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/24 00:00:16 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include "Request/Request.hpp"
#include "ConfigFile/ConfigFile.hpp"
#include "ConfigFile/ServerConfig.hpp"

// read all requests (stored in read in select function)

#define NUMBER_SERVERS 5

class Socket
{
    public:
        Socket(){};
        ~Socket(){};
        void receive_request();
        void send_response();
        
        void create_socket(ServerConfig &serv); 
        int	accept_socket(int fd); // don't forget to clear fd
		void handling_socket(ConfigFile cf);
		int search_fd(int i, std::vector<ServerConfig> serv);
    private:
        // int                 _server_socket_fd;
};

void    Socket::create_socket(ServerConfig &serv)
{
	//to replace with parsed port and host
    int port = serv.getListen().second;
	int yes = 1;
	std::string host = serv.getListen().first;

	struct sockaddr_in serv_addr;
	int addr_len = sizeof(serv_addr);
	std::cout << port << std::endl;
	std::cout << host << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	if ((serv._server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // 0 == use TCP
	{
		perror("ERROR : CREATION OF SOCKET!");
		exit(EXIT_FAILURE);
	}
	setsockopt(serv._server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if(fcntl(serv._server_socket_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("ERROR : NONBLOCK ERROR!");
		exit(EXIT_FAILURE);
	}
	bzero(&serv_addr, addr_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	// serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // any incoming addr
	serv_addr.sin_addr.s_addr = inet_addr(host.c_str());

	if (bind(serv._server_socket_fd, (struct sockaddr *)&serv_addr, addr_len) < 0)
	{
		perror("ERROR : BIND ERROR!");
		exit(EXIT_FAILURE);
	}
	if (listen(serv._server_socket_fd, 3) < 0) // allow 3 requests to queue up
	{
		perror("ERROR : LISTEN ERROR!");
		exit(EXIT_FAILURE);
	}
}

int    Socket::accept_socket(int fd)
{
	int client_socket_fd;
    struct sockaddr_in client_addr;

    int client_addr_len = sizeof(client_addr);
    if ((client_socket_fd = accept(fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len)) < 0)
    {
        perror("ERROR : ACCEPT ERROR!");
        exit(EXIT_FAILURE);
    }
	return (client_socket_fd);
}

int Socket::search_fd(int i, std::vector<ServerConfig> servs)
{
	std::vector<ServerConfig>::iterator it_serv;
	for (it_serv = servs.begin(); it_serv != servs.end(); it_serv++)
	{
		// std::cout << "server_fd : " << (*it_serv)._server_socket_fd << " | looking for: " << i << std::endl;
		if ((*it_serv)._server_socket_fd == i)
			return (i);
	}
	return (-1);
}

void    Socket::handling_socket(ConfigFile cf)
{
	long ret_read;
	int fd_client;
	int rs;
	int max_fd;
	fd_set read_set, write_set;
	fd_set tmp_write_set, tmp_read_set;
	
	std::vector<ServerConfig> servs = cf.getServers();
	std::vector<ServerConfig>::iterator it_serv;
	FD_ZERO(&read_set);
	FD_ZERO(&write_set);
	for (it_serv = servs.begin(); it_serv != servs.end(); it_serv++)
	{
		create_socket(*it_serv);
		// std::cout << "master_socket_fd : " << (*it_serv)._server_socket_fd << std::endl;
		FD_SET((*it_serv)._server_socket_fd, &read_set);
		if ((*it_serv)._server_socket_fd > max_fd)
			max_fd = (*it_serv)._server_socket_fd;
	}
	while(1)
	{
		// the select function allows you to check on several different sockets or pipes
		// returs the total number of ready descriptors in all the sets
		// params : size of what we want to work with (FD_SETSIZE is the max), fd ready to read, fd ready to write, have an exceptional condition pending,
			//time to wait if it is null it specifies a maximum interval to wait

		//keep_alive : true = set to read and clear in write | false = clear in write
		
		struct timeval timeout;
		{
			timeout.tv_sec = 20;
			timeout.tv_usec = 0;
		};
		FD_ZERO(&tmp_read_set);
		FD_ZERO(&tmp_write_set);
		FD_COPY(&read_set, &tmp_read_set);
		FD_COPY(&write_set, &tmp_write_set);
		// tmp_read_set = read_set;
		// tmp_write_set = write_set;
		// select can handle around 1024 sockets in one shot

		if ((rs = select(max_fd + 1, &tmp_read_set, &tmp_write_set, NULL, &timeout)) < 0)
		{
			perror("ERROR : SELECT ERROR!");
			exit(EXIT_FAILURE);
		}
		if (!rs)
		{
			printf("select time_out !!\n");
			continue;
		}
		else
		{
			for (int i = 0; i < max_fd + 1; i++)
			{
				// std::cout << " fd : " << i << " | val : " << _server_socket_fd << std::endl;
				if (FD_ISSET(i, &tmp_read_set))
				{
					// check list of accepted sockets
					// if !null handle sockets (recv and send fd from fd_master) | dont forget keep_alive cases !
					int fd_master = search_fd(i, servs);
					if (fd_master != -1)
					{
						// std::cout << "accepted" << std::endl;
						fd_client = accept_socket(fd_master);
						// map[fd_client](bufff, ret_read);
						FD_SET(fd_client, &read_set);
						if (fd_client > max_fd)
							max_fd = fd_client;
					}
					else
					{
						char bufff[1024];
						ret_read = read(fd_client, bufff, 1024);
						Request r(bufff, ret_read);
						if (ret_read == 0 || cf.getStoredRequest()[fd_client].getIsFinished())
						{
							std::cout << "close file  !! " << std::endl;
							cf.getStoredRequest()[fd_client].close_file();
							FD_SET(fd_client, &write_set);
							FD_CLR(fd_client, &read_set);
							return;
						}
						// if (ret_read == 0)
						// {
							// Request r(bufff, ret_read);
							// cf.setStoredRequest(fd_client, r);
							// FD_SET(fd_client, &write_set);
							// FD_CLR(fd_client, &read_set);
						// }
						// if (map[fd].is)
						if (ret_read > 0)
						{
							// std::cout << "3afak " << std::endl;
							cf.setStoredRequest(fd_client, r);	
						}
						else
						{
							FD_CLR(fd_client, &read_set);
							close(fd_client);
							perror("READ PROBLEM ! ");
							exit(EXIT_FAILURE);
						}
					}
				}
				// else if (FD_ISSET(fd_client, &tmp_write_set))
				// {
				// 	if ((ret = send(fd_client, buf, sizeof(buf), 0)) < 0)
				// 	{
				// 		FD_CLR(fd_client, &read_set);
				// 		close(fd_client);
				// 		perror("ERROR : RECV ERROR!");
				// 		exit(EXIT_FAILURE);		
				// 	}
				// 	else
				// 	{
				// 		//handle keep_alive case
				// 		printf("send success!");
				// 		FD_CLR(fd_client, &write_set);
				// 		close(fd_client);
				// 	}
				// }
			}
		}
	}
		
}
	
  