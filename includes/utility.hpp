/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:06:58 by juligonz          #+#    #+#             */
/*   Updated: 2021/08/19 15:03:08 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <sstream>

std::string intToString(int i);
void		lowerStringInPlace(std::string& s);
bool		isInteger(std::string& s);

#endif
