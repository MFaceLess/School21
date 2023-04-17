#include <gtk/gtk.h>

#include "epoxy/gl.h"
#include "s21_3DViewer.h"

static GtkWidget* demo_window = NULL;
static GtkWidget* gl_area = NULL;

GtkWidget* button = NULL;

static GLuint position_buffer;
static GLuint ebo_buffer;
static GLuint program;
static GLuint mvp_location;
static GLuint buf;

static GLfloat vertex_data[10000000];
static GLuint indices[100000000];

GtkWidget* label1;
GtkWidget* label2;

GtkWidget* vbox7;
GtkWidget* controls;
GtkWidget* vbox_step;

GtkWidget* spinbox_scale;
GtkWidget* spinbox;

int num_of_indices = 0;

enum {
  X_AXIS,
  Y_AXIS,
  Z_AXIS,

  N_AXIS
};
/* Rotation angles on each axis */
static float rotation_angles[N_AXIS] = {0.0};
static float scale_values[N_AXIS] = {1.0, 1.0, 1.0};
static float move_values[N_AXIS] = {0.0, 0.0, 0.0};

//-------------------Функции-----------------------------
static GtkWidget* create_axis_slider(int axis);
GtkWidget* create_glarea_window(GtkWidget* do_widget);
gint delete_event(GtkWidget*, GdkEvent*, gpointer);
GtkWidget* do_glarea(GtkWidget* do_widget);
static gboolean render(GtkGLArea* area, GdkGLContext* context);
static void realize(GtkWidget* widget);
static void unrealize(GtkWidget* widget);
static void init_buffers(GLuint* vao_out, GLuint* buffer_out, GLuint* buf);
static GLuint create_shader(int type, const char* src);
static void init_shaders(GLuint* program_out, GLuint* mvp_out);
static void compute_mvp(float* res, float phi, float theta, float psi);
static void draw_triangle(void);
static void on_axis_value_change(GtkAdjustment* adjustment, gpointer data);
void choose(GtkWidget* button, GdkEvent*, gpointer);
void recalculation(size_t sz_vd, size_t sz_ind);

void rotate(GtkWidget*, GdkEvent*, gpointer);
void scale(GtkWidget*, GdkEvent*, gpointer);
void movement(GtkWidget*, GdkEvent*, gpointer);
void change_scale(GtkWidget*, GdkEvent*, gpointer);
void change_move(GtkWidget*, GdkEvent*, gpointer);

int main(int argc, char* argv[]) {
  char* name = "sphere.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (!check) {
    if (points.num != 0 && surface.amount_of_surfaces != 0) {
      int j = 0;
      float max = 0;
      for (int i = 0; i < points.num; i++) {
        if (fabs(points.points[i].x) > max) {
          max = fabs(points.points[i]
                         .x);  // Нормировка, так как границы виджета -1 до 1.
        }
        if (fabs((float)points.points[i].y) > max) {
          max = fabs((float)points.points[i].y);
          if (fabs((float)points.points[i].z) > max) {
            max = fabs((float)points.points[i].z);
          }
        }
        if (fabs((float)points.points[i].z) > max) {
          max = fabs((float)points.points[i].z);
        }
      }
      for (int i = 0; i < points.num; i++) {
        if (max == 0.0) {
          max = 1.0;
        }
        vertex_data[j] = (float)points.points[i].x / (1.5 * max);
        j++;
        vertex_data[j] = (float)points.points[i].y / (1.5 * max);
        j++;
        vertex_data[j] = (float)points.points[i].z / (1.5 * max);
        j++;
      }

      int ind = 0;
      for (int k = 0; k < surface.amount_of_surfaces; k++) {
        for (size_t i = 0; i < surface.mass_of_surfaces[k]->top; i++) {
          indices[ind] = (GLuint)surface.mass_of_surfaces[k]->data[i] - 1;
          // g_print("indices = %d\n", indices[ind]);
          ind++;
          num_of_indices++;
        }
      }
      destroy_points(&points);
      destroy_surfaces(&surface);
    }
  }
  gtk_init(&argc, &argv);
  demo_window = do_glarea(gl_area);
  gtk_main();

  // Очистка памяти
  return 0;
}

