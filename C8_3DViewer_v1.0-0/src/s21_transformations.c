#include "s21_3DViewer.h"

// Перемещают точки модели в заданной плоскости на заданную величину
void move_x(mass_points *points_arr, double x) {
  for (int i = 0; i < points_arr->num; i++) points_arr->points[i].x += x;
}

void move_y(mass_points *points_arr, double y) {
  for (int i = 0; i < points_arr->num; i++) points_arr->points[i].y += y;
}

void move_z(mass_points *points_arr, double z) {
  for (int i = 0; i < points_arr->num; i++) points_arr->points[i].z += z;
}

// Поворачивает модель на заданный угол
void rotate_x(mass_points *points_arr, double angle) {
  for (int i = 0; i < points_arr->num; i++) {
    double temp_y = points_arr->points[i].y;
    double temp_z = points_arr->points[i].z;
    points_arr->points[i].y = cos(angle) * temp_y - sin(angle) * temp_z;
    points_arr->points[i].z = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotate_y(mass_points *points_arr, double angle) {
  for (int i = 0; i < points_arr->num; i++) {
    double temp_x = points_arr->points[i].x;
    double temp_z = points_arr->points[i].z;
    points_arr->points[i].x = cos(angle) * temp_x + sin(angle) * temp_z;
    points_arr->points[i].z = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void rotate_z(mass_points *points_arr, double angle) {
  for (int i = 0; i < points_arr->num; i++) {
    double temp_x = points_arr->points[i].x;
    double temp_y = points_arr->points[i].y;
    points_arr->points[i].x = cos(angle) * temp_x - sin(angle) * temp_y;
    points_arr->points[i].y = -sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

// Увеличивает или уменьшает модель в заданной плоскости в заданное количество
// раз
void scale_x(mass_points *points_arr, double x) {
  for (int i = 0; i < points_arr->num; i++) points_arr->points[i].x *= x;
}

void scale_y(mass_points *points_arr, double y) {
  for (int i = 0; i < points_arr->num; i++) points_arr->points[i].y *= y;
}

void scale_z(mass_points *points_arr, double z) {
  for (int i = 0; i < points_arr->num; i++) points_arr->points[i].z *= z;
}
