//
// Created by matt on 3/20/17.
//

#ifndef MV_lsboost_H
#define MV_lsboost_H
#include <iostream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <unistd.h>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>


#undef BOOST_NO_CXX11_SCOPED_ENUMS
namespace fs = boost::filesystem;

using namespace std;


int cd(string new_dir);

fs::path pwd(string line);


#endif