/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:05:43 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/16 18:38:21 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ServerConfig.hpp"

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
		void print_infos();
		
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
};