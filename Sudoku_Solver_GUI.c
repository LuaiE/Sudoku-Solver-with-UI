#include <gtk/gtk.h>
// Code : Here include your necessary library(s)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
// Code : Write your global variables here, like:
#define N 9
/* Code : write your functions here , or the declaration of the function/
For example write the recursive function solveSudoku(), like: */
int count=0;
GtkWidget *sol;

void ten(int a[N][N]){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (a[i][j]==0){
                a[i][j]=10;
            };
        }
    }
}
bool validRows(int a[N][N]){
    int col[N]={0};
    int x=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
           if(a[i][j]>19){
                return false;
            }
            if (a[i][j]!=10){
            if (a[i][j]>10){
                x=a[i][j]-10;
            }
            else{
                x=a[i][j];
            }
            col[x-1]=col[x-1]+1;
            if (col[x-1]>1){
                return false;
            }
        }
        }
        for (int f=0; f<N; f++){
            col[f]=0;
        }
    }
    return true;
}
bool validBoxes(int a[N][N]){
    for (int t=0; t<3; t++){
        for (int q=0; q<3; q++){
    int box[N]={0};
    int x=0;
    for (int i=0+(t*3); i<3+(t*3); i++){
        for (int j=0+(q*3); j<3+(q*3); j++){
         if(a[i][j]>19){
                return false;
            }
            if (a[i][j]!=10){
            if (a[i][j]>10){
                x=a[i][j]-10;
            }
            else{
                x=a[i][j];
            }
            box[x-1]=box[x-1]+1;
            if (box[x-1]>1){
                return false;
            }
        }       
        }
    }
        }
    }
    return true;
}
bool validCollumns(int a[N][N]){
    int row[N]={0};
    int x=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if(a[j][i]>19){
                return false;
            }
            if (a[j][i]!=10){
            if (a[j][i]>10){
                x=a[j][i]-10;
            }
            else{
                x=a[j][i];
            }
            row[x-1]=row[x-1]+1;
            if (row[x-1]>1){
                return false;
            }
        }
        }
        for (int f=0; f<N; f++){
            row[f]=0;
        }
    }
    return true;
}


bool validGrid(int a[N][N]){
    return (validRows (a)&& validCollumns(a) && validBoxes(a));
}
void print(int a[N][N]){
    int x=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (a[i][j]>9){
                x=a[i][j]-10;
            }
            else {
                x=a[i][j];
            }
            printf("%d  ",x);
            if((j+1)%3==0){
                printf("|");
            }
        }
        if((i+1)%3==0){
            printf("\n_____________________");
        }
        printf("\n");
    }
}
int prev(int a[N][N], int col, int row){
    for (int c=col; c>=0; --c){
        if (a[row][c]>10){
            return c;
        }
    }
    return -1;
}
void solveSudoku (int a[N][N])
{
    ten(a);
    if ((validGrid(a))==true){
    count=0;
//Code: count+1, thenumber of times thefunction was called.
//Code: here write the implementation of solveSudoku.
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            count=count+1;
            if(a[i][j]>9){
                a[i][j]=a[i][j]+1;
                while ((validGrid(a)==false)){
                a[i][j]=a[i][j]+1;            
                if (a[i][j]>19){
                    a[i][j]=10;
                    j=prev(a, j, i)-1;
                    if (j<0){
                        i=i-1;
                        j=prev(a, N, i)-1;
                    }
                    break;
                }
                } 

            }
            
        }
    }
    }
}
// gcc -o Gtk_example Gtk_example.c `pkg-config --cflags --libs gtk+-3.0`
// Function to handle button click event

void reset_clicked(GtkWidget *widget, gpointer data) {
GtkWidget **entries = (GtkWidget **)data;
char str[50];
sprintf(str, "%d", (0));   
GdkRGBA color;
gdk_rgba_parse(&color, "black");
gtk_label_set_text(GTK_LABEL(sol)," ");
for(int i=0; i<81; i++){
    gtk_widget_override_color(entries[i], GTK_STATE_FLAG_NORMAL, &color);    
    (gtk_entry_set_text(GTK_ENTRY(entries[i]), " "));
}
}




