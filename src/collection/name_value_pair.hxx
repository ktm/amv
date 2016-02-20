//
// Created by ktm on 9/11/15.
//
#include <memory>
#include <string>
#include <boost/variant.hpp>

#ifndef AMVMODEL_NAME_VALUE_PAIR_HXX_H
#define AMVMODEL_NAME_VALUE_PAIR_HXX_H

using Value = boost::variant<boost::blank, std::string, int, double>;
using NameValuePair = std::pair<std::string, std::string>;
using NameValuePairPtr = std::shared_ptr<NameValuePair>;


#endif //AMVMODEL_NAME_VALUE_PAIR_HXX_H
