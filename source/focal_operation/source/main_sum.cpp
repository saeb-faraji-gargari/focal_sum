#include <boost/program_options.hpp>

#include <iostream>

#include <ctime>

using namespace boost::program_options;

#include "dc/io.hpp"
#include "dc/raster.hpp"

#include "dc/focal_sum.hpp"

void focal_sum_operation(const std::string& input, const std::string& output, int const&, int const&);

int main(int argc, const char* argv[])
{
    std::string input;
    std::string output;
    std::string window;

    options_description desc{"Options"};
    desc.add_options()

        ("help,h",
         "Help screen. This app takes a input data file and export an output "
         "data file calculating focal sum using a n*m window. To use app do: "
         "./focal_sum --input <input_file_name> --output <output_file_name> \"(n,m)\" or "
         "./focal_sum <input_file_name> <output_file_name> \"(n,m)\" ")(
            "input,i", value(&input), "Input file")("output,o", value(&output), "Output file")(
            "window_size,w", value(&window), "window_size in the format (n,m)");

    positional_options_description positionals;
    positionals.add("input", 1).add("output", 1).add("window_size", 1);

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

        int const window_size_x = std::stoi(window.substr(1, window.find(',') - 1));
        int const window_size_y =
            std::stoi(window.substr(window.find(',') + 1, window.size() - window.find(',') - 2));

        try
        {

            focal_sum_operation(input, output, window_size_x, window_size_y);
        }
        catch (const std::exception& e)
        {

            std::cerr << "An exception is happed for " << e.what() << std::endl;
        }
    }

    return 0;
}

void focal_sum_operation(
    const std::string& input, const std::string& output, int const& window_size_x, int const& window_size_y)
{

    const dc::Raster input_raster = dc::read(input);

    clock_t start = clock();

    const dc::Raster output_raster = dc::focal_sum(input_raster, window_size_x, window_size_y);
    
    clock_t stop = clock();
    double duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken by function: " << duration << " seconds" << std::endl;


    dc::write(output_raster, output);
}