void button_clicked(GtkWidget *widget, gpointer data) {
    // Cast the data pointer back to its original type
    GtkWidget **entries = (GtkWidget **)data;
    // Get the text from the entry fields
    int grid[N][N]={0};
    int w=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
         grid[i][j] = atoi(gtk_entry_get_text(GTK_ENTRY(entries[w])));
        w=w+1;
        }
    }
    // Print the text to console (Terminal)
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
         printf("Entry a[%d][%d]: %d\n",i, j, grid[i][j]);
        }
    }
    ten(grid);
    if(validGrid(grid)==false){
    gtk_label_set_text(GTK_LABEL(sol),"No Solutions");
    }
    else{
    solveSudoku(grid);
    w=0;
    char str[50];
    
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
        GdkRGBA color;
        if (grid[i][j]>9){
          sprintf(str, "%d", (grid[i][j]-10));   
          gdk_rgba_parse(&color, "red");
       }
       else{
        sprintf(str, "%d", grid[i][j]);
         gdk_rgba_parse(&color, "black");
       }
        gtk_widget_override_color(entries[w], GTK_STATE_FLAG_NORMAL, &color);    
         (gtk_entry_set_text(GTK_ENTRY(entries[w]), str));
        w=w+1;
        }
    }
    char s[100]="A solution exists and was found after ";
    char s2[20];
    sprintf(s2, "%d", count);
    strcat(s, s2);
    char s3[20]=" iterations.";
    strcat(s, s3);
     gtk_label_set_text(GTK_LABEL(sol), s);

    }
}
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry[81];
    GtkWidget *button;
    GtkWidget *button2;
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku Solver");
    //  The following line of code, closes the app (not just the window opened) from terminal, if you click close
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 20 size distance from the border of outer window. 
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    // Create a new gridls. We will later put buttons in it.
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    // Create two entry fields. The places that user can have entires.
GdkRGBA color;
for (int i=0; i<81; i++){
        entry[i]= gtk_entry_new();
        gtk_entry_set_max_length(GTK_ENTRY(entry[i]), 2);
        gtk_entry_set_width_chars(GTK_ENTRY(entry[i]), 2);
        }

color.red=8/5;
color.blue=0.4;
color.green=0.4;
color.alpha=0.75;
int u=0;
for (int n=0; n<3; n++){
  for (int g=0; g<3; g++){
    for (int v=0; v<9; v++){
    gtk_widget_override_background_color(entry[u], GTK_STATE_FLAG_NORMAL, &color);  
    u=u+1;
    
    if ((v+1)%3==0){
        color.red=(v)/5;
    }
    }
  }
        color.blue=(color.blue+0.2);
        color.green=(color.green+0.2);

}

    
    //gdk_rgba_parse(&color, "(1.0, 0.0, 0.0, 1.0)");
    // attach the entry(s) to the grid, and specify the location
    int h=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
        gtk_grid_attach(GTK_GRID(grid), entry[h], j, i, 1, 1);
        h=h+1;
        }
    }

    // Attach the entry(s) to the grid, and specify the location
    

    // Create a button with name "Submit"
    
    button = gtk_button_new_with_label("Submit"); 
    button2= gtk_button_new_with_label("Reset"); 
    // if the button is click execute the function button_clicked
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), entry);
    g_signal_connect(button2, "clicked", G_CALLBACK(reset_clicked), entry);
    // attach the button to the grid, and specify the location
    gtk_grid_attach(GTK_GRID(grid), button, -1, 9, 12, 1);
    gtk_grid_attach(GTK_GRID(grid), button2, -1, 10, 12, 1);
    sol=gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), sol, -1, -1, 12, 1);
    
    // It is a loop because the window will be shown and it will stay opened.
    // Show all widgets
    gtk_widget_show_all(window);
    // Start the GTK main loop. 
    gtk_main();
    

    return 0;
}
