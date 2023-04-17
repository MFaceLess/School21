#include <gtk/gtk.h>

#include "s21_SmartCalc.h"

GtkWidget *LCD;
GtkWidget *graph;
FILE *temp;
FILE *gnuplotPipe;
GtkWidget *spinbox1;
GtkWidget *spinbox2;
GtkWidget *spinbox1Y;
GtkWidget *spinbox2Y;
GtkWidget *spinbox1_credit;
GtkWidget *spinbox2_credit;
GtkWidget *spinbox3_credit;
GtkWidget *spinbox4_credit;
GtkWidget *spinbox5_credit;
GtkWidget *spinbox6_credit;
GtkWidget *downwidget;

GtkWidget *spinbox1_dep;
GtkWidget *spinbox2_dep;
GtkWidget *spinbox3_dep;
GtkWidget *spinbox4_dep;
GtkWidget *spinbox5_dep;
GtkWidget *spinbox6_dep;
GtkWidget *spinbox7_dep;
GtkWidget *spinbox8_dep;
GtkWidget *spinbox9_dep;
GtkWidget *spinbox10_dep;
GtkWidget *spinbox11_dep;

char buff_for_shit[BUFF];

void draw(GtkWidget *, GdkEventExpose *, gpointer) {
  double x_left = gtk_spin_button_get_value((GtkSpinButton *)spinbox1);
  double x_right = gtk_spin_button_get_value((GtkSpinButton *)spinbox2);
  double y_left = gtk_spin_button_get_value((GtkSpinButton *)spinbox1Y);
  double y_right = gtk_spin_button_get_value((GtkSpinButton *)spinbox2Y);
  char buff_x_left[BUFF];
  char buff_x_right[BUFF];
  char buff_y_left[BUFF];
  char buff_y_right[BUFF];
  sprintf(buff_x_left, "%lf", x_left);
  sprintf(buff_x_right, "%lf", x_right);
  sprintf(buff_y_left, "%lf", y_left);
  sprintf(buff_y_right, "%lf", y_right);
  char temp1[BUFF];
  char temp2[BUFF];
  int check1 = snprintf(temp1, sizeof(temp1), "set xrange[%s:%s]", buff_x_left,
                        buff_x_right);
  int check2 = snprintf(temp2, sizeof(temp2), "set yrange[%s:%s]", buff_y_left,
                        buff_y_right);
  g_print("АГСЛ\n");
  if (check1 < 0 || check2 < 0) {
    exit(1);
  }
  Stack *x_values = init();
  Stack *y_values = init();
  for (double i = x_left; i <= x_right; i += 0.1) {
    char for_changing[BUFF];
    strcpy(for_changing, buff_for_shit);
    char temp_for_double[BUFF];
    if (i < 0) {
      sprintf(temp_for_double, "%lf", -i);
      strcat(temp_for_double, "~");
    } else {
      sprintf(temp_for_double, "%lf", i);
    }
    while (strstr(for_changing, "x") != NULL) {
      strcpy(for_changing, find_and_insert(for_changing, "x", temp_for_double));
    }
    int check;
    char *fuck_me = (char *)malloc(10 * strlen(for_changing) * sizeof(char));
    strcpy(fuck_me, for_changing);
    g_print("fuck_me = %s\n", fuck_me);
    double result = Calculation(fuck_me, &check);
    push(y_values, result);
    push(x_values, i);
  }
  char *commandsForGnuplot[] = {"set title \"Graph!\"",
                                "set grid",
                                "set xlabel \"X\"",
                                "set ylabel \"Y\"",
                                temp1,
                                temp2,
                                "plot './data.dat' with lines"};
  temp = fopen("data.dat", "w");
  gnuplotPipe = popen("gnuplot -persistent", "w");
  for (size_t i = 0; i < x_values->top; i++) {
    fprintf(temp, "%lf %lf\n", x_values->data[i], y_values->data[i]);
  }
  for (int i = 0; i < NUM_COMMANDS; i++) {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
  }
  // fflush(gnuplotPipe);
  fclose(temp);
  fclose(gnuplotPipe);
  destroy(&x_values);
  destroy(&y_values);
}

