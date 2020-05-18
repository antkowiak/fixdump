
//
// main.cpp - Program entry point
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "algorithm_rda.h"
#include "cmdline_options.h"
#include "fileio.h"
#include "fix_message.h"
#include "fix_message_util.h"
#include "json.h"
#include "platform_defs.h"

void help()
{
    std::cout << "usage:  fixdump [-h] [-?] [-s] [-f \"filter\"] [file1 file2 ...]" << std::endl;
    std::cout << std::endl;
    std::cout << " -h           Display help" << std::endl;
    std::cout << " -?           Display help" << std::endl;
    std::cout << " -s           Skip printing the original fix message" << std::endl;
    std::cout << " -f filter    Only show FIX tags in the filter list (comma or space separated)" << std::endl;
    std::cout << std::endl;
    std::cout << "If no files are specified, then input will be read from stdin." << std::endl;

    exit(EXIT_SUCCESS);
}

int main(int argc, const char *argv[])
{
    using option = rda::cmdline_options::option;
    using option_type = rda::cmdline_options::option_type;
    using option_value_num = rda::cmdline_options::option_value_num;

    // set up the expected command line options
    std::vector<option> options;
    options.emplace_back(option(option_type::OT_SHORT, option_value_num::OVN_NONE, "?")); // help
    options.emplace_back(option(option_type::OT_SHORT, option_value_num::OVN_NONE, "h")); // help
    options.emplace_back(option(option_type::OT_SHORT, option_value_num::OVN_NONE, "s")); // skip original
    options.emplace_back(option(option_type::OT_SHORT, option_value_num::OVN_ONE, "f"));  // filter

    // parse command line options
    rda::cmdline_options cmd(options);
    cmd.parse(argc, argv);

    // if the user is just requesting help
    if (options[0].present || options[1].present)
        help();

    // check if the user wants to print printing the header
    bool print_orig_msg = true;
    if (options[2].present)
        print_orig_msg = false;

    // check if a filter was set
    std::string filter = "";
    if (options[3].present && !options[3].values.empty())
        filter = options[3].values.front();

    // any other parameters are assumed to be files that should be read
    if (cmd.unclaimed.empty())
    {
        // read from stdin
        std::string line;

        while (std::getline(std::cin, line))
        {
            rda::fix_message fm(line);
            rda::fix::fix_message_util::GetInstance().print_fix_message(fm, filter, print_orig_msg);
        }
    }
    else
    {
        // read from files
        for (auto &s : cmd.unclaimed)
        {
            // TODO
        }
    }

    return EXIT_SUCCESS;
}
