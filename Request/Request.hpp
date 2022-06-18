/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 02:13:01 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/18 21:43:07 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Request
{
    public:
        Request(char *buf);
        ~Request();
        std::string getMethod() const;
        std::string getPath() const;
        std::string getVersionProtocol() const;
        std::map<std::string, std::string> getHeaders() const;
        std::string getBody() const;
        
        void setMethod(std::string method);
        void setPath(std::string path);
        void setVersionPotocol(std::string version);
        void setHeaders(std::pair<std::string, std::string> headers);
        void setBody(std::string body);

        void handling_request();
        void    split_first_line(std::string line);
        std::pair<std::string, std::string> split_line(std::string line);
        void handling_chunks(int start);
    
    
    private:
        std::string _buf;
        std::string _method;
        std::string _path;
        std::string _v_protocol;
        std::map<std::string, std::string> _header;
        std::string _body;
        bool _is_chunked;
};