gint delete_event(GtkWidget *, GdkEvent *, gpointer) {
  gtk_main_quit();
  return FALSE;
}

void callback(GtkWidget *, gpointer data) {
  const char *temp = gtk_label_get_text((GtkLabel *)LCD);
  char buffer[BUFF];
  if (!strcmp((char *)data, "clear")) {
    strcpy(buffer, "Nothing");
  } else if (!strcmp((char *)data, "del") && !strcmp(temp, "Nothing")) {
    strcpy(buffer, "Nothing");
  } else if (!strcmp((char *)data, "del") && strcmp(temp, "Nothing")) {
    if (strlen(temp) == 1) {
      strcpy(buffer, "Nothing");
    } else {
      size_t i = 0;
      for (i = 0; i < strlen(temp) - 1; i++) {
        buffer[i] = temp[i];
      }
      buffer[i] = '\0';
      g_print("Come in %s\n", buffer);
    }
  } else if (!strcmp(temp, "Nothing")) {
    strcpy(buffer, "");
    strcat(buffer, (char *)data);
  } else if (!strcmp((char *)data, "+") || !strcmp((char *)data, "-") ||
             !strcmp((char *)data, "/") || !strcmp((char *)data, "*") ||
             !strcmp((char *)data, "^")) {
    if (is_operator(temp[strlen(temp) - 1])) {
      size_t i;
      for (i = 0; i < strlen(temp) - 1; i++) {
        buffer[i] = temp[i];
      }
      buffer[i] = '\0';
      strcat(buffer, (char *)data);
    } else {
      strcpy(buffer, temp);
      strcat(buffer, (char *)data);
    }
  } else if (!strcmp((char *)data, "=")) {
    strcpy(buffer, temp);
    while (strstr(buffer, "acos") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "acos", "o"));
    }
    while (strstr(buffer, "asin") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "asin", "i"));
    }
    while (strstr(buffer, "atan") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "atan", "a"));
    }
    while (strstr(buffer, "cos") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "cos", "c"));
    }
    while (strstr(buffer, "sin") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "sin", "s"));
    }
    while (strstr(buffer, "tan") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "tan", "t"));
    }
    while (strstr(buffer, "sqrt") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "sqrt", "q"));
    }
    while (strstr(buffer, "ln") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "ln", "l"));
    }
    while (strstr(buffer, "log") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "log", "g"));
    }
    while (strstr(buffer, "mod") != NULL) {
      strcpy(buffer, find_and_insert(buffer, "mod", "%"));
    }
    int check_for_digit = 0;
    for (size_t i = 0; i < strlen(buffer); i++) {
      if (isdigit(buffer[i])) {
        check_for_digit = 1;
      }
    }
    int check_for_x = 0;
    if (strstr(buffer, "x") != NULL) {
      check_for_digit = 1;
      check_for_x = 1;
    }
    if (check_for_digit) {
      char *out = Sort_Facility(buffer);
      g_print("out = %s\n", out);
      if (!strcmp(out, "Error")) {
        strcpy(buffer, "Error");
      } else if (!check_for_x) {
        int check;
        double result = Calculation(out, &check);
        if (check == 1) {
          strcpy(buffer, "Error");
        } else {
          sprintf(buffer, "%.8f", result);
          g_print("result = %f\n", result);
        }
      } else if (check_for_x) {
        int check_for_many_x = 0;
        for (size_t i = 0; i < strlen(buffer); i++) {
          if ((buffer[i] == 'x' &&
               (!is_operator(buffer[i - 1]) && buffer[i - 1] != '(') &&
               (!is_operator(buffer[i + 1]) && buffer[i + 1] != ')')) &&
              strlen(buffer) != 1) {
            check_for_many_x = 1;
            break;
          }
        }
        if (check_for_many_x) {
          strcpy(buffer, "Error");
        }
        if (!check_for_many_x) {
          // right version
          if (GTK_IS_WIDGET(graph)) {
            gtk_widget_destroy(graph);
          }
          graph = gtk_window_new(GTK_WINDOW_TOPLEVEL);
          gtk_window_set_title(GTK_WINDOW(graph), "Graph");
          gtk_window_set_resizable(GTK_WINDOW(graph), FALSE);

          GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
          gtk_container_add(GTK_CONTAINER(graph), vbox);

          GtkWidget *button1 = gtk_button_new_with_label("Построить график");

          spinbox1 = gtk_spin_button_new_with_range(-1000000, 1000000, 0.2);
          spinbox2 = gtk_spin_button_new_with_range(-1000000, 1000000, 0.2);
          gtk_spin_button_set_value((GtkSpinButton *)spinbox1, 0);
          gtk_spin_button_set_value((GtkSpinButton *)spinbox2, 10);

          GtkWidget *label1 = gtk_label_new("Левая граница по X");
          GtkWidget *label2 = gtk_label_new("Правая граница по X");
          GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
          gtk_box_pack_start(GTK_BOX(hbox1), label1, TRUE, TRUE, 0);
          gtk_box_pack_start(GTK_BOX(hbox1), label2, TRUE, TRUE, 0);

          GtkWidget *label1Y = gtk_label_new("Левая граница по Y");
          GtkWidget *label2Y = gtk_label_new("Правая граница по Y");
          GtkWidget *hbox1Y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
          gtk_box_pack_start(GTK_BOX(hbox1Y), label1Y, TRUE, TRUE, 0);
          gtk_box_pack_start(GTK_BOX(hbox1Y), label2Y, TRUE, TRUE, 0);

          GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
          gtk_box_pack_start(GTK_BOX(hbox2), spinbox1, TRUE, TRUE, 0);
          gtk_box_pack_start(GTK_BOX(hbox2), spinbox2, TRUE, TRUE, 0);

          spinbox1Y = gtk_spin_button_new_with_range(-1000000, 1000000, 0.2);
          spinbox2Y = gtk_spin_button_new_with_range(-1000000, 1000000, 0.2);
          gtk_spin_button_set_value((GtkSpinButton *)spinbox1Y, 0);
          gtk_spin_button_set_value((GtkSpinButton *)spinbox2Y, 10);
          GtkWidget *hbox2Y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
          gtk_box_pack_start(GTK_BOX(hbox2Y), spinbox1Y, TRUE, TRUE, 0);
          gtk_box_pack_start(GTK_BOX(hbox2Y), spinbox2Y, TRUE, TRUE, 0);

          gtk_box_pack_start(GTK_BOX(vbox), hbox1Y, FALSE, FALSE, 0);
          gtk_box_pack_start(GTK_BOX(vbox), hbox2Y, FALSE, FALSE, 0);
          gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 0);
          gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 0);
          gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 0);

          gtk_window_set_default_size((GtkWindow *)graph, 500, 70);
          strcpy(buff_for_shit, out);
          g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(draw),
                           NULL);
          gtk_widget_show_all(graph);
        }
        g_print("oh, boy = %s\n", out);
      }
      g_print("buffer = %s\n", buffer);
    } else {
      strcpy(buffer, "Error");
    }
  } else {
    strcpy(buffer, temp);
    strcat(buffer, (char *)data);
  }
  gtk_label_set_text((GtkLabel *)LCD, buffer);
}

