#include <boost/program_options.hpp>

using namespace boost::program_options;

#include "focal_sum.h"

int main(int argc, const char* argv[])
{

    std::string input;
    std::string output;

    options_description desc{"Options"};
    desc.add_options()

        ("help,h",
         "Help screen. This app takes a input data file and export an output "
         "data file calculating focal sum using a 3*3 window. To use app do: "
         "./focal_sum --input <input_file_name> --output <output_file_name> or "
         "./focal_sum <input_file_name> <output_file_name>")("input,i", value(&input), "Input file")(
            "output,o", value(&output), "Output file");

    // Configure options here
    positional_options_description positionals;
    positionals.add("input", 1).add("output", 1);

    variables_map vm;
    try
    {
        store(command_line_parser(argc, argv).options(desc).positional(positionals).run(), vm);
        notify(vm);
    }
    catch (const std::exception& e)
    {

        std::cerr << "Error The command does NOT specify in correct way"
                     "Enter '/.focal_sum -h/' for help"
                  << e.what() << std::endl;

        return 1;
    }

    if (vm.count("help"))
    {
        std::cout << desc << '\n';
    }
    else
    {

        dc::Raster_data input_data = dc::read(input);

        dc::Raster_data output_raster = dc::focal_sum(input_data, output);

        // dc::write (output_raster, output);
    }

    return 0;
}
