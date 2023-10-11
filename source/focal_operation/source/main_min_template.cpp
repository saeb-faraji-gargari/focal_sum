int main(int argc, const char* argv[])
{
    std::string input;
    std::string output;
    std::string window;

    // ... Parse command line arguments ...

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
            // Determine the template type based on the input raster's data type
            auto input_raster = dc::read(input);
            const auto& input_raster_data_type = input_raster.getDataType();

            if (input_raster_data_type == GDT_Float32)
            {
                focal_min_operation<float>(input, output, window_size_x, window_size_y);
            }
            else if (input_raster_data_type == GDT_Float64)
            {
                focal_min_operation<double>(input, output, window_size_x, window_size_y);
            }
            else if (input_raster_data_type == GDT_Int32)
            {
                focal_min_operation<int>(input, output, window_size_x, window_size_y);
            }
            // Add more cases for other data types as needed
            else
            {
                throw std::runtime_error("Unsupported data type in input raster");
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "An exception occurred: " << e.what() << std::endl;
        }
    }

    return 0;
}
