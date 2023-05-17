#include <boost/program_options.hpp>
#include <iostream>

#include <fstream>

#include <string>

using namespace boost::program_options;

#include "focal_sum_gdal.h"

void on_age(int age) { std::cout << "On age: " << age << '\n'; }

int main(int argc, const char *argv[]) {

  std::string input_sahand;
  std::string output_sahand;

  const char *input_sahand_const_char = input_sahand.c_str();
  const char *output_sahand_const_char = output_sahand.c_str();

  options_description desc{"Options"};
  desc.add_options()

      ("help,h",
       "Help screen. This app takes a input data file and export an output "
       "data file calculating focal sum using a 3*3 window. To use app do: "
       "./focal_sum --input <input_file_name> --output <output_file_name> or "
       "./focal_sum <input_file_name> <output_file_name>")
	  ("input,i", value(&input_sahand),"Input file")
      ("output,o", value(&output_sahand), "Output file"); 

  // Configure options here
  positional_options_description positionals;
  positionals.add("input", 1).add("output", 1 );

  variables_map vm;
  store(command_line_parser(argc, argv)
            .options(desc)
            .positional(positionals)
            .run(),
        vm);
  notify(vm);

  if (vm.count("help"))
    std::cout << desc << '\n';

  if (vm.count("input")) {

    focal_sum_gdal(input_sahand_const_char, output_sahand_const_char);
  }

  return 0;
}
