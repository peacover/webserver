/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 11:33:50 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/18 21:50:49 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(char *buf)
{ 
    _buf = std::string(buf);
    _is_chunked = false;
    _header.clear();
}
Request::~Request()
{
    
}

std::string Request::getMethod() const
{
    return _method;
}
std::string Request::getPath() const
{
    return _path;
}
std::string Request::getVersionProtocol() const
{
    return _v_protocol;
}
std::map<std::string, std::string> Request::getHeaders() const
{
    return _header;
}
std::string Request::getBody() const
{
    return _body;
}


void Request::setMethod(std::string method)
{
    _method = method;
}
void Request::setPath(std::string path)
{
    _path = path;
}
void Request::setVersionPotocol(std::string version)
{
    _v_protocol = version;
}
void Request::setHeaders(std::pair<std::string, std::string> headers)
{
    _header.insert(headers);
}
void Request::setBody(std::string body)
{
    _body = body;
}


std::pair<std::string, std::string> Request::split_line(std::string line)
{
    int p;
    std::string key;
    std::string value;
    p = line.find(": ");
    key = line.substr(0, p);
    value = line.substr(p + 2);
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "key: " << key << std::endl;
    std::cout << "value: " << value << std::endl;
    if (key == "Transfer-Encoding" && value == "chunked")
        _is_chunked = true;
    std::cout << "----------------------------------------------------" << std::endl;
    return std::make_pair(key, value);
}

void    Request::split_first_line(std::string line)
{
    int p;
    p = line.find(" ");
    _method = line.substr(0, p);
    line = line.substr(p + 1);
    p = line.find(" ");
    _path = line.substr(0, p);
    line = line.substr(p + 1);
    p = line.find(" ");
    _v_protocol = line.substr(0, p);
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "method: " << _method << std::endl;
    std::cout << "path: " << _path << std::endl;
    std::cout << "version: " << _v_protocol << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}
void    Request::handling_chunks(int start)
{
    int size = _buf.size();
    int tmp_start = start;
    std::string tmp;
    for (int i = start; i < size; i++)
    {
        if (_buf[i] == '\r' && _buf[i + 1] == '\n')
        {
            tmp = _buf.substr(tmp_start, i - tmp_start);
            // std::cout << "hhhhh : " << tmp << std::endl;
            size = std::stoi();
        }
    }
}
void Request::handling_request()
{
    std::string tmp;
    int tmp_i;
    bool first_line = true;
    int size = _buf.size();
    for (int i = 0; i < size; i++)
    {
        if (first_line)
        {
            if (_buf[i] == '\r' && _buf[i + 1] == '\n')
            {
                std::string tmp = _buf.substr(0, i);
                split_first_line(tmp);
                i++;
                tmp_i = i + 1;
                first_line = false;
            }
        }
        else
        {
            if (_buf[i] == '\r' && _buf[i + 1] == '\n')
            {
                tmp = _buf.substr(tmp_i, i - tmp_i);
                setHeaders(split_line(tmp));
                i++;
                tmp_i = i + 1;
                if (i + 2 < size && _buf[i + 1] == '\r' && _buf[i + 2] == '\n')// \r\n\r\n
                {
                    if (_is_chunked)
                        handling_chunks(i + 3);
                    tmp = _buf.substr(tmp_i, i - tmp_i);
                    i++;
                    tmp_i = i + 2;
                    tmp = _buf.substr(tmp_i, i - tmp_i);
                    i++;
                    tmp_i = i + 1;
                    _body = tmp;
                    std::cout << "----------------------------------------------------" << std::endl;
                    std::cout << "body : \n" << _body << std::endl;
                    std::cout << "----------------------------------------------------" << std::endl;
                    break;
                }
            }
        }
    }

}
 