GtkWidget* create_glarea_window(GtkWidget*) {
  GtkWidget *window, *box;
  int i;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  // gtk_window_set_screen (GTK_WINDOW (window),
  // GDK_SCREEN(gtk_widget_get_screen(do_widget)));
  gtk_window_set_title(GTK_WINDOW(window), "OpenGL Area");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 650);
  gtk_container_set_border_width(GTK_CONTAINER(window), 12);
  g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event),
                   NULL);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, FALSE);
  gtk_box_set_spacing(GTK_BOX(box), 6);
  gtk_container_add(GTK_CONTAINER(window), box);

  gl_area = gtk_gl_area_new();
  gtk_widget_set_hexpand(gl_area, TRUE);
  gtk_widget_set_vexpand(gl_area, TRUE);
  gtk_container_add(GTK_CONTAINER(box), gl_area);

  /* We need to initialize and free GL resources, so we use
   * the realize and unrealize signals on the widget
   */
  g_signal_connect(gl_area, "realize", G_CALLBACK(realize), NULL);
  g_signal_connect(gl_area, "unrealize", G_CALLBACK(unrealize), NULL);

  /* The main "draw" call for GtkGLArea */
  g_signal_connect(gl_area, "render", G_CALLBACK(render), NULL);

  GSList* list = NULL;
  GtkWidget* radio1 = gtk_radio_button_new_with_label(list, "Вращение");
  list = g_slist_append(list, radio1);
  GtkWidget* radio2 = gtk_radio_button_new_with_label(list, "Масштабирование");
  list = g_slist_append(list, radio2);
  GtkWidget* radio3 = gtk_radio_button_new_with_label(list, "Перемещение");
  g_signal_connect(radio1, "toggled", G_CALLBACK(rotate), NULL);
  g_signal_connect(radio2, "toggled", G_CALLBACK(scale), NULL);
  g_signal_connect(radio3, "toggled", G_CALLBACK(movement), NULL);

  GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);
  gtk_box_pack_start(GTK_BOX(hbox), (GtkWidget*)radio1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), (GtkWidget*)radio2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), (GtkWidget*)radio3, TRUE, TRUE, 0);
  gtk_box_set_spacing(GTK_BOX(hbox), 6);
  gtk_container_add(GTK_CONTAINER(box), hbox);

  controls = gtk_box_new(GTK_ORIENTATION_VERTICAL, FALSE);
  gtk_container_add(GTK_CONTAINER(box), controls);
  gtk_widget_set_hexpand(controls, TRUE);

  for (i = 0; i < N_AXIS; i++)
    gtk_container_add(GTK_CONTAINER(controls), create_axis_slider(i));

  //---------------------------------------------------------------------
  GtkWidget* lable_step;
  lable_step = gtk_label_new_with_mnemonic("Шаг:");
  spinbox = gtk_spin_button_new_with_range(-10000, 10000, 0.5);
  gtk_spin_button_set_value((GtkSpinButton*)spinbox, 1);
  GtkWidget* hbox_ = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, TRUE);
  gtk_box_pack_start(GTK_BOX(hbox_), lable_step, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox_), spinbox, TRUE, TRUE, 0);

  GtkWidget* button_x = gtk_button_new_with_label("По оси X");
  GtkWidget* button_y = gtk_button_new_with_label("По оси Y");
  GtkWidget* button_z = gtk_button_new_with_label("По оси Z");
  g_signal_connect(G_OBJECT(button_x), "clicked", G_CALLBACK(change_move),
                   (gpointer) "x");
  g_signal_connect(G_OBJECT(button_y), "clicked", G_CALLBACK(change_move),
                   (gpointer) "y");
  g_signal_connect(G_OBJECT(button_z), "clicked", G_CALLBACK(change_move),
                   (gpointer) "z");

  GtkWidget* hbox5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);
  gtk_box_pack_start(GTK_BOX(hbox5), button_x, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox5), button_y, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox5), button_z, TRUE, TRUE, 0);
  vbox7 = gtk_box_new(GTK_ORIENTATION_VERTICAL, FALSE);
  gtk_box_pack_start(GTK_BOX(vbox7), hbox5, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox7), hbox_, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), vbox7, FALSE, FALSE, 0);
  //---------------------------------------------------------------------
  GtkWidget* lable_koeff =
      gtk_label_new_with_mnemonic("Коэффициент масштабирования");
  spinbox_scale = gtk_spin_button_new_with_range(0.1, 10, 0.1);
  GtkWidget* hbox_step = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);
  GtkWidget* button_scale = gtk_button_new_with_label("Промасштабировать");
  g_signal_connect(button_scale, "clicked", G_CALLBACK(change_scale), NULL);
  gtk_box_pack_start(GTK_BOX(hbox_step), lable_koeff, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox_step), spinbox_scale, TRUE, TRUE, 0);
  vbox_step = gtk_box_new(GTK_ORIENTATION_VERTICAL, FALSE);
  gtk_box_pack_start(GTK_BOX(vbox_step), hbox_step, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox_step), button_scale, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), vbox_step, FALSE, FALSE, 0);
  //---------------------------------------------------------------------

  label1 = gtk_label_new_with_mnemonic("Количество вершин:");
  gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_LEFT);
  gtk_label_set_xalign((GtkLabel*)label1, 0.0);
  label2 = gtk_label_new_with_mnemonic("Количество ребер:");
  gtk_label_set_justify(GTK_LABEL(label2), GTK_JUSTIFY_LEFT);
  gtk_label_set_xalign((GtkLabel*)label2, 0.0);
  GtkWidget* box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, FALSE);
  gtk_box_pack_start(GTK_BOX(box1), label1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box1), label2, TRUE, TRUE, 0);
  gtk_box_set_spacing(GTK_BOX(box1), 6);
  gtk_container_add(GTK_CONTAINER(box), box1);

  button = gtk_file_chooser_button_new("Select a file",
                                       GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_widget_set_hexpand(button, TRUE);
  gtk_container_add(GTK_CONTAINER(box), button);
  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(button), "/etc");

  GtkWidget* button2 = gtk_button_new_with_label("Прочитать файл");
  gtk_widget_set_hexpand(button2, TRUE);
  gtk_container_add(GTK_CONTAINER(box), button2);
  g_signal_connect(button2, "clicked", G_CALLBACK(choose), NULL);

  return window;
}

