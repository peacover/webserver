/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:12:48 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/14 03:35:49 by yer-raki         ###   ########.fr       */
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
std::pair<std::string, bool> ConfigFile::after_space(std::string str) // first string after space | true if eof or end of line
{
    std::string s;
    for(int i = 0; i < str.length(); i++)
    {
        if (isspace(str[i]))
            continue;
        else
        {
            for (int j = i; j < str.length(); j++)
            {
                if (isspace(str[j]))
                {
                    for (int k = j; k < str.length(); k++)
                    {
                        if (str[k] == '\n' || str[k] == EOF)
                            return (std::make_pair(s, true));
                        if (!isspace(str[k]))
                            return (std::make_pair(s, false));
                    }
                    return (std::make_pair(s, true));
                }
                else
                {
                    s += str[j];
                    if (j == str.length() - 1)
                        return (std::make_pair(s, true));
                }
            }
        }
    }
    return (std::make_pair(s, true));
}
std::pair<int, int> ConfigFile::check_server(std::vector<std::string>::iterator &it, int &start)
{
    int tmp_start = start;
    int last_pos = start;
    bool in = false;
    std::stack<std::string> stack;
    for (it = _file_data.begin() + start - 1; it != _file_data.end(); it++)
    {
        if (in == false && *it == "server" && (it + 1) != _file_data.end() && *(it + 1) == "{")
        {
            in = true;
            stack.push("{");
            it += 2;
            tmp_start = start + 2;
            start += 2;
        }
        if (in == true)
        {
            std::pair<std::string, bool> p;
            p = after_space(*it);
            // std::cout << p.first << " | " << start << std::endl;
            if ((p.first == "{" && p.second) || (p.first == "}" && p.second))
            {
                if (p.first == "}" && stack.top() == "{")
                    stack.pop();
                else
                    stack.push(p.first);
                last_pos = start;
                // std::cout << "last pos : " << last_pos << std::endl;
            }
            if (p.first == "server")
            {
                if (!stack.empty())
                    throw ParsingConfigFileException(strdup("brakets problem"));
                start = start - (start - last_pos);
                return(std::make_pair(tmp_start, start));
            }
        }
        start++;
    }
    if (!stack.empty())
        throw ParsingConfigFileException(strdup("brakets problem"));
    else
        return(std::make_pair(tmp_start, start));
}

void ConfigFile::handling_single_server(int start, int end)
{
    
}

void ConfigFile::fill_serv_infos()
{
    std::vector<std::string>::iterator it;
    std::pair<int, int> p; // start | end
    int start = 1;
    int tmp_start = start;
    for (it = _file_data.begin(); it != _file_data.end(); it++)
    {
        tmp_start = start;
        p = check_server(it, start);
        std::cout << p.first << " | " << p.second << std::endl;
        // handling_single_server(p.first, p.second - 1); // use array of string
        it += (start - tmp_start);
        start++;
        if (start >= _file_data.size())
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
