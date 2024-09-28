#include "bmp.h"
#include <GL/glut.h>

BMPImage* readBMP(const char *filename) {
  BMPImage *image = malloc(sizeof(BMPImage));
  FILE *file = fopen(filename, "rb");

  if (!file) {
    fprintf(stderr, "No se puede abrir el archivo %s\n", filename);
    free(image);
    return NULL;
  }

  fread(image->header, sizeof(unsigned char), 54, file);
  image->width = *(int*)&image->header[18];
  image->height = *(int*)&image->header[22];

  image->data = malloc(image->width * image->height * 3); // 3 bytes por píxel
  fread(image->data, sizeof(unsigned char), image->width * image->height * 3, file);
  fclose(file);

  // Convertir la imagen a blanco y negro
  unsigned char *bwData = malloc(image->width * image->height);
  for (int i = 0; i < image->width * image->height; i++) {
    unsigned char r = image->data[i * 3 + 2]; // Rojo
    unsigned char g = image->data[i * 3 + 1]; // Verde
    unsigned char b = image->data[i * 3];     // Azul

    // Cálculo de la luminancia para el gris
    unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
    bwData[i] = gray;
  }

  free(image->data); // Liberar la memoria de la imagen original
  image->data = bwData; // Reemplazar con los datos en blanco y negro

  return image;
}

void freeBMP(BMPImage *image) {
  free(image->data);
  free(image);
}

void drawBMP(BMPImage *image) {
  // Para dibujar en blanco y negro, usa GL_LUMINANCE
  glDrawPixels(image->width, image->height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image->data);
}
