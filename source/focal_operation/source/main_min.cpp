#include <boost/program_options.hpp>

#include <iostream>

using namespace boost::program_options;

#include "dc/io.hpp"
#include "dc/raster.hpp"

#include "dc/focal_min.hpp"

/*template<typename T>
void focal_min_operation(
    const std::string& input, const std::string& output, int const& window_size_x, int const& window_size_y);*/

/*template<typename T>
void focal_min_operation(
    const std::string& input, const std::string& output, int const& window_size_x, int const& window_size_y)
{

    dc::Raster<T> input_raster = dc::read<T>(input);
    const dc::Raster<T> output_raster = dc::focal_min<T>(input_raster, window_size_x, window_size_y);
    dc::write(output_raster, output);
}*/


int main(int argc, const char* argv[])
{
    std::string input;
    std::string output;
    std::string window;

    options_description desc{"Options"};
    desc.add_options()

        ("help,h",
         "Help screen. This app takes a input data file and export an output "
         "data file calculating focal min using a n*m window. To use app do: "
         "./focal_min --input <input_file_name> --output <output_file_name> \"(n,m)\" or "
         "./focal_min <input_file_name> <output_file_name> \"(n,m)\" ")(
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
                     "Enter '/.focal_min -h/' for help"
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
             //focal_min_operation(input, output, window_size_x, window_size_y);
             
             std::string gdal_data_type =  dc::read_set_data_type(input);

             if (gdal_data_type == "GDT_Float32")

             {

             dc::Raster<float> input_raster = dc::read_set_value <float, GDT_Float32> (input);
             const dc::Raster<float> output_raster = dc::focal_min<float>(input_raster, window_size_x, window_size_y);
             dc::write<float>(output_raster, output);

             }

             else if (gdal_data_type == "GDT_Float64")
             {
             
             dc::Raster<double> input_raster = dc::read_set_value <double, GDT_Float64> (input);
             const dc::Raster<double> output_raster = dc::focal_min<double>(input_raster, window_size_x, window_size_y);
             dc::write<double>(output_raster, output);

             }
        }
        catch (const std::exception& e)
        {

            std::cerr << "An exception is happed for " << e.what() << std::endl;
        }
    }

    return 0;
}


