#include <boost/process.hpp>
#include <regex>
#include <iostream>
#include <string>
#include <vector>


namespace bp = ::boost::process;


bp::child start_child(const std::string& path)
{
    std::string exec = path;
    std::vector<std::string> args;
    args.push_back("--version");
    bp::context ctx;
    ctx.stdout_behavior = bp::capture_stream();
    ctx.stdin_behavior = bp::capture_stream();
    return bp::launch(exec, args, ctx);
}


int main(int argc, char** argv)
{
    if (argc != 2) return 123;
    std::string _path;
    _path = argv[1];
    bp::child c = start_child(_path);
    bp::postream &os = c.get_stdin();
    bp::pistream &is = c.get_stdout();
    std::string token;
    std::cout << "token: ";
    if (std::cin >> token)
    {
        os << token << std::endl;
        os << "get_groups -v" << std::endl;
        os << "4" << std::endl;
        os << "close" << std::endl;
        std::string line;
        std::smatch sm;
        std::regex mask("//w+//s*");
        int w_count = 0;
        while (std::getline(is, line))
        {
            while (std::regex_search(line, sm, mask))
            {
                w_count++;
                line = sm.suffix().str();
            }
            //std::cout << line << std::endl;
        }
        bp::status s = c.wait();
        std::cout << "Total words number: " << w_count << std::endl;
        return s.exited() ? s.exit_status() : EXIT_FAILURE;
    }
    return 123;
}