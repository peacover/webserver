/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:31:40 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/13 16:31:40 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream> 
#include <unistd.h> 
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iterator>
#include <exception>
#include <fstream>


#include <cstring>
#include "Location.hpp"

class ServerConfig
{
	public:

		ServerConfig();
		virtual ~ServerConfig();
		
		std::string getHost() const;
		int getPort() const;
		std::string getRoot() const;
		std::vector<std::string> getAllowMethods() const;
		std::string getUploadPath() const;
		std::string getIndex() const;
		std::vector<std::pair<int, std::string> > getErrorPage() const;
		bool getAutoIndex() const;
		std::pair<int, std::string> getRedirection() const;
		std::vector<std::pair<std::string, std::string> > getCgi() const;
		std::vector<Location> getLocation() const;

		void setHost(std::string host);
		void setPort(int port);
		void setRoot(std::string root);
		void setAllowMethods(std::vector<std::string> allow_methode);
		void setUploadPath(std::string upload_path);
		void setIndex(std::string index);
		void setErrorPage(std::pair<int, std::string> error_page);
		void setAutoIndex(bool auto_index);
		void setRedirection(std::pair<int, std::string> redirection);
		void setCgi(std::pair<std::string, std::string> cgi);
		void setLocation(Location location);


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
		int	_port;
		std::string	_root;
		std::vector<std::string> _allow_methods;
		std::string	_upload_path;
		std::string _index;
		std::vector<std::pair<int, std::string> > _error_page; // first : error index | second : path error
		bool	_autoindex;
		std::pair<int, std::string> _redirection; // first : type redirection | second : path redirection
		std::vector<std::pair<std::string, std::string> > _cgi; // first : extension | second : path 
		std::vector<Location> _location;
};