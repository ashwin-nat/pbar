# PBar

PBar is a pure C library for rendering a progress bar in the terminal. It uses the FILE API's and ioctl() to do this. 

ioctl() is used to get the terimnal window size, so that the library can render the progress bar based on the terminal size. The code is doxygen documented and simple to understand (I think).


## Usage

Simply add the pbar.c and pbar.h files to your source code. 

To use this in your code,
1. get the terminal dimensions using pbar_get_wdim ()
2. render the progress bar using pbar_print ()

## Example

There is a provided example usage of this library (example.c). Use the given Makefile to build the example

```
make
./pbar_example
```

# Credits

This readme file was made using [https://www.makeareadme.com](https://www.makeareadme.com)


## License
[MIT](https://choosealicense.com/licenses/mit/)