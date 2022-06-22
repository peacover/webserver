/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 02:12:48 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/22 22:08:42 by yer-raki         ###   ########.fr       */
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
    _file_data.clear();
    _stored_request.clear();
    menu(path);
}

ConfigFile::~ConfigFile()
{
    
}

std::pair<std::string, bool> after_space(std::string str) // first string after space | true if eof or end of line
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
            if ((p.first == "{" && p.second) || (p.first == "}" && p.second))
            {
                if (p.first == "}" && stack.top() == "{")
                    stack.pop();
                else
                    stack.push(p.first);
                last_pos = start;
            }
            if (p.first == "server")
            {
                if (!stack.empty())
                    throw ParsingConfigFileException(strdup("brakets problem"));
                start = last_pos;
                return(std::make_pair(tmp_start, start));
            }
        }
        start++;
    }
    if (!stack.empty())
        throw ParsingConfigFileException(strdup("brakets problem"));
    else
    {
        start = last_pos;
        return(std::make_pair(tmp_start, start));
    }
}

std::string delete_first_word(std::string line, std::string first_word)
{
    int n = line.find(first_word);
    if (n != std::string::npos)
        return (line.erase(n, first_word.length()));
    return (NULL);
}

std::pair<std::string, int> handling_listen(std::string first_word)
{
    std::pair<std::string, int> p;
    std::string tmp = "";
    std::string tmp1 = "";
    bool b = false;
    
    for (int i = 0; i < first_word.size(); i++)
    {
        if (first_word[i] != ':')
            tmp += first_word[i];
        else
        {
            // if (tmp == "localhost")
            //     p.first = "127.0.0.1";
            p.first = tmp;
            i++;
            b = true;   
        }
        if (b)
            tmp1 += first_word[i];
    }
    p.second = std::stoi(tmp1);
    return (p);
}

std::pair<int, std::string> handling_error_page(std::string line)
{
    std::pair<int, std::string> ret;
    std::pair<std::string, bool> p = after_space(line);
    
    line = delete_first_word(line, p.first);
    p = after_space(line);
    ret.first = stoi(p.first);
    line = delete_first_word(line, p.first);
    p = after_space(line);
    ret.second = p.first;
    return (ret);
}

std::pair<int, std::string> handling_redirection(std::string line)
{
    std::pair<int, std::string> ret;
    std::pair<std::string, bool> p = after_space(line);
    
    line = delete_first_word(line, p.first);
    p = after_space(line);
    ret.first = stoi(p.first);
    line = delete_first_word(line, p.first);
    p = after_space(line);
    ret.second = p.first;
    return (ret);
}

std::vector<std::string> handling_allow_methods(std::string line)
{
    std::vector<std::string> v;
    std::pair<std::string, bool> p = after_space(line);
    std::string tmp;
    line = delete_first_word(line, p.first);
    while (p.second == false)
    {   
        p = after_space(line);
        line = delete_first_word(line, p.first);
        v.push_back(p.first);
    }
    return v;
}

std::pair<std::string, std::string> handling_cgi(std::vector<std::string>::iterator &it_line) // extention | path
{
    std::pair<std::string, std::string> ret;
    std::string line = *it_line;
    std::pair<std::string, bool> p = after_space(line);
    line = delete_first_word(line, p.first);
    p = after_space(line);
    ret.first = p.first;
    it_line += 2;
    line = *it_line;
    p = after_space(line);
    line = delete_first_word(line, p.first);
    p = after_space(line);
    ret.second = p.first;
    it_line++;
    return (ret);
}

Location ConfigFile::handling_location(std::vector<std::string>::iterator &it_line) // extention | path
{
    Location single_loc;
    std::string str;
    std::string first_word;
    std::string line = *it_line;
    std::pair<std::string, bool> p = after_space(line);
    line = delete_first_word(line, p.first);
    p = after_space(line);
    single_loc.setPath(p.first);
    it_line += 2;
    while (1)
    {
        p = after_space(*it_line);
        if (p.first == "}")
            return (single_loc);
        first_word = after_space(*it_line).first;
        str = delete_first_word(*it_line, first_word);
        if (first_word == "listen")
            single_loc.setListen(handling_listen(after_space(str).first));
        if (first_word == "root")
            single_loc.setRoot(after_space(str).first);
        if (first_word == "allow_methods")
            single_loc.setAllowMethods(handling_allow_methods(*it_line));
        if (first_word == "upload_path")
            single_loc.setUploadPath(after_space(str).first);
        if (first_word == "index")
            single_loc.setIndex(after_space(str).first);
        if (first_word == "error_page")
        {
            std::pair<int, std::string> ret = handling_error_page(*it_line);
            if (ret.first < 400 || ret.first > 511)
                throw ParsingConfigFileException(strdup("error_page range invalid"));
            single_loc.setErrorPage(ret);
        }
        if (first_word == "autoindex")
            (after_space(str).first == "true") ? single_loc.setAutoIndex(true) : single_loc.setAutoIndex(false);
        if (first_word == "return")
            single_loc.setRedirection(handling_redirection(*it_line));
        if (first_word == "cgi")
            single_loc.setCgi(handling_cgi(it_line)); 

        it_line++;
    }
    
    return (single_loc);
}

