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
    _port.clear();
    _root.clear();
    _allow_methods.clear();
    _upload_path.clear();
    _index.clear();
    _error_page.clear();
    _autoindex = false;
    _redirection.clear();
    _cgi.clear();
    _location.clear();
}

ServerConfig::~ServerConfig()
{

}