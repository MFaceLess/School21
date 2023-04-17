#include "s21_3DViewer.h"

int readFile(char* file_name, mass_points* points, surfaces* surface) {
  FILE* file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error in file open\n");
    return 1;
  }
  int size_of_massive =
      INIT_SIZE;  // начальный размер выделяемой памяти для точек

  points->points = (point*)malloc(sizeof(point) * size_of_massive);
  points->num = 0;

  int num_of_Stacks =
      INIT_SIZE;  // начальный размер выделяемой памяти для поверхностей

  surface->mass_of_surfaces = (Stack**)malloc(sizeof(Stack*) * num_of_Stacks);
  surface->amount_of_surfaces = 0;

  char str[BUFF];
  int i = 0;    // для прохода по массиву точек
  int ind = 0;  // для прохода по массиву стеков
  while (!feof(file)) {
    if (fgets(str, BUFF, file) == NULL) {
      continue;
    }
    if (*str == 'v' && *(str + 1) == ' ') {
      char c;
      double x_temp;
      double y_temp;
      double z_temp;
      sscanf(str, "%c %lf %lf %lf", &c, &x_temp, &y_temp, &z_temp);
      points->num += 1;
      if (points->num > size_of_massive) {
        size_of_massive *= MULTIPLIER;
        points->points =
            (point*)realloc(points->points, size_of_massive * sizeof(point));
      }
      points->points[i].x = x_temp;
      points->points[i].y = y_temp;
      points->points[i].z = z_temp;
      points->points[i].serial_number = points->num;
      i++;
    } else if (*str == 'f' && *(str + 1) == ' ') {
      int ind_ = 0;
      while (str[strlen(str) - 3 - ind_] == ' ') {
        str[strlen(str) - 3 - ind_] = 0;
        ind_++;
      }
      surface->amount_of_surfaces += 1;
      if (surface->amount_of_surfaces > num_of_Stacks) {
        num_of_Stacks *= MULTIPLIER;
        surface->mass_of_surfaces = (Stack**)realloc(
            surface->mass_of_surfaces, num_of_Stacks * sizeof(Stack*));
      }
      surface->mass_of_surfaces[ind] = init();
      char* pch;
      long num;
      pch = strtok(str, " ");
      pch = strtok(NULL, " ");
      while (pch != NULL) {
        sscanf(pch, "%ld/", &num);
        push(surface->mass_of_surfaces[ind], num);
        pch = strtok(NULL, " ");
      }
      ind++;
    }
  }
  fclose(file);
  return 0;
}

void destroy_points(mass_points* points) { free(points->points); }

void destroy_surfaces(surfaces* surface) {
  for (int k = 0; k < surface->amount_of_surfaces; k++) {
    destroy(&(surface->mass_of_surfaces[k]));
  }
  free(surface->mass_of_surfaces);
}
