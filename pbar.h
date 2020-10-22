/* MIT License
Copyright (c) [2020] [Ashwin Natarajan]
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef __PBAR_H__
#define __PBAR_H__
/**
 * @brief               - The structure that holds the terminal window dimensions
 * 
 */
struct wdim {
    int width;
    int height;
};

/**
 * @brief               - The structure that holds the optional args for pbar_print ()
 * 
 */
struct pbar_extras {
    char *prefix;
    char *suffix;
};

/**
 * @brief               - Fills the given struct wdim instance with the terminal width and height
 * 
 * @param dim           - Pointer to the struct wdim where the dimensions are to be saved.
 * @return int          - Returns 0 on succeess, -1 on failure
 */
int pbar_get_wdim (struct wdim *dim); 

/**
 * @brief               - Prints the progress bar with the given percentage based on the specified dimensions. 
 *                        NOTE: It is assumed that _dim holds correct information
 * 
 * @param fp            - FILE pointer where the output is to be written to, assumed to be non-NULL
 * @param _dim          - Pointer to the struct wdim instance holding the terminal window dimensions
 * @param percentage    - Percentage to be rendered
 * @param extras        - Pointer to structure containing optional arguments (prefix and suffix)
 * @return int          - Returns 0 on success, -1 on failure
 */
int pbar_print (FILE *fp, const struct wdim *_dim, int percentage, 
            const struct pbar_extras *extras);

#endif  //__PBAR_H__