void ConfigFile::menu_single_serv(std::vector<std::string>::iterator &it_line, std::string first_word, ServerConfig &single_serv)
{
    std::string str;
    str = delete_first_word(*it_line, first_word);

    if (first_word == "listen")
        single_serv.setListen(handling_listen(after_space(str).first));
    if (first_word == "root")
        single_serv.setRoot(after_space(str).first);
    if (first_word == "allow_methods")
        single_serv.setAllowMethods(handling_allow_methods(*it_line));
    if (first_word == "upload_path")
        single_serv.setUploadPath(after_space(str).first);
    if (first_word == "index")
        single_serv.setIndex(after_space(str).first);
    if (first_word == "error_page")
    {
        std::pair<int, std::string> ret = handling_error_page(*it_line);
        if (ret.first < 400 || ret.first > 511)
            throw ParsingConfigFileException(strdup("error_page range invalid"));
        single_serv.setErrorPage(ret);
    }
    if (first_word == "autoindex")
        (after_space(str).first == "true") ? single_serv.setAutoIndex(true) : single_serv.setAutoIndex(false);
    if (first_word == "return")
        single_serv.setRedirection(handling_redirection(*it_line));
    if (first_word == "location")
        single_serv.setLocation(handling_location(it_line));
    if (first_word == "cgi")
        single_serv.setCgi(handling_cgi(it_line)); 
}

void ConfigFile::handling_single_server(int start, int end, ServerConfig &single_serv)
{
    std::vector<std::string>::iterator it;
    // std::cout << start << " | " << end << std::endl;
    for (it =_file_data.begin() + start - 1; it != _file_data.begin() + end; it++)
    {
        std::pair<std::string, bool> p;
        p = after_space(*it);
        menu_single_serv(it, after_space(*it).first, single_serv);
        // std::cout << p.first << std::endl;
        // std::cout << *it << std::endl;
        
    }
    
    // std::cout << "---------------------------------" << std::endl;
}

void ConfigFile::fill_serv_infos()
{
    std::vector<std::string>::iterator it;
    std::pair<int, int> p; // start | end
    int start = 1;
    int tmp_start = start;
    // for (it = _file_data.begin(); it != _file_data.end(); it++)
    it = _file_data.begin();
    while (it != _file_data.end())
    {
        ServerConfig single_serv;
        tmp_start = start;
        p = check_server(it, start);
        if (p.first >= p.second)
            break;
        handling_single_server(p.first, p.second - 1, single_serv); // use array of string
        _servers.push_back(single_serv);
        it += (start - tmp_start);
        start++;
    }
}

std::map<int , Request> ConfigFile::getStoredRequest() const
{
    return _stored_request;
}

void ConfigFile::setStoredRequest(int fd_client, Request rq)
{
    std::map<int , Request>::iterator it;
    std::pair<int, Request> p;
    p.first = fd_client;
    p.second = rq; // should add operator =
    it = _stored_request.find(p.first);
    if (it != _stored_request.end())
    {
        //continue uploading
        rq.setIgnoreHeader(true);
        rq.handling_request();
    }
    else
    {
        //add new request
        rq.init(fd_client);
        rq.handling_request();
    }
    _stored_request.insert(p);
}
std::vector<ServerConfig> ConfigFile::getServers() const
{
    return (_servers);
}

void ConfigFile::print_infos()
{
    std::vector<ServerConfig>::iterator it_serv;
    std::vector<std::pair<std::string, std::string> > cgi;
    std::vector<std::pair<std::string, std::string> >::iterator it_cgi;
    int i = 0;
    for (it_serv = _servers.begin(); it_serv != _servers.end(); it_serv++)
    {
        cgi = it_serv->getCgi();
        for (it_cgi = cgi.begin(); it_cgi != cgi.end(); it_cgi++)
        {
            std::cout << (*it_cgi).first << " | " << (*it_cgi).second << std::endl;
        }
        std::cout << "---------------------------" << std::endl;
    }
    std::cout << "server size : " << _servers.size() << std::endl;
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
    print_infos();

}