/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:14:56 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/22 22:02:55 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location()
{
    _root.clear();
    _allow_methods.clear();
    _upload_path.clear();
    _index.clear();
    _error_page.clear();
    _autoindex = false;
    _cgi.clear();
}

Location::~Location()
{
    
}


std::string Location::getPath() const 
{
    return (_path);
}
std::pair<std::string, int> Location::getListen() const
{
    return (_listen);
}
std::string Location::getRoot() const 
{
    return (_root);
}
std::vector<std::string> Location::getAllowMethods() const 
{
    return (_allow_methods);
}
std::string Location::getUploadPath() const 
{
    return (_upload_path);
}
std::string Location::getIndex() const 
{
    return (_index);
}
std::vector<std::pair<int, std::string> > Location::getErrorPage() const 
{
    return (_error_page);
}
bool Location::getAutoIndex() const 
{
    return (_autoindex);
}
std::pair<int, std::string> Location::getRedirection() const 
{
    return (_redirection);
}
std::vector<std::pair<std::string, std::string> > Location::getCgi() const 
{
    return (_cgi);
}


void Location::setPath(std::string path)
{
    _path = path;
}
void Location::setListen(std::pair<std::string, int> listen)
{
   _listen = listen;
}
void Location::setRoot(std::string root)
{
    _root = root;
}
void Location::setAllowMethods(std::vector<std::string> allow_methode)
{
    _allow_methods = allow_methode;
}
void Location::setUploadPath(std::string upload_path)
{
    _upload_path = upload_path;
}
void Location::setIndex(std::string index)
{
    _index = index;
}
void Location::setErrorPage(std::pair<int, std::string> error_page)
{
    _error_page.push_back(error_page);
}
void Location::setAutoIndex(bool auto_index)
{
    _autoindex = auto_index;
}
void Location::setRedirection(std::pair<int, std::string>  redirection)
{
    _redirection = redirection;
}
void Location::setCgi(std::pair<std::string, std::string> cgi)
{
    _cgi.push_back(cgi);
}