static void on_axis_value_change(GtkAdjustment* adjustment, gpointer data) {
  int axis = GPOINTER_TO_INT(data);

  g_assert(axis >= 0 && axis < N_AXIS);

  /* Update the rotation angle */
  rotation_angles[axis] = gtk_adjustment_get_value(adjustment);

  gtk_gl_area_set_auto_render((GtkGLArea*)gl_area, TRUE);
  /* Update the contents of the GL drawing area */
  gtk_widget_queue_draw(gl_area);
}

static GtkWidget* create_axis_slider(int axis) {
  GtkWidget *box, *label, *slider;
  GtkAdjustment* adj;
  const char* text;

  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  switch (axis) {
    case X_AXIS:
      text = "X axis";
      break;

    case Y_AXIS:
      text = "Y axis";
      break;

    case Z_AXIS:
      text = "Z axis";
      break;

    default:
      g_assert_not_reached();
  }

  label = gtk_label_new(text);
  gtk_container_add(GTK_CONTAINER(box), label);
  gtk_widget_show(label);

  adj = gtk_adjustment_new(0.0, 0.0, 360.0, 1.0, 12.0, 0.0);
  g_signal_connect(adj, "value-changed", G_CALLBACK(on_axis_value_change),
                   GINT_TO_POINTER(axis));
  slider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
  gtk_container_add(GTK_CONTAINER(box), slider);
  gtk_widget_set_hexpand(slider, TRUE);
  gtk_widget_show(slider);

  gtk_widget_show(box);

  return box;
}

