/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_config.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:37:18 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/18 11:45:15 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFile.cpp"
#include "Location.cpp"
#include "ServerConfig.cpp"
#include "../Request/Request.cpp"

#include "ConfigFile.hpp"
#include "Location.hpp"
#include "ServerConfig.hpp"
#include "../Request/Request.hpp"


int main()
{
    try
    {
        ConfigFile cf("./servers_conf_file.conf");
        // ConfigFile cf;
        // system("leaks a.out");
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        // system("leaks a.out");
    }
}