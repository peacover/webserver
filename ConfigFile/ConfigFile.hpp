/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:05:43 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/22 19:22:54 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ServerConfig.hpp"
#include "../Request/Request.hpp"

class ConfigFile
{
	public:

		ConfigFile();
		ConfigFile(std::string path);
		virtual ~ConfigFile();
		
		void menu(std::string path);
		void fill_serv_infos();
		std::pair<int, int> check_server(std::vector<std::string>::iterator &it, int &start);
		void handling_single_server(int start, int end, ServerConfig &single_serv);
		void menu_single_serv(std::vector<std::string>::iterator &it_line, std::string first_word, ServerConfig &single_serv);
		Location handling_location(std::vector<std::string>::iterator &it_line);
		void fix_duplicated_elements(ServerConfig &single_serv);
		void print_infos();
		
		std::map<int , Request> getStoredRequest() const; // the only thing that you need in request
		std::vector<ServerConfig> getServers() const;
		void setStoredRequest(int fd_client, Request rq);
		
		class ParsingConfigFileException : public std::exception
        {
            public:
				ParsingConfigFileException(char *str) : _str(str){};
                const char* what() const throw()
                {
					char *s;

					strcpy(s, "ParsingConfigFileException : ");
					strcat(s, _str);
					if (_str)
						free(_str);
                    return (s);
                }
				char *_str;
			private:
        };
	private:
		std::vector<ServerConfig> _servers;
		std::vector<std::string> _file_data;

		std::map<int , Request> _stored_request; // first : fd_client | second : class request of that fd_client
};