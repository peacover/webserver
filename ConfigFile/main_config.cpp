/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_config.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:37:18 by yer-raki          #+#    #+#             */
/*   Updated: 2022/06/13 05:16:38 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFile.cpp"
#include "Location.cpp"

#include "ConfigFile.hpp"
#include "Location.hpp"

int main()
{
    try
    {
        ConfigFile cf("./servers_conf_file.conf");
        // system("leaks a.out");
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        // system("leaks a.out");
    }
}