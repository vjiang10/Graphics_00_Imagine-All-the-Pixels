#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    char line[50];
    int fd = open("image.ppm", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    snprintf(line, sizeof(line), "P3 500 500 255\n");
    write(fd, line, strlen(line));

    int i, j;
    int rgb[3];
    // magic circle
    for (i=0; i<500; i++) {
        for (j=0; j<500; j++) {
            double square = (i-250)*(i-250) + (j-250)*(j-250);
            if (square/100 > 500 && square/100 < 600) {
                rgb[0] = i%10; rgb[1] = j%100; rgb[2] = (i+j)%100;
                int k;
                for (k=0; k<3; k++) rgb[k]-=(square/100 - 500)/20; 
            }
            else {rgb[0] = rgb[1] = rgb[2] = 0;}
            snprintf(line, sizeof(line), "%d %d %d ", rgb[0], rgb[1], rgb[2]);
            write(fd, line, strlen(line));
        }
    }

    close(fd);
    return 0;
}