#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_index(int x, int y, int width) {
    return y * width + x;
}

int main(int argc, char *argv[]) {
    FILE *file;
    char file_name[255];
    char buff[255];
    int width, height, max_value;
    int i, j, index;
    unsigned char pixel;
    unsigned char *pixels;

    strcpy(file_name, "..\\tests\\");
    strcat(file_name, argv[1]);

    file = fopen(file_name, "r");

    if (!file)
    {
        printf("File not found.");
        return EXIT_FAILURE;
    }

    fscanf(file, "%s", buff);

    fscanf(file, "%d %d", &width, &height);
    fscanf(file, "%d", &max_value);
    // reading new line symbol, so it does not end up in pixels array
    fscanf(file, "%c", &pixel);

    printf("buff %s\nwidth %d\nheight %d\nmax value %d\n", buff, width, height, max_value);

    pixels = calloc(width * height, sizeof(unsigned char));

    index = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fscanf(file, "%c", &pixel);

            if (!((unsigned char) pixel == max_value || (unsigned char) pixel == 0))
            {
                printf("Incorrect PGM format.");
                fclose(file);
                free(pixels);
                return EXIT_FAILURE;
            }

            pixels[index++] = (unsigned char) pixel;
        }
    }
    fclose(file);

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            printf("%d", pixels[get_index(j, i, width)] == 255 ? 1 : 0);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}