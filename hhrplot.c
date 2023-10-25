#include <gtk/gtk.h>      // for gtk3
#include <stdio.h>        // for printf()
#include <stdlib.h>       // for srand48()
#include <time.h>         // for time()
#include "gennumber.h"    // for gennumber()
#include "interaction.h"  // for print_init_message(), user_input(), 
                          // print_hints(), ITERATION, and ITER_MSGS
#include "interaction2.h" 
#include <math.h>
//#include <unistd.h>
#include <time.h>
#ifndef HEADER_H	
#define HEADER_H
typedef struct window_template {
	 GtkWidget *window;
	 GtkWidget *button1;
	 GtkWidget *button2;
       	 GtkWidget *entry;	
       	 GtkWidget *label1;
	 GtkWidget *label2;
	 GtkWidget *label3;
	 GtkWidget *grid;
	 GtkWidget *vbox;
	 GtkWidget *vbox2;
	 GtkWidget *hbox;
	 GtkWidget *hbox2;
	 GtkWidget *hbox3;
	 GtkWidget *frame1;
	 GtkWidget *frame2;
	 int a;
} Template;
#endif

int check;

/*gennumber.c*/

#define ITER 10000

/* This is a helper function used only in this file.
   This shuffles the array of ten characters pointed
   by the parameter '*str.' */
void
shuffle(unsigned char *str) {
  unsigned char p, q, tmp;
  unsigned int i;

  /* Swap the characters located at 'p' and 'q' ITER times. */
  for (i = 0; i < ITER; i++) {
    p = (unsigned char)(drand48()*10);
    q = (unsigned char)(drand48()*10);
    tmp = str[p];
    str[p] = str[q];
    str[q] = tmp;
  }
}

/* This function makes a four-digit number,
   which has different numbers in each digit. */
unsigned int
gennumber() {
  unsigned char str[] = "0123456789";
  unsigned int d;

  shuffle(str);

  /* 'str[x]' has the value of the character code of '0' to '9.'
     Therefore, subtracting the character code of '0' from 'str[x]'
     results in the numerical value from 0 to 9. */
  d = (str[0]-'0')*1000+(str[1]-'0')*100+(str[2]-'0')*10+(str[3]-'0');
  return d;
}

/*interaction.c*/

/* Get the n-th digit. 
   'pow(10, n-1)' means '10^(n-1).' */
unsigned char 
n_digit(unsigned int d, unsigned int n) {
  return ((d / (int)pow(10, n-1)) % 10);
}

/* If parameter d contains four different digits,
   this function returns 1(true), 
   otherwise this returns 0(false) */
int 
check_digits(unsigned int d) {
  int flag = 0;

  if (d < 9999) {
    unsigned char d1 = n_digit(d, 4);
    unsigned char d2 = n_digit(d, 3);
    unsigned char d3 = n_digit(d, 2);
    unsigned char d4 = n_digit(d, 1);
    flag = (d1-d2) * (d1-d3) * (d1-d4) * (d2-d3) * (d2-d4) * (d3-d4);
    /* Note: 'if (flag) {...}' means 'if (flag != 0) {...}'. */
    if (flag) { 
      printf("The number you gave me is %d%d%d%d.\n",d1,d2,d3,d4);
    }
  }
  /* Note: if the value of 'flag' is non-zero, the comparison (flag != 0) 
     returns 1(true), otherwise it returns 0(false). */
  return (flag != 0);
}

/* This function makes initial message. */
void
print_init_message(gpointer data) {
  char buf[1000];
  /* show the init massage in the window1 */
  sprintf(buf, "%s",INIT_MSG); 
  gtk_label_set_text(GTK_LABEL(((Template*)data)->label1), buf);
}

/*input a entry*/
int number_entry(gpointer data){
   const gchar *j;
   j = gtk_entry_get_text(GTK_ENTRY(((Template*)data)->entry));
   return (int)*j;
}

int number_entried(){
    check = 1;
}

void mySleep(){
	time_t now = 3 * CLOCKS_PER_SEC + clock();
	while (now > clock());
}
/* This function requests the user to enter 
   a four-digit number in the proper format. */
unsigned int
user_input(gpointer data) {
  //const guchar j[10];
  unsigned int *fourdigit_number2;
  unsigned int fourdigit_number;
  unsigned char flag = 0;
  gchar buf[50];
  gchar buf2[50];
  check = 0;

  while (flag == 0) { 
    char *text = "Enter a four-digit number:";
    sprintf(buf,"%s",text);
    gtk_label_set_text(GTK_LABEL(((Template*)data)->label3),buf);
    //printf("Enter a four-digit number: ");
    //gchar *j;
    
    while(check == 0){
        mySleep();
        //g_signal_connect(G_OBJECT(((Template*)data)->button1),"clicked",G_CALLBACK(number_entried),NULL);
        check = 1;
    }
    
    //fourdigit_number = number_entry(data);
    //j = number_entry(data);
    //sscanf(j,"%d",&fourdigit_number);
    //g_print("%d\n",fourdigit_number);
    //sscanf(fourdigit_number2,"%d",&fourdigit_number);

    /* Check the appropriateness of the user's input, 
       expecting the flag becomes 1(true). */    
      //flag = check_digits(fourdigit_number);
      //g_print("%d",i);
      
    /*if (flag == 0) { 
      char *text = "Please enter an appropriate number.";
      sprintf(buf2,"%s",text);
      gtk_label_set_text(GTK_LABEL(((Template*)data)->label3), buf); 
    }*/
    flag = 1;
  } 
  return fourdigit_number;
}