void choose(GtkWidget*, GdkEvent*, gpointer) {
  gtk_gl_area_set_auto_render((GtkGLArea*)gl_area, FALSE);
  static size_t sz_vd;
  static size_t sz_ind;
  num_of_indices = 0;
  mass_points points;
  surfaces surface;
  static char* name;
  char temp[1000];
  int check2 = 1;
  if (gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button)) == NULL) {
    gtk_label_set_label((GtkLabel*)label1, "Количество вершин:");
    gtk_label_set_label((GtkLabel*)label2, "Количество ребер:");
    return;
  }
  if (name != NULL) {
    strcpy(temp, name);
  }
  name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
  if (temp != NULL && !strcmp(temp, name)) {
    g_print("Тот же файл\n");
    check2 = 0;
  }
  int check = readFile(name, &points, &surface);
  if (!check) {
    if (points.num != 0 && surface.amount_of_surfaces != 0) {
      int j = 0;
      float max = 0;
      for (int i = 0; i < points.num; i++) {
        if (fabs(points.points[i].x) > max) {
          max = fabs(points.points[i]
                         .x);  // Нормировка, так как границы виджета -1 до 1.
        }
        if (fabs((float)points.points[i].y) > max) {
          max = fabs((float)points.points[i].y);
          if (fabs((float)points.points[i].z) > max) {
            max = fabs((float)points.points[i].z);
          }
        }
        if (fabs((float)points.points[i].z) > max) {
          max = fabs((float)points.points[i].z);
        }
      }
      if (max == 0.0) {
        max = 1.0;
      }
      for (int i = 0; i < points.num; i++) {
        vertex_data[j] = (float)points.points[i].x / (1.5 * max);
        j++;
        vertex_data[j] = (float)points.points[i].y / (1.5 * max);
        j++;
        vertex_data[j] = (float)points.points[i].z / (1.5 * max);
        j++;
      }

      int ind = 0;
      for (int k = 0; k < surface.amount_of_surfaces; k++) {
        for (size_t i = 0; i < surface.mass_of_surfaces[k]->top; i++) {
          indices[ind] = (GLuint)surface.mass_of_surfaces[k]->data[i] - 1;
          ind++;
          num_of_indices++;
        }
      }
      g_print("Дошел\n");
      sz_vd = sizeof(GLfloat) * points.num * 3;
      sz_ind = sizeof(GLuint) * surface.amount_of_surfaces *
               surface.mass_of_surfaces[0]->top;
      char buff[512];
      char* first = "Количество вершин:";
      char* second = "Количество ребер:";
      char third[512];
      char forth[512];
      sprintf(buff, "%d", points.num);
      snprintf(third, sizeof third, "%s%s", first, buff);
      sprintf(buff, "%d", surface.amount_of_surfaces);
      snprintf(forth, sizeof forth, "%s%s", second, buff);

      gtk_label_set_label((GtkLabel*)label1, third);
      gtk_label_set_label((GtkLabel*)label2, forth);
      destroy_points(&points);
      destroy_surfaces(&surface);
      g_print("sz_vd = %ld\n", sz_vd);
      g_print("sz_ind = %ld\n", sz_ind);
      if (check2) {
        recalculation(sz_vd, sz_ind);
      }
      gtk_widget_queue_draw(gl_area);
    } else {
      printf("Error in file data\n");
      gtk_label_set_label((GtkLabel*)label1, "Количество вершин:");
      gtk_label_set_label((GtkLabel*)label2, "Количество ребер:");
    }
  }
  gtk_gl_area_set_auto_render((GtkGLArea*)gl_area, TRUE);
}