void credit_calc(GtkWidget *, GdkEventExpose *, gpointer) {
  double x1 =
      gtk_spin_button_get_value((GtkSpinButton *)spinbox1_credit);  // Кредит
  double x2 = gtk_spin_button_get_value(
      (GtkSpinButton *)spinbox2_credit);  // Срок в месяцах
  double x3 = gtk_spin_button_get_value(
      (GtkSpinButton *)spinbox3_credit);  // Процентая ставка
  g_print("x1 = %lf\n", x1);
  g_print("x2 = %lf\n", x2);
  g_print("x3 = %lf\n", x3);
  double result;
  // аннуитетный
  if (!strcmp("0", gtk_combo_box_get_active_id((GtkComboBox *)downwidget))) {
    double stavka = x3 / 12.0 / 100.0;
    double koeff =
        (stavka * pow((1 + stavka), x2)) / (pow((1 + stavka), x2) - 1);
    result = x1 * koeff;
    g_print("res = %lf\n", result);
  } else {
    double Cd = x1 / x2;
    double sum;
    for (int i = 0; i < x2; i++) {
      double temp = (x1 - Cd * i) * x3 / 100 * 31 / 365;
      sum += temp;
    }
    result = Cd * x2 + sum;
  }
  gtk_spin_button_set_value((GtkSpinButton *)spinbox4_credit, result);
  gtk_spin_button_set_value((GtkSpinButton *)spinbox5_credit,
                            (result * x2) - x1);
  gtk_spin_button_set_value((GtkSpinButton *)spinbox6_credit,
                            (result * x2) - x1 + x1);
}

