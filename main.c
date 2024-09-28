#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}
  
int main(int argc, char *argv[]) {
  if (argc != 2) {
      fprintf(stderr, "Uso: %s <nombre_del_archivo.bmp>\n", argv[0]);
      return 1;
  }

  // Verificar la extensión del archivo
  if (strstr(argv[1], ".bmp") == NULL) {
      fprintf(stderr, "El archivo debe tener la extensión .bmp\n");
      return 1;
  }

  image = readBMP(argv[1]);
  if (!image) {
      fprintf(stderr, "Error al leer el archivo BMP: %s\n", argv[1]);
      return 1;
  } 

  glutInit(&argc, argv);

  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->width, image->height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->width, image->height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
