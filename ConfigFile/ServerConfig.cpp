/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:37:26 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/13 16:37:26 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
{
    _host.clear();
    _root.clear();
    _allow_methods.clear();
    _upload_path.clear();
    _index.clear();
    _error_page.clear();
    _autoindex = false;
    _cgi.clear();
    _location.clear();
}

ServerConfig::~ServerConfig()
{
    
}


std::string ServerConfig::getHost() const 
{
    return (_host);
}
int ServerConfig::getPort() const 
{
    return (_port);
}
std::string ServerConfig::getRoot() const 
{
    return (_root);
}
std::vector<std::string> ServerConfig::getAllowMethods() const 
{
    return (_allow_methods);
}
std::string ServerConfig::getUploadPath() const 
{
    return (_upload_path);
}
std::string ServerConfig::getIndex() const 
{
    return (_index);
}
std::vector<std::pair<int, std::string> > ServerConfig::getErrorPage() const 
{
    return (_error_page);
}
bool ServerConfig::getAutoIndex() const 
{
    return (_autoindex);
}
std::pair<int, std::string> ServerConfig::getRedirection() const 
{
    return (_redirection);
}
std::vector<std::pair<std::string, std::string> > ServerConfig::getCgi() const 
{
    return (_cgi);
}
std::vector<Location> ServerConfig::getLocation() const 
{
    return (_location);
}


void ServerConfig::setHost(std::string host)
{
    _host = host;
}
void ServerConfig::setPort(int port)
{
    _port = port;
}
void ServerConfig::setRoot(std::string root)
{
    _root = root;
}
void ServerConfig::setAllowMethods(std::vector<std::string> allow_methode)
{
    _allow_methods = allow_methode;
}
void ServerConfig::setUploadPath(std::string upload_path)
{
    _upload_path = upload_path;
}
void ServerConfig::setIndex(std::string index)
{
    _index = index;
}
void ServerConfig::setErrorPage(std::pair<int, std::string> error_page)
{
    _error_page.push_back(error_page);
}
void ServerConfig::setAutoIndex(bool auto_index)
{
    _autoindex = auto_index;
}
void ServerConfig::setRedirection(std::pair<int, std::string>  redirection)
{
    _redirection = redirection;
}
void ServerConfig::setCgi(std::pair<std::string, std::string> cgi)
{
    _cgi.push_back(cgi);

    // std::cout << _cgi.back().first << " | " << _cgi.back().second << std::endl;
    // std::cout << "check02------------------------" << std::endl;     

    
}
void ServerConfig::setLocation(std::vector<Location> location)
{
    _location = location;
}