/* This function shows some hints according to 
   the comparison of the two four-digit numbers 
   provided as parameters, 'user' and 'system.' */
void 
print_hints(unsigned int user, unsigned int system,gpointer data) {
  unsigned char u[4], s[4], i, j, hr = 0, hit = 0;
  char buf[50];
  char txt1,txt2,txt3,txt4;


  for (i = 0; i < 4; i++) {
    u[i] = n_digit(user, 4-i);
    s[i] = n_digit(system, 4-i);
  }
  printf("Umm..., ");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (u[i] == s[j]) {
        if (i == j) { hr++; } else { hit++; }
        break; 
        /* Note: this statement would break out only from the inner loop. */
      }
    }
  }
  /*txt1 = hit;
  txt2 = ((hit!=1)?"s":"");
  txt3 = hr;
  txt4 = ((hr!=1)?"s":"");*/

  sprintf(buf,"%d hit%s and %d HR%s.\n", 
	hit,((hit!=1)?"s":""),hr ,((hr!=1)?"s":"") );
  gtk_label_set_text(GTK_LABEL(((Template*)data)->label2), buf);
}

/*main.c*/


int close_window(GtkWidget *widget,gpointer window_name){
	gtk_widget_hide(window_name);
	//g_print("%p\n",window_name);
	return 0;
 }

int hit_and_HR_main2(unsigned int pointer,gpointer data) {
  char buf1[50];
  char buf2[50];
  unsigned int hidden_number;
  hidden_number = pointer;

  sprintf(buf1,"\nMy secret number was %04d.\n", hidden_number);
  sprintf(buf2,"Game over! Try again!\n"); 
  gtk_label_set_text(GTK_LABEL(((Template*)data)->label1), buf1);
  gtk_label_set_text(GTK_LABEL(((Template*)data)->label2), buf2);

  return 0;
}

int window3(unsigned int pointer){
	/*settings of the window*/
	Template three;
	//gtk_init(&argc,&argv);
	three.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(three.window,600,300);
	gtk_container_set_border_width(GTK_CONTAINER(three.window),10);
	gtk_window_set_position(GTK_WINDOW(three.window),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(three.window),"hit_and_HR-master");
	
	/*settings of the boxes*/
	three.vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	gtk_container_add(GTK_CONTAINER(three.window),three.vbox);
	three.hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
	gtk_box_pack_start(GTK_BOX(three.vbox),three.hbox,TRUE,TRUE,0);	
	three.hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
       	gtk_box_pack_start(GTK_BOX(three.vbox),three.hbox2,TRUE,TRUE,0);
	three.hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	gtk_box_pack_start(GTK_BOX(three.vbox),three.hbox3,TRUE,TRUE,0);

	/*settings of the label*/
	three.label1 = gtk_label_new("massage");
	gtk_box_pack_start(GTK_BOX(three.hbox),three.label1,TRUE,TRUE,0);
	three.label2 = gtk_label_new("massage2");
	gtk_box_pack_start(GTK_BOX(three.hbox2),three.label2,TRUE,TRUE,0);

	/*settings of the grid*/
	three.grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(three.hbox3),three.grid);

	/*settings of the button*/
	three.button1 = gtk_button_new_with_label("Exit");
	gtk_grid_attach(GTK_GRID(three.grid),three.button1,50,50,10,10);
        g_signal_connect(G_OBJECT(three.button1),"clicked",G_CALLBACK(gtk_main_quit),NULL);

	/*hit and HR game main*/
        hit_and_HR_main2(pointer,&three);
	
	g_signal_connect(three.window, "destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_widget_show_all(three.window);
	return 0;
}




int hit_and_HR_main1(GtkWidget *widget,gpointer data) {
  char ctr = 0;
  unsigned int fourdigit_number, hidden_number;
  char *iter_msg[ITERATION] = ITER_MSGS;
  char buf[50];
  int i = 0;

  /* After setting a seed for the random number generator,
     a secret four-digit number is set to 'hidden_number.' */
  srand48((unsigned char)time(NULL));
    hidden_number = gennumber();
  //g_print("%d",hidden_number);


  /* Iterations until acquiring an appropriate four-digit number. */
  do {
	sprintf(buf,"%s try...",iter_msg[ctr]);
	gtk_label_set_text(GTK_LABEL(((Template*)data)->label1), buf);
	//gtk_label_set_text((((Template*)data)->label1), buf);
	g_print("%s\n", buf);
    //printf("\n%s try...\n", iter_msg[ctr]);
       fourdigit_number = user_input(data);
     //g_print("%d\n",fourdigit_number);
     

    /* Confirm whether the user's input hits the correct answer or not.
       If the user does not reach the answer, this provides some hints
       for the next trial. 
       Note: The value of 'ctr' would remain less than ITERATION,
       if you find the correct number before 'ctr' reaches ITERATION. */ 
     //if (hidden_number == fourdigit_number) { break; }
    //print_hints(fourdigit_number, hidden_number,&data);
  
  /* User can try guessing the number until the counter reaches ITERATION. */
  } while (++ctr < ITERATION);
  /*i = 1;
  if(i==1){
  close_window(NULL,((Template*)data)->window);
  }
  g_signal_connect(G_OBJECT(((Template*)data)->window),"hide",G_CALLBACK(window3),&hidden_number);*/
  return 0;

}