void credit(GtkWidget *, GdkEventExpose *, gpointer) {
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Кредитный калькулятор");

  GtkWidget *label1 = gtk_label_new("Общая сумма кредита (руб)");
  GtkWidget *label2 = gtk_label_new("Срок в месяцах");
  GtkWidget *label3 = gtk_label_new("Процентная ставка (%)");
  GtkWidget *label4 = gtk_label_new("Тип");
  spinbox1_credit = gtk_spin_button_new_with_range(0, 1000000000, 0.1);
  spinbox2_credit = gtk_spin_button_new_with_range(0, 1000000, 1);
  spinbox3_credit = gtk_spin_button_new_with_range(0, 100, 0.1);
  downwidget = gtk_combo_box_text_new();
  gtk_combo_box_text_append((GtkComboBoxText *)downwidget, "0", "аннуитетный");
  gtk_combo_box_text_append((GtkComboBoxText *)downwidget, "1",
                            "дифференцированный");
  gtk_combo_box_set_active((GtkComboBox *)downwidget, 0);
  GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *button = gtk_button_new_with_label("Рассчитать");
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_box_pack_start(GTK_BOX(hbox2), label1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox2), label2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox2), label3, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox2), label4, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), spinbox1_credit, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), spinbox2_credit, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), spinbox3_credit, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), downwidget, TRUE, TRUE, 0);

  GtkWidget *label5 = gtk_label_new("Eжемесячный платеж");
  GtkWidget *label6 = gtk_label_new("Переплата по кредиту");
  GtkWidget *label7 = gtk_label_new("Общая выплата");
  spinbox4_credit = gtk_spin_button_new_with_range(0, 10000000000, 0.1);
  spinbox5_credit = gtk_spin_button_new_with_range(0, 10000000000, 0.1);
  spinbox6_credit = gtk_spin_button_new_with_range(0, 10000000000, 0.1);
  GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(hbox3), label5, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox3), label6, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox3), label7, TRUE, TRUE, 0);

  GtkWidget *hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(hbox4), spinbox4_credit, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox4), spinbox5_credit, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox4), spinbox6_credit, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox3, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox4, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(credit_calc),
                   (gpointer) "7");

  gtk_window_set_default_size((GtkWindow *)window, 1000, 80);
  gtk_widget_show_all(window);
  g_print("fuck1\n");
}

void depozit_calc(GtkWidget *, GdkEventExpose *, gpointer) {
  double x1 =
      gtk_spin_button_get_value((GtkSpinButton *)spinbox1_dep);  // Кредит
  double x2 = gtk_spin_button_get_value(
      (GtkSpinButton *)spinbox2_dep);  // Срок в месяцах
  double x3 = gtk_spin_button_get_value(
      (GtkSpinButton *)spinbox3_dep);  // Процентая ставка
  double x4 = gtk_spin_button_get_value(
      (GtkSpinButton *)spinbox4_dep);  // Процентая ставка

  double result = x1 * x2 * x3 / x4 / 100.0;

  gtk_spin_button_set_value((GtkSpinButton *)spinbox9_dep, result);
  gtk_spin_button_set_value((GtkSpinButton *)spinbox10_dep, result + x1);
}

