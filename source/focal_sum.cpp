
#include "dc/raster.hpp"

#include "dc/focal_sum.hpp"


namespace dc {

    Raster focal_sum(Raster& input)

    {

        int const ncols = input.size_x;
        int const nrows = input.size_y;

        Raster output(ncols, nrows);

        for (std::size_t i = 0; i < (ncols * nrows); i++)

        {

            int mod_left = i % ncols;
            int mod_right = (i + 1) % ncols;

            if (i == 0)
            {

                output.value[i] = input.value[i] + input.value[i + 1] + input.value[i + 2] +
                                  input.value[i + ncols] + input.value[i + 1 + ncols] +
                                  input.value[i + 2 + ncols] + input.value[i + (2 * ncols)] +
                                  input.value[i + 1 + (2 * ncols)] + input.value[i + 2 + (2 * ncols)];
            }
            else if (i == (ncols - 1))
            {

                output.value[i] = input.value[i] + input.value[i - 1] + input.value[i - 2] +
                                  input.value[i + ncols] + input.value[i - 1 + ncols] +
                                  input.value[i - 2 + ncols] + input.value[i + (2 * ncols)] +
                                  input.value[i - 1 + (2 * ncols)] + input.value[i - 2 + (2 * ncols)];
            }
            else if (i == ((nrows - 1) * ncols))
            {

                output.value[i] = input.value[i] + input.value[i + 1] + input.value[i + 2] +
                                  input.value[i - ncols] + input.value[i + 1 - ncols] +
                                  input.value[i + 2 - ncols] + input.value[i - (2 * ncols)] +
                                  input.value[i + 1 - (2 * ncols)] + input.value[i + 2 - (2 * ncols)];
            }
            else if (i == (ncols * nrows) - 1)
            {

                output.value[i] = input.value[i] + input.value[i - 1] + input.value[i - 2] +
                                  input.value[i - ncols] + input.value[i - 1 - ncols] +
                                  input.value[i - 2 - ncols] + input.value[i - (2 * ncols)] +
                                  input.value[i - 1 - (2 * ncols)] + input.value[i - 2 - (2 * ncols)];
            }

            else if ((i >= 1) && (i <= ncols - 2))
            {

                output.value[i] = input.value[i] + input.value[i - 1] + input.value[i + 1] +
                                  input.value[i + ncols] + input.value[i - 1 + ncols] +
                                  input.value[i + 1 + ncols] + input.value[i + (2 * ncols)] +
                                  input.value[i - 1 + (2 * ncols)] + input.value[i + 1 + (2 * ncols)];
            }
            else if ((i >= ((nrows - 1) * ncols) + 1) && (i <= (ncols * nrows) - 2))
            {

                output.value[i] = input.value[i] + input.value[i - 1] + input.value[i + 1] +
                                  input.value[i - ncols] + input.value[i - 1 - ncols] +
                                  input.value[i + 1 - ncols] + input.value[i - (2 * ncols)] +
                                  input.value[i - 1 - (2 * ncols)] + input.value[i + 1 - (2 * ncols)];
            }

            else if (mod_left == 0)
            {

                output.value[i] = input.value[i] + input.value[i + 1] + input.value[i + 2] +
                                  input.value[i - ncols] + input.value[i + 1 - ncols] +
                                  input.value[i + 2 - ncols] + input.value[i + ncols] +
                                  input.value[i + 1 + ncols] + input.value[i + 2 + ncols];
            }

            else if (mod_right == 0)

            {

                output.value[i] = input.value[i] + input.value[i - 1] + input.value[i - 2] +
                                  input.value[i - ncols] + input.value[i - 1 - ncols] +
                                  input.value[i - 2 - ncols] + input.value[i + ncols] +
                                  input.value[i - 1 + ncols] + input.value[i - 2 + ncols];
            }

            else
            {

                output.value[i] = input.value[i] + input.value[i - 1] + input.value[i + 1] +
                                  input.value[i - ncols] + input.value[i - 1 - ncols] +
                                  input.value[i + 1 - ncols] + input.value[i + ncols] +
                                  input.value[i - 1 + ncols] + input.value[i + 1 + ncols];
            }
        }

        return output;
    }

}  // namespace dc