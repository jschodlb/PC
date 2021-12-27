#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct thenode {
    int value;
    struct thenode *next;
} node;

node *head = NULL;  // Adresa začátku

//      Dvě * v deklaraci = pointer na pointer             Dvě * jinde = Dereference
//                    Adresa Adresy Začátku, aby se to měnilo globálně a ne jen lokálně
int add_node(node **list, unsigned char value) {
    node *temp = malloc(sizeof(node)); // Dej mi pamět pro struct node a vrať mi na ní ukazatel

    if (!temp) return 0; // Pokud je temp null, aneb mallocu došla pamět

    temp->value = value;

    temp->next = *list;  // Vložíme list na začátek, aby na něj ukazoval head

    *list = temp; // Head teď bude ukazovat na nový list, nový list bude první v zásobníku

    printf("Adding %d ...\n", temp->value);
    return 1;
}

int get_index(int x, int y, int width) {
    return y * width + x;
}

int pixel_value(unsigned char *pixels, int x, int y, int width) {
    if (pixels[get_index(x + 1, y, width)] > 0 || pixels[get_index(x - 1, y, width)] > 0)

    return 1;
}

int main(int argc, char *argv[]) {
    FILE *file;
    char file_name[255];
    char magic_number[2];
    int width, height, max_value;
    int i, j, index;
    unsigned char pixel;
    unsigned char *pixels;
    unsigned char *mask;
    node n;
    int value;

    strcpy(file_name, "..\\tests\\");
    strcat(file_name, argv[1]);

    file = fopen(file_name, "r");

    if (!file) {
        printf("File not found.");
        return EXIT_FAILURE;
    }

    fscanf(file, "%s", magic_number);

    fscanf(file, "%d %d", &width, &height);
    fscanf(file, "%d", &max_value);
    // reading new line symbol, so it does not end up in pixels array
    fscanf(file, "%c", &pixel);

    // basic info about pgm file
    printf("buff %s\nwidth %d\nheight %d\nmax value %d\n", magic_number, width, height, max_value);

    // assigns memory for pixels array and for mask array
    pixels = calloc(width * height, sizeof(unsigned char));
    mask = calloc(width * height, sizeof(unsigned char));

    index = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fscanf(file, "%c", &pixel);

            if (!((unsigned char) pixel == max_value || (unsigned char) pixel == 0)) {
                printf("Incorrect PGM format.");
                fclose(file);
                free(pixels);
                return EXIT_FAILURE;
            }

            pixels[index++] = (unsigned char) pixel;
        }
    }
    fclose(file);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%d", pixels[get_index(j, i, width)] == 255 ? 1 : 0);
        }
        printf("\n");
    }

    value = 1;
    // first line of the mask
    // x = 0
    if (pixels[0] != 0) {
        mask[0] = value;
        add_node(&head, value);
        value++;
    }
    // for x in 1 to width-1
    for (j = 1; j < width - 1; j++) {
        if (pixels[j] != 0) {

        }
    }

    for (i = 1; i < height; i++) {
        for (j = 0; j < width; j++) {

        }
    }

    pixel_value(pixels, 10, 5, width);

    free(pixels);
    free(mask);

    return EXIT_SUCCESS;
}