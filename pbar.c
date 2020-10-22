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

#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include "pbar.h"
/******************************************************************************************************/
#define ERR                 -1
#define SUCCESS             0
#define PBAR_FILLER         "#"
#define PBAR_START          "["
#define PBAR_END            "]"
#define PBAR_SUFFIX_SEP     " | "
#define PBAR_NUMBER_LEN     5       //1 space, 3 digit percentage, 1 % symbol
/******************************************************************************************************/
/**
 * @brief               - Fills the given struct wdim instance with the terminal width and height
 * 
 * @param dim           - Pointer to the struct wdim where the dimensions are to be saved.
 * @return int          - Returns 0 on succeess, -1 on failure
 */
int pbar_get_wdim (struct wdim *dim)
{
    struct winsize w;
    //check ioctl() return code
    if(ioctl(0, TIOCGWINSZ, &w) == ERR) {
        perror("ioctl");
        return ERR;
    }

    dim->width = w.ws_col;
    dim->height = w.ws_row;

    return SUCCESS;
}

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
            const struct pbar_extras *extras)
{
    //basic checks
    if(percentage < 0 || percentage > 100) {
        return ERR;
    }
    if(_dim == NULL) {
        return ERR;
    }

    int i;
    //these const variables are used mainly for readability, the compiler will probably optimise them out
    const char *prefix      = (extras) ? extras->prefix : NULL;
    const char *suffix      = (extras) ? extras->suffix : NULL;
    const int prefix_len    = (prefix) ? strlen (prefix) : 0;
    const int filler_len    = strlen (PBAR_FILLER);
    const int start_len     = strlen (PBAR_START);
    const int end_len       = strlen (PBAR_END);
    const int suffix_len    = (suffix) ? (strlen(suffix) + 
                                strlen(PBAR_SUFFIX_SEP)) : 0;
    //the length of the bar is a function of the above lengths, terminal width, and some extra space for printing
    //the numerical value of the percentage
    const int bar_len       = (_dim->width - (prefix_len + filler_len + 
                                    start_len + end_len)) - 
                                    (PBAR_NUMBER_LEN + suffix_len);
    const int filler_count  = ( (bar_len * percentage) / (filler_len * 100) );
    const int blank_count   = bar_len - filler_count;

    //print prefix if required
    if(prefix) {
        fprintf(fp, "\r" "%s" PBAR_START, prefix);
    }
    else {
        fprintf(fp, "\r" PBAR_START);
    }

    //print the filler symbol based on the given percentage
    for(i=0; i<filler_count; i++) {
        fprintf(fp, PBAR_FILLER);
    }
    //fill the remainder of the progress bar with blank spaces
    for(i=0; i<blank_count; i++) {
        fprintf(fp, " ");
    }

    //print the numerical value of the percentage
    fprintf(fp, PBAR_END " %3d%%", percentage);

    //if a suffix is provided, print it
    if(suffix) {
        fprintf(fp, PBAR_SUFFIX_SEP "%s", suffix);
    }
    //flush the file pointer because we are not going to be adding \n to the end
    fflush(fp);

    return SUCCESS;
}