void depozit(GtkWidget *, GdkEventExpose *, gpointer) {
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Депозитный калькулятор");

  GtkWidget *label1 = gtk_label_new("Сумма вклада");
  GtkWidget *label2 = gtk_label_new("Годовая ставка");
  GtkWidget *label3 = gtk_label_new("Количество дней вклада");
  GtkWidget *label4 = gtk_label_new("365 или 366");
  spinbox1_dep = gtk_spin_button_new_with_range(0, 1000000000, 0.1);
  spinbox2_dep = gtk_spin_button_new_with_range(0, 1000000000, 0.1);
  spinbox3_dep = gtk_spin_button_new_with_range(0, 1000000000, 0.1);
  spinbox4_dep = gtk_spin_button_new_with_range(0, 1000000000, 0.1);
  GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *button = gtk_button_new_with_label("Рассчитать");
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_box_pack_start(GTK_BOX(hbox2), label1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox2), label2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox2), label3, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox2), label4, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), spinbox1_dep, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), spinbox2_dep, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), spinbox3_dep, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), spinbox4_dep, TRUE, TRUE, 0);

  GtkWidget *label9 = gtk_label_new("Начисленные проценты");
  GtkWidget *label10 = gtk_label_new("Сумма налога");
  spinbox9_dep = gtk_spin_button_new_with_range(0, 10000000000, 0.1);
  spinbox10_dep = gtk_spin_button_new_with_range(0, 10000000000, 0.1);
  GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(hbox3), label9, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox3), label10, TRUE, TRUE, 0);

  GtkWidget *hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(hbox4), spinbox9_dep, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox4), spinbox10_dep, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox3, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox4, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(depozit_calc),
                   (gpointer) "7");

  gtk_window_set_default_size((GtkWindow *)window, 1000, 80);
  gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "s21_SmartCalc");
  gtk_container_set_border_width(GTK_CONTAINER(window), 50);
  g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event),
                   NULL);

  GtkWidget *table = gtk_grid_new();

  GtkWidget *button1 = gtk_button_new_with_label("7");
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(callback),
                   (gpointer) "7");
  gtk_grid_attach((GtkGrid *)table, button1, 0, 1, 1, 1);

  GtkWidget *button2 = gtk_button_new_with_label("8");
  g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(callback),
                   (gpointer) "8");
  gtk_grid_attach((GtkGrid *)table, button2, 1, 1, 1, 1);

  GtkWidget *button3 = gtk_button_new_with_label("9");
  g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(callback),
                   (gpointer) "9");
  gtk_grid_attach((GtkGrid *)table, button3, 2, 1, 1, 1);

  GtkWidget *button4 = gtk_button_new_with_label("4");
  g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(callback),
                   (gpointer) "4");
  gtk_grid_attach((GtkGrid *)table, button4, 0, 2, 1, 1);

  GtkWidget *button5 = gtk_button_new_with_label("5");
  g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(callback),
                   (gpointer) "5");
  gtk_grid_attach((GtkGrid *)table, button5, 1, 2, 1, 1);

  GtkWidget *button6 = gtk_button_new_with_label("6");
  g_signal_connect(G_OBJECT(button6), "clicked", G_CALLBACK(callback),
                   (gpointer) "6");
  gtk_grid_attach((GtkGrid *)table, button6, 2, 2, 1, 1);

  GtkWidget *button7 = gtk_button_new_with_label("1");
  g_signal_connect(G_OBJECT(button7), "clicked", G_CALLBACK(callback),
                   (gpointer) "1");
  gtk_grid_attach((GtkGrid *)table, button7, 0, 3, 1, 1);

  GtkWidget *button8 = gtk_button_new_with_label("2");
  g_signal_connect(G_OBJECT(button8), "clicked", G_CALLBACK(callback),
                   (gpointer) "2");
  gtk_grid_attach((GtkGrid *)table, button8, 1, 3, 1, 1);

  GtkWidget *button9 = gtk_button_new_with_label("3");
  g_signal_connect(G_OBJECT(button9), "clicked", G_CALLBACK(callback),
                   (gpointer) "3");
  gtk_grid_attach((GtkGrid *)table, button9, 2, 3, 1, 1);

  GtkWidget *button10 = gtk_button_new_with_label("del");
  g_signal_connect(G_OBJECT(button10), "clicked", G_CALLBACK(callback),
                   (gpointer) "del");
  gtk_grid_attach((GtkGrid *)table, button10, 0, 4, 1, 1);

  GtkWidget *button11 = gtk_button_new_with_label("0");
  g_signal_connect(G_OBJECT(button11), "clicked", G_CALLBACK(callback),
                   (gpointer) "0");
  gtk_grid_attach((GtkGrid *)table, button11, 1, 4, 1, 1);

  GtkWidget *button12 = gtk_button_new_with_label(".");
  g_signal_connect(G_OBJECT(button12), "clicked", G_CALLBACK(callback),
                   (gpointer) ".");
  gtk_grid_attach((GtkGrid *)table, button12, 2, 4, 1, 1);

  GtkWidget *button13 = gtk_button_new_with_label("(");
  g_signal_connect(G_OBJECT(button13), "clicked", G_CALLBACK(callback),
                   (gpointer) "(");
  gtk_grid_attach((GtkGrid *)table, button13, 4, 1, 1, 1);

  GtkWidget *button14 = gtk_button_new_with_label(")");
  g_signal_connect(G_OBJECT(button14), "clicked", G_CALLBACK(callback),
                   (gpointer) ")");
  gtk_grid_attach((GtkGrid *)table, button14, 5, 1, 1, 1);

  GtkWidget *button16 = gtk_button_new_with_label("+");
  g_signal_connect(G_OBJECT(button16), "clicked", G_CALLBACK(callback),
                   (gpointer) "+");
  gtk_grid_attach((GtkGrid *)table, button16, 6, 1, 1, 1);

  GtkWidget *button17 = gtk_button_new_with_label("-");
  g_signal_connect(G_OBJECT(button17), "clicked", G_CALLBACK(callback),
                   (gpointer) "-");
  gtk_grid_attach((GtkGrid *)table, button17, 4, 2, 1, 1);

  GtkWidget *button18 = gtk_button_new_with_label("*");
  g_signal_connect(G_OBJECT(button18), "clicked", G_CALLBACK(callback),
                   (gpointer) "*");
  gtk_grid_attach((GtkGrid *)table, button18, 5, 2, 1, 1);

  GtkWidget *button19 = gtk_button_new_with_label("/");
  g_signal_connect(G_OBJECT(button19), "clicked", G_CALLBACK(callback),
                   (gpointer) "/");
  gtk_grid_attach((GtkGrid *)table, button19, 6, 2, 1, 1);

  GtkWidget *button20 = gtk_button_new_with_label("^");
  g_signal_connect(G_OBJECT(button20), "clicked", G_CALLBACK(callback),
                   (gpointer) "^");
  gtk_grid_attach((GtkGrid *)table, button20, 4, 3, 1, 1);

  GtkWidget *button21 = gtk_button_new_with_label("mod");
  g_signal_connect(G_OBJECT(button21), "clicked", G_CALLBACK(callback),
                   (gpointer) "mod");
  gtk_grid_attach((GtkGrid *)table, button21, 5, 3, 1, 1);

  GtkWidget *button22 = gtk_button_new_with_label("cos");
  g_signal_connect(G_OBJECT(button22), "clicked", G_CALLBACK(callback),
                   (gpointer) "cos");
  gtk_grid_attach((GtkGrid *)table, button22, 6, 3, 1, 1);

  GtkWidget *button23 = gtk_button_new_with_label("sin");
  g_signal_connect(G_OBJECT(button23), "clicked", G_CALLBACK(callback),
                   (gpointer) "sin");
  gtk_grid_attach((GtkGrid *)table, button23, 4, 4, 1, 1);

  GtkWidget *button24 = gtk_button_new_with_label("tan");
  g_signal_connect(G_OBJECT(button24), "clicked", G_CALLBACK(callback),
                   (gpointer) "tan");
  gtk_grid_attach((GtkGrid *)table, button24, 5, 4, 1, 1);

  GtkWidget *button25 = gtk_button_new_with_label("acos");
  g_signal_connect(G_OBJECT(button25), "clicked", G_CALLBACK(callback),
                   (gpointer) "acos");
  gtk_grid_attach((GtkGrid *)table, button25, 6, 4, 1, 1);

  GtkWidget *button26 = gtk_button_new_with_label("asin");
  g_signal_connect(G_OBJECT(button26), "clicked", G_CALLBACK(callback),
                   (gpointer) "asin");
  gtk_grid_attach((GtkGrid *)table, button26, 7, 1, 1, 1);

  GtkWidget *button27 = gtk_button_new_with_label("atan");
  g_signal_connect(G_OBJECT(button27), "clicked", G_CALLBACK(callback),
                   (gpointer) "atan");
  gtk_grid_attach((GtkGrid *)table, button27, 8, 1, 1, 1);

  GtkWidget *button28 = gtk_button_new_with_label("sqrt");
  g_signal_connect(G_OBJECT(button28), "clicked", G_CALLBACK(callback),
                   (gpointer) "sqrt");
  gtk_grid_attach((GtkGrid *)table, button28, 7, 2, 1, 1);

  GtkWidget *button29 = gtk_button_new_with_label("ln");
  g_signal_connect(G_OBJECT(button29), "clicked", G_CALLBACK(callback),
                   (gpointer) "ln");
  gtk_grid_attach((GtkGrid *)table, button29, 8, 2, 1, 1);

  GtkWidget *button30 = gtk_button_new_with_label("log");
  g_signal_connect(G_OBJECT(button30), "clicked", G_CALLBACK(callback),
                   (gpointer) "log");
  gtk_grid_attach((GtkGrid *)table, button30, 7, 3, 1, 1);

  GtkWidget *button31 = gtk_button_new_with_label("clear");
  g_signal_connect(G_OBJECT(button31), "clicked", G_CALLBACK(callback),
                   (gpointer) "clear");
  gtk_grid_attach((GtkGrid *)table, button31, 8, 4, 1, 1);

  GtkWidget *button32 = gtk_button_new_with_label("=");
  g_signal_connect(G_OBJECT(button32), "clicked", G_CALLBACK(callback),
                   (gpointer) "=");
  gtk_grid_attach((GtkGrid *)table, button32, 7, 4, 1, 1);

  GtkWidget *button33 = gtk_button_new_with_label("x");
  g_signal_connect(G_OBJECT(button33), "clicked", G_CALLBACK(callback),
                   (gpointer) "x");
  gtk_grid_attach((GtkGrid *)table, button33, 8, 3, 1, 1);

  LCD = gtk_label_new("Nothing");
  gtk_grid_attach((GtkGrid *)table, LCD, 0, 0, 10, 1);

  GtkWidget *vbox;
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  GtkWidget *menubar;
  menubar = gtk_menu_bar_new();
  GtkWidget *fileMenu;
  fileMenu = gtk_menu_new();

  GtkWidget *fileMi;
  fileMi = gtk_menu_item_new_with_label("Calculator`s type");
  GtkWidget *quitMi;
  quitMi = gtk_menu_item_new_with_label("Кредитный калькулятор");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
  GtkWidget *type2 = gtk_menu_item_new_with_label("Депозитный калькулятор");
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), type2);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(credit), NULL);
  g_signal_connect(G_OBJECT(type2), "activate", G_CALLBACK(depozit), NULL);
  gtk_widget_set_valign(menubar, GTK_ALIGN_START);

  gtk_grid_set_row_homogeneous((GtkGrid *)table, TRUE);
  gtk_grid_set_column_homogeneous((GtkGrid *)table, TRUE);
  gtk_grid_set_column_spacing((GtkGrid *)table, 10);
  gtk_grid_set_row_spacing((GtkGrid *)table, 10);

  gtk_window_set_default_size((GtkWindow *)window, 500, 500);
  gtk_widget_show_all(window);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  gtk_main();
  return (0);
}

char *find_and_insert(char *str, char *sub_str, char *sub_str_rep) {
  char *buffer = NULL;
  if (str && sub_str && sub_str_rep) {
    buffer = (char *)malloc(BUFF);
    memset(buffer, 0, strlen(str));
    strncpy(buffer, str, strlen(str) - strlen(strstr(str, sub_str)));
    strcat(buffer, sub_str_rep);
    strcat(buffer, strstr(str, sub_str) + strlen(sub_str));
    strcpy(str, buffer);
    free(buffer);
  }
  return str;
}
