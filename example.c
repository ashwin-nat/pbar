#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "pbar.h"

int main (void)
{
    //get terminal dimensions
    struct wdim _dim;
    if(pbar_get_wdim(&_dim) == -1) {
        return 1;
    }

    //basic progress bar, no prefix and no suffix
    struct pbar_extras extras = { NULL, NULL };
    printf("Progress bar without prefix and suffix\n");
    pbar_print (stdout, &_dim, 60, &extras);

    //progress bar with constant prefix and ETA as suffix
    printf("\nDynamic progress bar\n");
    char suffix[20];
    int i;
    extras.prefix       = "Progress: ";
    extras.suffix       = suffix;
    for(i=0; i<10; i++) {
        memset (suffix, 0, sizeof(suffix));
        snprintf(suffix, sizeof(suffix)-1, "ETA: %d sec", 10-i);
        pbar_print (stdout, &_dim, (i*10), &extras);
        sleep(1);
    }
    
    memset (suffix, 0, sizeof(suffix));
    snprintf(suffix, sizeof(suffix)-1, "Complete");
    pbar_print (stdout, &_dim, (i*10), &extras);

    printf("\n");

    return 0;
}