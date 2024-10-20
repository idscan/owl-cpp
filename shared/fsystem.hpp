
#ifndef FSYSTEM_HPP
#define FSYSTEM_HPP

// "fs" is either boost:: or std:: filesystem depending on USE_BOOST_FILESYSTEM

#if USE_BOOST_FILESYSTEM
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
namespace fs = boost::filesystem;
using ifstream = boost::filesystem::ifstream;
#else
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
using ifstream = std::ifstream;
#endif

#endif // FSYSTEM_HPP
