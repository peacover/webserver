/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 11:33:50 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/20 17:58:33 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(char *buf, int ret_read)
{ 
    _buf = std::string(buf, ret_read);
    // _is_chunked = false;
    _ignore_header = false;
    // _header.clear();
}
Request::Request()
{
    
}
Request::~Request()
{
    
}

Request::Request(Request const &src)
{
    *this = src;
}

Request & Request::operator=(Request const & src)
{
    _buf = src._buf;
    _method = src._method;
    _path = src._path;
    _v_protocol = src._v_protocol;
    _header = src._header;
    _body = src._body;
    _is_chunked = src._is_chunked;
    _ignore_header = src._ignore_header;
    _is_finished = src._is_finished;
    return (*this);
}

void Request::init(int i)
{
    std::string str = "./stored_files/file_" + std::to_string(i);
    // std::cout << "name file : " << str << std::endl;
    _header.clear();
    _is_chunked = false;
    _ignore_header = false; 
    _is_finished = false;
    
    _myfile.open(str);
    // myfile << "Writing this to a file.\n";
    // 
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
bool Request::getIsFinished() const
{
    return _is_finished;
}

void Request::close_file()
{
    _myfile.close();
    // std::cout << "closed" << std::endl;
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
void Request::setIgnoreHeader(bool ignore_header)
{
    _ignore_header = ignore_header;
}


std::pair<std::string, std::string> Request::split_line(std::string line)
{
    int p;
    std::string key;
    std::string value;
    p = line.find(": ");
    key = line.substr(0, p);
    value = line.substr(p + 2);
    // std::cout << "----------------------------------------------------" << std::endl;
    // std::cout << "key: " << key << std::endl;
    // std::cout << "value: " << value << std::endl;
    if (key == "Transfer-Encoding" && value == "chunked")
        _is_chunked = true;
    // std::cout << "----------------------------------------------------" << std::endl;
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
    // std::cout << "----------------------------------------------------" << std::endl;
    // std::cout << "method: " << _method << std::endl;
    // std::cout << "path: " << _path << std::endl;
    // std::cout << "version: " << _v_protocol << std::endl;
    // std::cout << "----------------------------------------------------" << std::endl;
}
void    Request::handling_chunks(int start)
{
    int size = _buf.size();
    int i;
    int tmp_start = start;
    std::string tmp;
    // for (i = start; i < size; i++)
    // {
    //     if (_buf[i] == '\r' && _buf[i + 1] == '\n')
    //     {
    //         tmp = _buf.substr(tmp_start, i - tmp_start);
    //         _chunks_length = tmp.length();
    //         _chunk_size = std::stoi(tmp, 0, 16);
    //         std::cout << "3afak : " << _chunk_size << std::endl;
    //     }
    // }
    // start = ++i;
    
}

void Request::handling_request()
{
    std::string tmp;
    bool first_line = true;

    // std::cout << _buf << std::endl;
   
    int pos;
    // bool ignore_header = false;
    int chunk_size = 0;
    int i = 0;
    for (i = 0; i < _buf.size(); i++)
    {
        if (!_ignore_header)
        {
            pos = _buf.find("\r\n");
            if (pos == -1)
                break;
            if (_buf[pos + 2] == '\r' && _buf[pos + 3] == '\n')
            {
                _ignore_header = true;
                pos = pos + 4;
                _buf = _buf.substr(pos);
                continue;
            }
            tmp = _buf.substr(0, pos);
            if (first_line)
            {
                split_first_line(tmp);
                first_line = false;
            }
            else
                setHeaders(split_line(tmp));
            _buf = _buf.substr(pos + 2);
        }
        else
        {
            // std::cout << "----------------------------------------------------" << std::endl;
            // std::cout << "first char : " << _buf[0] << std::endl;
            // std::cout << _buf << std::endl;
            if (pos == -1)
                return;
            if (_is_chunked)
            {
                pos = _buf.find("\r\n");
                tmp = _buf.substr(0, pos);
                if (tmp == "0\r\n")
                {
                    //close file
                    // std::cout << "salat l7efla !!!!!!" << std::endl;
                    _is_finished = true;
                    return;
                }

                // std::cout << "salat l7efla___ !!!!!!  " << tmp << std::endl;
                chunk_size = std::stoi(tmp, 0, 16);
                // std::cout << "salat l7efla !!!!!!" << std::endl;
  
                _buf = _buf.substr(pos + 2);

                if (chunk_size < _buf.size())
                    tmp = _buf.substr(0, chunk_size);
                else
                    tmp = _buf;
                    
                // std::cout << "chunk : " << std::endl;
                // std::cout << tmp << std::endl;
                _myfile << tmp;
                if (chunk_size < _buf.size())
                    _buf = _buf.substr(0, chunk_size + 2);
                else
                    return;
                
                // std::cout << _buf << std::endl;

            }
            else
            {
                pos = _buf.find("\r\n");
                tmp = _buf.substr(0, pos);
                _body = tmp;
                return;
                // std::cout << "----------------------------------------------------" << std::endl;
            }
        }
        
    }

}
 