void recalculation(size_t sz_vd, size_t sz_ind) {
  glBindVertexArray(position_buffer);

  glBindBuffer(GL_ARRAY_BUFFER, buf);
  glBufferData(GL_ARRAY_BUFFER, sz_vd, vertex_data, GL_STREAM_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sz_ind, indices, GL_STREAM_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

gint delete_event(GtkWidget*, GdkEvent*, gpointer) {
  /* Reset the state */
  demo_window = NULL;
  gl_area = NULL;

  rotation_angles[X_AXIS] = 0.0;
  rotation_angles[Y_AXIS] = 0.0;
  rotation_angles[Z_AXIS] = 0.0;
  gtk_main_quit();
  return TRUE;
}

GtkWidget* do_glarea(GtkWidget* do_widget) {
  if (demo_window == NULL) demo_window = create_glarea_window(do_widget);

  if (!gtk_widget_get_visible(demo_window)) {
    gtk_widget_show_all(demo_window);
    gtk_widget_set_visible(vbox7, FALSE);
    gtk_widget_set_visible(vbox_step, FALSE);
  } else
    gtk_widget_destroy(demo_window);

  return demo_window;
}

static gboolean render(GtkGLArea* area, GdkGLContext*) {
  if (gtk_gl_area_get_error(area) != NULL) return FALSE;

  /* Clear the viewport */
  // glEnable(GL_DEPTH_TEST);
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Draw our object */
  draw_triangle();

  /* Flush the contents of the pipeline */
  glFlush();

  return TRUE;
}

/* We need to set up our state when we realize the GtkGLArea widget */
static void realize(GtkWidget* widget) {
  gtk_gl_area_make_current(GTK_GL_AREA(widget));

  if (gtk_gl_area_get_error(GTK_GL_AREA(widget)) != NULL) return;

  init_buffers(&position_buffer, &ebo_buffer, &buf);
  init_shaders(&program, &mvp_location);
}

/* Initialize the GL buffers */
static void init_buffers(GLuint* vao_out, GLuint* buffer_out, GLuint* buf) {
  GLuint vao, buffer, ebo;

  /* We only use one VAO, so we always keep it bound */
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* This is the buffer that holds the vertices */
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data,
               GL_DYNAMIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  if (vao_out != NULL) *vao_out = vao;

  if (buffer_out != NULL) *buffer_out = ebo;

  if (buf != NULL) *buf = buffer;
}

/* Create and compile a shader */
static GLuint create_shader(int type, const char* src) {
  GLuint shader;
  int status;

  shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    int log_len;
    char* buffer;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

    buffer = g_malloc(log_len + 1);
    glGetShaderInfoLog(shader, log_len, NULL, buffer);

    g_warning("Compile failure in %s shader:\n%s",
              type == GL_VERTEX_SHADER ? "vertex" : "fragment", buffer);

    g_free(buffer);

    glDeleteShader(shader);

    return 0;
  }

  return shader;
}

/* Initialize the shaders and link them into a program */
static void init_shaders(GLuint* program_out, GLuint* mvp_out) {
  GLuint vertex, fragment;
  GLuint program = 0;
  GLuint mvp = 0;
  int status;

  const char* vertexShaderSource =
      "#version 330 core\n"
      "layout(location = 0) in vec3 position;\n"
      "uniform mat4 mvp;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);\n"
      "}\0";
  vertex = create_shader(GL_VERTEX_SHADER, vertexShaderSource);

  if (vertex == 0) {
    *program_out = 0;
    return;
  }

  const char* vertexFragmentSource =
      "#version 330 core\n"
      "out vec4 outputColor;\n"
      "void main()\n"
      "{\n"
      "outputColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\0";
  fragment = create_shader(GL_FRAGMENT_SHADER, vertexFragmentSource);

  if (fragment == 0) {
    glDeleteShader(vertex);
    *program_out = 0;
    return;
  }

  program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    int log_len;
    char* buffer;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

    buffer = g_malloc(log_len + 1);
    glGetProgramInfoLog(program, log_len, NULL, buffer);

    g_warning("Linking failure:\n%s", buffer);

    g_free(buffer);

    glDeleteProgram(program);
    program = 0;

    goto out;
  }

  /* Get the location of the "mvp" uniform */
  mvp = glGetUniformLocation(program, "mvp");

  glDetachShader(program, vertex);
  glDetachShader(program, fragment);

out:
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  if (program_out != NULL) *program_out = program;

  if (mvp_out != NULL) *mvp_out = mvp;
}

/* We should tear down the state when unrealizing */
static void unrealize(GtkWidget* widget) {
  gtk_gl_area_make_current(GTK_GL_AREA(widget));

  if (gtk_gl_area_get_error(GTK_GL_AREA(widget)) != NULL) return;

  glDeleteBuffers(1, &position_buffer);
  glDeleteProgram(program);
}

static void draw_triangle(void) {
  float mvp[16];

  /* Compute the model view projection matrix using the
   * rotation angles specified through the GtkRange widgets
   */
  compute_mvp(mvp, rotation_angles[X_AXIS], rotation_angles[Y_AXIS],
              rotation_angles[Z_AXIS]);

  /* Use our shaders */
  glUseProgram(program);

  /* Update the "mvp" matrix we use in the shader */
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0]);

  /* Use the vertices in our buffer */
  // glBindVertexArray(position_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  /* Draw the three vertices as a triangle */
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements(GL_TRIANGLES, num_of_indices, GL_UNSIGNED_INT, 0);

  /* We finished using the buffers and program */
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

