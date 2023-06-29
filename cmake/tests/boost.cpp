#include <boost/filesystem.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    typedef std::istream_iterator<int> in;

    boost::filesystem::path p = boost::filesystem::path(".");
    std::cout << boost::filesystem::canonical(p);
}
