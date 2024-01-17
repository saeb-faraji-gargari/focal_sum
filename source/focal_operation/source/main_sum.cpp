#include <boost/program_options.hpp>
#include <iostream>
#include <ctime>
using namespace boost::program_options;
#include "dc/io.hpp"
#include "dc/raster.hpp"
#include "dc/focal_sum.hpp"
void focal_sum_operation(const std::string& input, const std::string& output, int const& window_size)
{
    const dc::Raster input_raster = dc::read(input);
    clock_t start = clock();
    const dc::Raster output_raster = dc::focal_sum(input_raster, window_size);
    clock_t stop = clock();
    double duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken by function: " << duration << " seconds" << std::endl;
    dc::write(output_raster, output);
}
int main(int argc, const char* argv[])
{
    std::string input;
    std::string output;
    int window_size;
    options_description desc{"Options"};
    desc.add_options()(
        "help,h",
        "Help screen. This app takes a input data file and export an output "
        "data file calculating focal sum using a circular window. To use app do: "
        "./focal_sum --input <input_file_name> --output <output_file_name> <radius for window (measured in "
        "terms of cell numbers)> or "
        "./focal_sum <input_file_name> <output_file_name> <radius for window (measured in terms of cell "
        "numbers)> ")("input,i", value(&input), "Input file")("output,o", value(&output), "Output file")(
        "window_radius,w", value(&window_size), "window_radius");
    positional_options_description positionals;
    positionals.add("input", 1).add("output", 1).add("window_radius", 1);
    variables_map vm;
    try
    {
        store(command_line_parser(argc, argv).options(desc).positional(positionals).run(), vm);
        notify(vm);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error The command is NOT specified in correct way"
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
        dc::GDALLibrary gdal{};
        try
        {
            focal_sum_operation(input, output, window_size);
        }
        catch (const std::exception& e)
        {
            std::cerr << "An exception is happed for " << e.what() << std::endl;
        }
    }
    return 0;
}