static void compute_mvp(float* res, float phi, float theta, float psi) {
  float x = phi * (G_PI / 180.f);
  float y = theta * (G_PI / 180.f);
  float z = psi * (G_PI / 180.f);
  float c1 = cosf(x), s1 = sinf(x);
  float c2 = cosf(y), s2 = sinf(y);
  float c3 = cosf(z), s3 = sinf(z);
  float c3c2 = c3 * c2;
  float s3c1 = s3 * c1;
  float c3s2s1 = c3 * s2 * s1;
  float s3s1 = s3 * s1;
  float c3s2c1 = c3 * s2 * c1;
  float s3c2 = s3 * c2;
  float c3c1 = c3 * c1;
  float s3s2s1 = s3 * s2 * s1;
  float c3s1 = c3 * s1;
  float s3s2c1 = s3 * s2 * c1;
  float c2s1 = c2 * s1;
  float c2c1 = c2 * c1;

  /* initialize to the identity matrix */
  res[0] = 1.f;
  res[4] = 0.f;
  res[8] = 0.f;
  res[12] = 0.f;
  res[1] = 0.f;
  res[5] = 1.f;
  res[9] = 0.f;
  res[13] = 0.f;
  res[2] = 0.f;
  res[6] = 0.f;
  res[10] = 1.f;
  res[14] = 0.f;
  res[3] = 0.f;
  res[7] = 0.f;
  res[11] = 0.f;
  res[15] = 1.f;

  /* apply all three rotations using the three matrices:
   *
   * ⎡  c3 s3 0 ⎤ ⎡ c2  0 -s2 ⎤ ⎡ 1   0  0 ⎤
   * ⎢ -s3 c3 0 ⎥ ⎢  0  1   0 ⎥ ⎢ 0  c1 s1 ⎥
   * ⎣   0  0 1 ⎦ ⎣ s2  0  c2 ⎦ ⎣ 0 -s1 c1 ⎦
   */
  res[0] = c3c2 * scale_values[X_AXIS];
  res[4] = (s3c1 + c3s2s1) * scale_values[X_AXIS];
  res[8] = (s3s1 - c3s2c1) * scale_values[X_AXIS];
  res[12] = move_values[X_AXIS];
  res[1] = -s3c2 * scale_values[Y_AXIS];
  res[5] = (c3c1 - s3s2s1) * scale_values[Y_AXIS];
  res[9] = (c3s1 + s3s2c1) * scale_values[Y_AXIS];
  res[13] = move_values[Y_AXIS];
  res[2] = s2 * scale_values[Z_AXIS];
  res[6] = -c2s1 * scale_values[Z_AXIS];
  res[10] = c2c1 * scale_values[Z_AXIS];
  res[14] = move_values[Z_AXIS];
  res[3] = 0.f;
  res[7] = 0.f;
  res[11] = 0.f;
  res[15] = 1.f;
}

void rotate(GtkWidget* radio, GdkEvent*, gpointer) {
  if (gtk_toggle_button_get_active((GtkToggleButton*)radio)) {
    gtk_widget_set_visible(vbox7, FALSE);
    gtk_widget_set_visible(controls, TRUE);
    gtk_widget_set_visible(vbox_step, FALSE);
  }
}
void scale(GtkWidget* radio, GdkEvent*, gpointer) {
  if (gtk_toggle_button_get_active((GtkToggleButton*)radio)) {
    gtk_widget_set_visible(vbox_step, TRUE);
    gtk_widget_set_visible(controls, FALSE);
    gtk_widget_set_visible(vbox7, FALSE);
  }
}
void movement(GtkWidget* radio, GdkEvent*, gpointer) {
  if (gtk_toggle_button_get_active((GtkToggleButton*)radio)) {
    gtk_widget_set_visible(vbox_step, FALSE);
    gtk_widget_set_visible(controls, FALSE);
    gtk_widget_set_visible(vbox7, TRUE);
  }
}

void change_scale(GtkWidget*, GdkEvent*, gpointer) {
  float koeff = gtk_spin_button_get_value((GtkSpinButton*)spinbox_scale);
  scale_values[X_AXIS] *= koeff;
  scale_values[Y_AXIS] *= koeff;
  scale_values[Z_AXIS] *= koeff;

  gtk_gl_area_set_auto_render((GtkGLArea*)gl_area, TRUE);
  /* Update the contents of the GL drawing area */
  gtk_widget_queue_draw(gl_area);
}

void change_move(GtkWidget* button, GdkEvent*, gpointer) {
  float koeff = gtk_spin_button_get_value((GtkSpinButton*)spinbox);
  if (!strcmp(gtk_button_get_label(GTK_BUTTON(button)), "По оси X")) {
    move_values[X_AXIS] += koeff;
  } else if (!strcmp(gtk_button_get_label(GTK_BUTTON(button)), "По оси Y")) {
    move_values[Y_AXIS] += koeff;
  } else if (!strcmp(gtk_button_get_label(GTK_BUTTON(button)), "По оси Z")) {
    move_values[Z_AXIS] += koeff;
  }
  gtk_gl_area_set_auto_render((GtkGLArea*)gl_area, TRUE);
  /* Update the contents of the GL drawing area */
  gtk_widget_queue_draw(gl_area);
}
