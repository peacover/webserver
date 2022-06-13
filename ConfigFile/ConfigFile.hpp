/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:05:43 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/13 05:19:25 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream> 
#include <unistd.h> 
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <exception>
#include <fstream>

#include "Location.hpp"

class ConfigFile
{
	public:

		ConfigFile();
		ConfigFile(std::string path);
		virtual ~ConfigFile();
		
		std::string getHost() const;
		std::string getPort() const;
		std::string getRoot() const;
		std::vector<std::string> getAllowMethods() const;
		std::string getUploadPath() const;
		std::string getIndex() const;
		std::vector<std::pair<int, std::string> > getErrorPage() const;
		bool getAutoIndex() const;
		std::vector<std::pair<std::string, std::string> > getRedirection() const;
		std::vector<std::pair<std::string, std::string> > getCgi() const;
		std::vector<Location> getLocation() const;

		void menu(std::string path);
		
		class ParsingConfigFileException : public std::exception
        {
            public:
				ParsingConfigFileException(char *str) : _str(str){};

                const char* what() const throw()
                {
					char *s = strdup("ParsingConfigFileException : ");
                    return (strcat(s, _str));
                }
			private:
				char *_str;
        };
	private:
		std::string	_host;
		std::string	_port;
		std::string	_root;
		std::vector<std::string> _allow_methods;
		std::string	_upload_path;
		std::string _index;
		std::vector<std::pair<int, std::string> > _error_page; // first : error index | second : path error
		bool	_autoindex;
		std::vector<std::pair<std::string, std::string> > _redirection; // first : first_path | second : second_path
		std::vector<std::pair<std::string, std::string> > _cgi; // first : extension | second : path 
		std::vector<Location> _location;
		std::vector<ConfigFile> _servers;
};