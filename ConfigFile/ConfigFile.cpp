/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:12:48 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/13 18:26:29 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFile.hpp"

ConfigFile::ConfigFile()
{
    throw ParsingConfigFileException(strdup("No config file is submitted"));
}

ConfigFile::ConfigFile(std::string path)
{
    _servers.clear();
    _single_serv_infos.clear();
    _file_data.clear();
    menu(path);
}

ConfigFile::~ConfigFile()
{
    
}

std::pair<int, int> ConfigFile::check_server(std::vector<std::string>::iterator &it, int &start)
{
    int tmp_start = 0;
    for (it = _file_data.begin() + start; it != _file_data.end(); it++)
    {
        //search for server from the first bracket to the last one
        start++;
    }
    return(std::make_pair(tmp_start, start));
}

void ConfigFile::handling_single_server(int start, int end)
{
    
}

void ConfigFile::fill_serv_infos()
{
    std::vector<std::string>::iterator it;
    std::pair<int, int> p;
    int start = 1;
    for (it = _file_data.begin(); it != _file_data.end(); it++)
    {
        p = check_server(it, start);
        handling_single_server(p.first, p.second);
        // std::cout << *it << std::endl;
        return;
    }
}

void ConfigFile::menu(std::string path)
{
    std::string line;
    std::ifstream file(path.c_str());
    if (file)
    {
        while (getline(file, line))
            _file_data.push_back(line);
        file.close();
    }
    else
        throw ParsingConfigFileException(strdup("File invalid!"));
    fill_serv_infos();
}