int window2(GtkWidget *widget, gpointer data){
	/*settings of the window*/
	Template two;
	//gtk_init(&argc,&argv);
	two.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(two.window,600,300);
       	gtk_container_set_border_width(GTK_CONTAINER(two.window),10);
	gtk_window_set_position(GTK_WINDOW(two.window),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(two.window),"hit_and_HR-master");
	
	/*settings of the grid*/
	two.grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(two.window),two.grid);

	/*settings of the label*/
	two.frame1 = gtk_frame_new("how many times have you tried?");
	two.frame2 = gtk_frame_new("hint!");
	two.label1 = gtk_label_new("how many times have you tried?"); 
	two.label2 = gtk_label_new("hint!");
	two.label3 = gtk_label_new("prompt");
	gtk_frame_set_shadow_type(GTK_FRAME(two.frame1),GTK_SHADOW_ETCHED_OUT);
	gtk_grid_attach(GTK_GRID(two.grid),two.frame1,0,0,2,2);
	gtk_container_add(GTK_CONTAINER(two.frame1),two.label1);
      	gtk_frame_set_shadow_type(GTK_FRAME(two.frame2),GTK_SHADOW_ETCHED_OUT);
	gtk_grid_attach(GTK_GRID(two.grid),two.frame2,2,2,4,4);
	gtk_container_add(GTK_CONTAINER(two.frame2),two.label2);
	gtk_grid_attach(GTK_GRID(two.grid),two.label3,4,4,8,8);

	/*settings of the entry*/
	two.entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(two.grid),two.entry,4,4,8,8);

	/*settings of the button*/
	two.button1 = gtk_button_new_with_label("Enter");
        gtk_grid_attach(GTK_GRID(two.grid),two.button1,4,8,8,8);
	//g_signal_connect(G_OBJECT(one.button1),"clicked",G_CALLBACK(window2),NULL);
	two.button2 = gtk_button_new_with_label("Start!");
	gtk_grid_attach(GTK_GRID(two.grid),two.button2,50,50,6,1);
	g_signal_connect(G_OBJECT(two.button2),"clicked",G_CALLBACK(hit_and_HR_main1),&two);

	/*hit and HR game main*/
	gtk_widget_show_all(two.window);
	//hit_and_HR_main1(NULL,&two);
	
	g_signal_connect(two.window, "destroy",G_CALLBACK(gtk_main_quit),NULL);
	
	return 0;
}



						 

int main(int argc, char** argv){

	/*window1*/
	/*Setting of the window*/
	Template one;
	gtk_init(&argc,&argv);
	one.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(one.window,600,300);
	gtk_container_set_border_width(GTK_CONTAINER(one.window),10);
	gtk_window_set_position(GTK_WINDOW(one.window),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(one.window),"hit_and_HR-master");

	//one.vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	//gtk_container_add(GTK_CONTAINER(one.window),one.vbox);
	//vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	//gtk_box_pack_start(GTK_BOX(one.vbox),vbox2,TRUE,TRUE,0);
	
	/*setting of the grid*/
	one.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(one.window),one.grid);
	//gtk_box_pack_start(GTK_BOX(vbox2),one.grid,TRUE,TRUE,0);
	
	/*setting of the instruction*/
	one.label1 = gtk_label_new("Here is the instruction.");
	one.frame1 = gtk_frame_new("Introduction!");
	gtk_frame_set_shadow_type(GTK_FRAME(one.frame1),GTK_SHADOW_ETCHED_OUT);
	gtk_grid_attach(GTK_GRID(one.grid),one.frame1,0,0,2,2);
	gtk_container_add(GTK_CONTAINER(one.frame1),one.label1);

	/*setting of the continue button*/
	one.button1 = gtk_button_new_with_label("Start!");
	gtk_grid_attach(GTK_GRID(one.grid),one.button1,50,50,6,1);
	g_signal_connect(G_OBJECT(one.button1),"clicked",G_CALLBACK(close_window),one.window);
	g_signal_connect(G_OBJECT(one.button1),"clicked",G_CALLBACK(window2),NULL);
	//g_signal_connect(G_OBJECT(one.button1),"clicked",G_CALLBACK(hit_and_HR_main1),&two);

	//g_print("%p\n",one.button1);
	//g_print("%p\n",one.window);

	/*hit and HR game main*/
	print_init_message(&one);
	
	g_signal_connect(one.window, "destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_widget_show_all(one.window);
	gtk_main();

	
	return 0;
}
