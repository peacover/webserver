/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:12:48 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/13 05:36:01 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFile.hpp"

ConfigFile::ConfigFile()
{
    throw ParsingConfigFileException(strdup("No config file is submitted"));
}

ConfigFile::ConfigFile(std::string path)
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
    menu(path);
}

ConfigFile::~ConfigFile()
{
    
}

void ConfigFile::menu(std::string path)
{
    std::string line;
    std::ifstream file(path.c_str());
    if (file)
    {
        while (getline(file, line))
        {
            ConfigFile 
            std::cout << line << std::endl;
        }
        file.close();
    }
    else
        throw ParsingConfigFileException(strdup("File invalid!"));
}
