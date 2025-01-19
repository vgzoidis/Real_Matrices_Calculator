///                                                             MATRICES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>

//συνάρτηση που καθαρίζει το τερματικό
void clrscr(){

	system("@cls||clear");
}

//απόρριψη άκυρων τιμών (για πραγματικούς)
void get_double(double* p){

    while(!scanf( "%lf", p)){

        fflush(stdin);
        printf("Not a real number, please try again\n");
    }
}

//απόρριψη άκυρων τιμών (για ακεραίους)
void get_int(int* p) {

    while(!scanf( "%d", p)){

        fflush(stdin);
        printf("Not an integer, please try again\n");
    }
}

///matrix functions

//συνάρτηση που φτιάχνει έναν πίνακα στη μορφή αρχείου
void create_matrix(){

	char sel, invalid, matname[51], filename[56];
	int n, m; //διαστάσεις πίνακα
	bool loop = 1;
	FILE *matrix_file;

	//Παίρνουμε το όνομα από τον χρήστη.
	printf("Please name your matrix (use one word):\n");
	fflush(stdin);
	scanf("%s", matname);

	while(strcmp(matname,"r") == 0){
        printf("Sorry, the name 'r' is not available.\n");
        fflush(stdin);
        scanf("%s", matname);
	}

	//Φτιάχνουμε ένα .txt αρχείο με αυτό το όνομα.
	sprintf(filename, "%s.txt", matname);
	matrix_file = fopen(filename, "w");

	//Ζητάμε το επιθυμητό μέγεθος του πίνακα και τον φτιάχνουμε αναλόγως.
	do{

		clrscr();
		printf("Matrix: %s\n\nInput the desired number of rows:", matname);
		get_int(&n);
		printf("Input the desired number of columns:");
		get_int(&m);
		clrscr();

		printf ("You opted for %d rows and %d columns\n\n", n, m);
		double (*A)[m] = malloc(n*m*sizeof(double));

		//συμπλήρωση πίνακα
		printf("Would you like to fill the matrix with pseudorandom numbers or by yourself?\n");
		printf("1.With pseudorandom numbers\n");
		printf("2.By myself\n");
		printf("Τype 'b' to go back to the rows and columns selection screen.\n");

		fflush(stdin);
		scanf(" %c", &sel);
		switch(sel){

			case '1':

				clrscr();
				fprintf(matrix_file, "Dimensions\nrows:%d\ncolumns:%d\n", n, m);
				printf("You opted to fill the matrix with pseudorandom numbers\n\n");

				//συμπληρώνεται αυτόματα
				for(int i=0; i<n; i++){

					for(int j=0 ; j<m; j++){

						printf( "%s[%d][%d]=", matname, i+1, j+1);
						A[i][j] = rand();

						int x;
						x = printf("%.3lf", A[i][j]);
						for(int z=0; z<10-x; z++)
                            putchar(' ');

						fprintf(matrix_file, "%.3lf\t", A[i][j]);
					}
					putchar ('\n');
					fprintf(matrix_file, "\n");
				}
				fclose(matrix_file);
				printf("\nYou successfully created a matrix.\n");
				loop = 0; //σταματά το loop
				break;

			case '2':

			    clrscr();
				fprintf(matrix_file, "Dimensions\nrows:%d\ncolumns:%d\n", n, m);
				printf("You opted to fill the matrix manually\n\n");

				//συμπληρώνεται χειροκίνητα
				for(int i=0; i<n; i++){

					for(int j=0; j<m; j++){

                        printf("%s[%d][%d]=", matname, i+1, j+1);
                        get_double(&A[i][j]);
                        fprintf(matrix_file,"%.3lf\t", A[i][j]);
                    }
					putchar ('\n');
					fprintf(matrix_file, "\n");
				}
				fclose(matrix_file);

				printf ("\nYou successfully created a matrix\n");
				loop = 0; //σταματά το loop
				break;

			case 'b':
				break;

			default:

				fflush(stdin);
				printf ("Your selection was invalid.\n");
				printf ("Press 'enter' to try again.\n");
				scanf("%c", &invalid);
		}
		free(A);
	}while(loop); //η συνάρτηση θα σταματήσει αν η πίνακας έχει δημιουργηθεί επιτυχως
}

//συνάρτηση που βρίσκει τις διαστάσεις ενός πίνακα
void dim(int* p1, int* p2, char matname[51], char filename[56]){

    int rows, cols;

    fflush(stdin);
    printf("Please write the name of the matrix you want to load.\n");
    scanf("%s", matname);
    sprintf(filename, "%s.txt", matname);
    putchar('\n');
    printf ("You loaded: %s\n\n", matname);

    FILE *temp_file;
    double buff;
    temp_file = fopen(filename, "r");
    fscanf(temp_file, "Dimensions\nrows:%d\ncolumns:%d\n", &rows, &cols);
    fclose(temp_file);

    *p1 = rows;
    *p2 = cols;
}

void dim2(int* p1, int* p2, char matname[51], char filename[56]){

    int rows, cols;
    sprintf(filename, "%s.txt", matname);
    putchar('\n');
    printf ("You loaded: %s\n\n", matname);

    FILE *temp_file;
    double buff;
    temp_file = fopen(filename, "r");
    fscanf(temp_file, "Dimensions\nrows:%d\ncolumns:%d\n", &rows, &cols);
    fclose(temp_file);

    *p1 = rows;
    *p2 = cols;
}

//συνάρτηση που φορτώνει τις τιμές ενός πίνακα
void load_mat(int rows, int cols, double mat[rows][cols], char matname[51], char filename[56]){

    FILE *temp_file;
    double buff;
    temp_file = fopen(filename, "r");
    fscanf(temp_file, "Dimensions\nrows:%d\ncolumns:%d\n", &rows, &cols);

    printf("Dimensions\nrows:%d\ncolumns:%d\n\n", rows, cols);

    for(int i=0;i<rows;i++){

        for(int j=0;j<cols;j++){

            fscanf(temp_file, "%lf ", &buff);
            mat[i][j]=buff;
            printf( "%s[%d][%d]=", matname, i+1, j+1);
            int x;
            x=printf("%.3lf", mat[i][j]);
            for (int z=0; z<10-x; z++) putchar(' ');
        }
        putchar ('\n');
    }
    fclose(temp_file);
}

//τύπωση πίνακα στην κονσόλα
void print_mat(int rows, int cols, double mat[rows][cols]){

	for(int i=0; i<rows; i++){

		for(int j=0; j<cols; j++){

			int x;
            x=printf("%.3lf", mat[i][j]);
            for (int z=0; z<14-x; z++) putchar(' ');

		}
		printf("\n");
	}
}

//προβολή διαθέσιμων πινάκων
void view_mat(){

    DIR *p;
    char name[51];
    struct dirent *pp;
    p = opendir ("./");

    if (p != NULL){

        while ((pp = readdir (p))!=NULL) {

            int length = strlen(pp->d_name);
            if (strncmp(pp->d_name + length - 4, ".txt", 4) == 0) {

                sprintf(name, "%s\b\b\b\b    ", pp->d_name);
                printf("%s\n", name);
            }
        }
        (void) closedir (p);
    }
}

//γινόμενο δυο πινάκων
void product_matrix(int n, int m, int o, double A[n][m], double B[m][o], double C[n][o]){

	for(int i=0; i<n; i++)
		for(int j=0; j<o; j++)
			for(int k=0; k<m; k++)
				C[i][j] += A[i][k]*B[k][j];
}

//δημιουργία αναστρόφου πίνακα
void transpose(int n, int m, double A[n][m], double AT[m][n]){

	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
	        AT[j][i] = A[i][j];

}

//υπολογισμός ορίζουσας nxn πίνακα
double det(int n, double A[n][n]){

	double (*minor)[n-1] = malloc((n-1)*(n-1)*sizeof(double)); //ο ελλάσον πίνακας (υποπίνακας)
	double d = 0; //determinant
	int i, j, k; //μετρητές
	int mini, minj; //δείκτες των υποπινάκων

    //Αν πρόκειται για πίνακα στοιχείο η ορίζουσα ταυτίζεται με το μοναδικό στοιχείο.
	if(n==1)
    	d = A[0][0];
	//Απλός υπολογισμός ορίζουσας πίνακα 2x2.
	if(n==2)
		d = A[0][0]*A[1][1]-A[0][1]*A[1][0];
	//Yπολογισμός ορίζουσας πίνακα 3x3 με τον κανόνα του Sarrus.
	else if(n==3)
		d = A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] - A[2][0]*A[1][1]*A[0][2] - A[2][1]*A[1][2]*A[0][0] - A[2][2]*A[1][0]*A[0][1];
	//Γενική περίπτωση ορίζουσας nxn.
    else{

		for(k=0; k<n; k++){

			mini=0;
            for(i=1; i<n; i++){

                minj=0;
                for(j=0; j<n; j++){

                    if (j==k)
                        continue;
                	minor[mini][minj] = A[i][j];
                    minj++;
                }
                mini++;
            }
            d += pow(-1.0, (double)k)*A[0][k]*det(n-1, minor);
        }
    }
    free(minor);
    return d;
}

//υπολογισμός αντίστροφου πίνακα (με χρήση του συμπληρωματικού)
void inverse(int n, double A[n][n], double adj[n][n], double inv[n][n]){

	double (*minor)[n-1] = malloc((n-1)*(n-1)*sizeof(double));
	int mini, minj;
	int i, j, k, l;

	for(l=0; l<n; l++)
		for(k=0; k<n; k++){

			mini = 0;

			for(i=0; i<n; i++){

				minj = 0;

				for(j=0; j<n; j++){

					if(l==i || k==j)
						continue;
					minor[mini][minj] = A[i][j];
					minj++;
				}

				if(l==i || k==j)
					continue;
				mini++;
			}
			mini = 0;
			minj = 0;

			if((l-k)%2==0 || l-k==0){

				adj[l][k] = det(n-1, minor);
				inv[l][k] = det(n-1, minor)/det(n, A);
			}
			else{

				adj[l][k] = -det(n-1, minor);
				inv[l][k] = -det(n-1, minor)/det(n, A);
			}
		}
	free(minor);
}

///vector functions

//όταν η πράξη διανυσμάτων απαιτεί τα δύο διανύσματα να έχουν την ίδια διάσταση
int dim_vec(){

	int n1, n2;
	do {

		printf("Please insert the dimension of the first vector:");
		fflush(stdin);
		get_int(&n1);
		printf("Please insert the dimension of the second vector:");
		get_int(&n2);
		if(n1!=n2)
			printf("The two vectors need to have the same dimension!\n");

	} while(n1!=n2);

	return n1;
}

//συπλήρωση διανύσματος από τον χρήστη
void get_vec(double* v, int n){

	for(int i=0; i<n; i++){

		printf("   Element no. %d:",i+1);
		get_double(&v[i]);
		//scanf("%lf",&v[i]);
	}
}

//τύπωση διανύσματος στην κονσόλα
void print_vec(double* v, int n){

	printf("This is your result: v={");

	for(int i=0; i<n-1; i++)
		printf("%.3lf, ",v[i]);
	printf("%.3lf}",v[n-1]);
}

//εσωτερικό γινόμενο
double dot(double* v1, double* v2, int n){

	double dp = 0;
	for(int i=0; i<n; i++)
		dp += v1[i]*v2[i];

	return dp;
}

//εξωτερικό γινόμενο
void cross(double v1[3], double v2[3], double result[3]){

	result[0] = v1[1]*v2[2]-v1[2]*v2[1];
	result[1] = v1[2]*v2[0]-v1[0]*v2[2];
	result[2] = v1[0]*v2[1]-v1[1]*v2[0];
}

//μικτό γινόμενο
double mix(double v1[3], double v2[3], double v3[3]){

	double CrossResult[3];
	cross(v2, v3, CrossResult);
	return dot(v1, CrossResult, 3);
}

//time delay function
void delay(float number_of_seconds){

    float milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

//title screen function
void loading_screen(){

	float x = .4;

	printf("This will only take a few seconds...");
	printf("\n\n\n\n                         ...............");

	for(int i=0; i<15; i++)
        printf("\b");

	for(int i=0; i<2; i++){
		delay(x);
        putchar('#');
    }
	delay(0.5*x);
	for(int i=0; i<3; i++){
		delay(0.5*x);
        putchar('#');
    }
	delay(0.5*x);
	for(int i=0; i<2; i++){
		delay(x);
        putchar('#');
	}
	delay(x);
	for(int i=0; i<4; i++){
		delay(0.75*x);
        putchar('#');
    }
	for(int i=0; i<3; i++){
		delay(x);
        putchar('#');
    }
	delay (1.5*x);
	putchar('#');
	delay(0.25*x);
	clrscr();
    printf(" Welcome to our application!\n\n\n Press 'enter' to start:");
	getchar();
}



///                                                   MAIN

int main() {

    loading_screen();

    int loop=1;

	do{
		//new start
		clrscr();

		//main menu
		printf ("Please select from below, by typing the coresponding number and then hitting 'enter':\n");
        printf ("\t1.Create a new matrix\n");
        printf ("\t2.View a matrix and get info (if rows=columns)\n");
        printf ("\t3.Delete a matrix\n");
        printf ("\t4.Do matrix operations\n");
        printf ("\t5.Do vector operations\n");
        printf ("\t6.Exit\n");

        char sel, buffer;
        fflush(stdin);
		scanf("%c",&sel);

		switch(sel){

			case '1':

			    clrscr();
			    printf("You opted to create a matrix\n\n");
                create_matrix();

                fflush(stdin);
                printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                scanf("%c", &buffer);
  				break;

			case '2':
			    {
                clrscr();
				printf("You opted to view a matrix\n\nHere are the matrices available for viewing:\n");
				view_mat();
				putchar('\n');

				int n, m;
                int i, j;
                char matname[51], filename[56];
                fflush(stdin);
                printf("Please write the name of the matrix you want to load or 'r' to return.\n");
                scanf("%s", matname);

                if(strcmp(matname,"r") == 0)
                    break;
                printf("\n");
                dim2(&n, &m, matname, filename);
                double (*A)[m] = malloc(n*m*sizeof(double));

                load_mat(n, m, A, matname, filename);

                    if(n==m){
                    printf ("\nHere is some information about the matrix you chose:\n\n");
                    printf("Matrix determinant: det(%s)=%.3lf\n", matname, det(n, A));

                    if(det(n, A)!=0){

                        printf("Matrix %s is invertible.\n", matname);

                        double (*adj)[n] = malloc(n*n*sizeof(double));
                        double (*inv)[n] = malloc(n*n*sizeof(double));

                        inverse(n, A, adj, inv);
                        printf("This is the adjacency matrix of %s:\n", matname);
                        print_mat(n, n, adj);
                        printf("This is the inverse matrix of %s:\n", matname);
                        print_mat(n, n, inv);

                        free(adj);
                        free(inv);
                    }

                    double trace = 0;
                    for(i=0; i<n; i++)
                        for(j=0; j<n; j++)
                            if(i==j)
                                trace += A[i][j];
                    printf("Matrix trace: tr(%s)=%.3lf\n", matname, trace);

                    bool id=1, ut=1, lt=1;
                    for(i=0; i<n; i++){

                        for(j=0; j<n; j++){

                            if(A[i][i]!=1)
                                id = 0;
                            if(i!=j)
                                if(A[i][j]!=0)
                                    id = 0;

                            if(i>j)
                                if(A[i][j]!=0)
                                    ut = 0;
                            if(i<j)
                                if(A[i][j]!=0)
                                    lt = 0;

                            if(!id && !ut && !ut)
                                break;
                        }
                        if(!id && !ut && !ut)
                            break;
                    }
                    if(id)
                        printf("Matrix %s is an identity matrix.\n", matname);
                    else if(ut && lt)
                        printf("Matrix %s is diagonal.\n", matname);
                    else if(ut)
                        printf("Matrix %s is upper triangular.\n", matname);
                    else if(lt)
                        printf("Matrix %s is lower triangular.\n", matname);
                    else
                        printf("Matrix %s is a square matrix.\n", matname);

                    double (*AT)[n] = malloc(n*n*sizeof(double));
                    transpose(n, n, A, AT);
                    bool sym=1, antisym=1;
                    for(i=0; i<n; i++)
                        for(j=0; j<n; j++){

                            if(A[i][j]!=AT[i][j])
                                sym = 0;
                            if(A[i][j]!=-AT[i][j])
                                antisym = 0;

                            if(sym==0 && antisym==0)
                                break;
                        }
                    printf("This is the traspose matrix of %s:\n", matname);
                    print_mat(n, n, AT);
                    putchar('\n');
                    free(AT);

                    if(sym)
                        printf("Matrix %s is symmetric.\n", matname);
                    else if(antisym)
                        printf("Matrix %s is antisymmetric.\n", matname);

                    double (*A2)[n] = calloc(n*n, n*n*sizeof(double));
                    product_matrix(n, n, n, A, A, A2);
                    bool involutory = 1;

                    for(i=0; i<n; i++){

                        for(j=0; j<m; j++)
                            if(A[i][j]!=A2[j][i]){

                                involutory = 0;
                                break;
                            }

                        if(A[i][j]!=A2[j][i])
                            break;
                    }
                    free(A2);
                    if(involutory)
                        printf("Matrix %s is involutory.\n", matname);
                }
                else
                    printf("\nMatrix '%s' doesn't belong to any general category of matrices.\n", matname);

                free(A);

                fflush(stdin);
				printf ("\n\nPress 'enter' to go back to the selection menu.\n");
				scanf("%c", &buffer);

				break;
                }
			case '3':

                clrscr();
				printf("You opted to delete a matrix\n\nHere are the matrices available for deleting:\n");
				view_mat();

				char name_of_the_matrix[51], name_of_the_matrix_file[56];
				fflush(stdin);
                printf("\nPlease write the name of the matrix you want to delete or 'r' to return.\n");
                scanf("%s", name_of_the_matrix);

                if(strcmp(name_of_the_matrix,"r") == 0) break;
                printf("\n");
				sprintf(name_of_the_matrix_file, "%s.txt", name_of_the_matrix);

				if (remove(name_of_the_matrix_file) == 0)
	      			printf("Deleted successfully");
	   			else
					printf("Unable to delete the matrix");

				fflush(stdin);
				printf ("\n\nPress 'enter' to go back to the selection menu.\n");
				scanf("%c", &buffer);
				break;

			case '4':

                clrscr();
                printf("You have chosen to do matrix operations.\n");

                //menu 3
                printf("\t1. Add/Substract Matrices (they must have the same dimension!)\n");
                printf("\t2. Multiply Matrix With Number\n");
                printf("\t3. Multiply Matrices (columns of the first matrix must equal rows of the second matrix!)\n");
                printf("\tPress 'r' to return\n");

                char menu3;
                fflush(stdin);
                scanf("%c", &menu3);

                while(menu3!='1' && menu3!='2' && menu3!='3' && menu3!='r'){

                    printf("\n '%c' was not a valid choice\n", menu3);
                    fflush(stdin);
                    menu3 = getchar();
                    //Δεκτές μόνο οι τιμές: 1, 2, 3.
                }

                if(menu3=='1'){

                    clrscr();
                    printf("Add/Substract Matrices.\n\nAvailable:\n");
                    view_mat();
                    putchar('\n');

                    int n1, m1, n2, m2;
                    int i, j;
                    char matname1[51], matname2[51], filename1[56], filename2[56];

                    dim(&n1, &m1, matname1, filename1);
                    dim(&n2, &m2, matname2, filename2);
                    while(n1!=n2 || m1!=m2){

                        printf("The two matrices need to have the same dimentions!\n");
                        printf("Please try again.\n");
                        dim(&n1, &m1, matname1, filename1);
                        dim(&n2, &m2, matname2, filename2);
                    }

                    int n=n1, m=m1;
                    double (*A)[m] = malloc(n*m*sizeof(double));
                    double (*B)[m] = malloc(n*m*sizeof(double));
                    load_mat(n, m, A, matname1, filename1);
                    load_mat(n, m, B, matname2, filename2);


                    clrscr();
                    printf("Press 'a' to add or 's' to substract.\n");
                    char sel;
                    fflush(stdin);
                    scanf("%c", &sel);

                    while(sel!='a' && sel!='s'){


                        printf("\n '%c' was not a valid choice\n", sel);
                        fflush(stdin);
                        sel = getchar();
                        //Δεκτές μόνο οι τιμές: a, s.
                    }
                    putchar('\n');

                    if(sel=='a'){

                        printf("This is the matrix %s+%s:\n\n", matname1, matname2);
                        for(i=0; i<n; i++){

                            for(j=0; j<m; j++)
                                printf("%.3lf ", A[i][j]+B[i][j]);

                            printf("\n");
                        }
                    }
                    else if(sel=='s'){

                        printf("This is the matrix %s-%s:\n\n", matname1, matname2);
                            for(i=0; i<n; i++){

                            for(j=0; j<m; j++)
                                printf("%.3lf ", A[i][j]-B[i][j]);

                            printf("\n");
                        }
                    }

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);
                    free(A);
                    free(B);
                }
                else if(menu3=='2'){

                    clrscr();
                    printf("Multiply Matrix With Number\n\n");
                    printf("Available:\n");
                    view_mat();
                    putchar('\n');

                    int n, m;
                    int i, j;
                    char matname[51], filename[56];
                    fflush(stdin);
                    dim(&n, &m, matname, filename);
                    double (*A)[m] = malloc(n*m*sizeof(double));
                    double l;

                    printf("Please input the real number with which you want to multiply your matrix:");
                    fflush(stdin);
                    get_double(&l);

                    load_mat(n, m, A, matname, filename);
                    clrscr();

                    for(int i=0; i<n; i++)
                        for(int j=0; j<m; j++)
                            A[i][j] *= l;

                    printf("This is the matrix %s*%.2lf :\n\n", matname, l);
                    print_mat(n, m, A);

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);
                    free(A);

                }
                else if(menu3=='3'){

                    clrscr();
                    printf("Multiply Matrices \n\n");
                    printf("Available:\n");
                    view_mat();
                    putchar('\n');
                    int n1, m1, n2, m2;
                    int i, j;
                    char matname1[51], matname2[51], filename1[56], filename2[56];

                    dim(&n1, &m1, matname1, filename1);
                    dim(&n2, &m2, matname2, filename2);
                    while(m1!=n2){

                        printf("The first matrix needs to have as much columns as the rows of the second matrix!\n");
                        printf("Please try again.\n\n");
                        dim(&n1, &m1, matname1, filename1);
                        dim(&n2, &m2, matname2, filename2);
                    }

                    double (*A)[m1] = malloc(n1*m1*sizeof(double));
                    double (*B)[m2] = malloc(n2*m2*sizeof(double));
                    double (*C)[m2] = malloc(n1*m2*sizeof(double));

                    load_mat(n1, m1, A, matname1, filename1);
                    load_mat(n2, m2, B, matname2, filename2);
                    clrscr();

                    product_matrix(n1, m1, m2, A, B, C);
                    printf("This is the matrix %s*%s:\n\n", matname1, matname2);
                    print_mat(n1, m2, C);

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);

                    free(A);
                    free(B);
                    free(C);
                }
                break;

            case '5':

                clrscr();
                printf("You have chosen to do vector operations.\n\n");

                //vector operations menu
                printf("Choose one of the following options by pressing the corresponding key, ranging from 1 to 5:\n");
                printf("\t1. Add/Substract Vectors\n");
                printf("\t2. Multiply Vector With Number\n");
                printf("\t3. Dot Product\n");
                printf("\t4. Cross Product\n");
                printf("\t5. Mix Product\n");
                printf("\tPress 'r' to return\n");

                char menu21;
                fflush(stdin);
                scanf("%c", &menu21);
                while(menu21!='1' && menu21!='2' && menu21!='3' && menu21!='4' && menu21!='5' && menu21!='r'){

                    printf("\n '%c' was not a valid choice\n", menu21);
                    fflush(stdin);
                    menu21 = getchar();
                    //Δεκτές μόνο οι τιμές: 1, 2, 3, 4, 5, r.
                }

                clrscr();
                if(menu21=='1'){

                    printf("You have chosen to add/substract vectors.\n");

                    int i, n=dim_vec();
                    double* v1 = (double*) malloc(n*sizeof(double));
                    double* v2 = (double*) malloc(n*sizeof(double));
                    double* v3 = (double*) malloc(n*sizeof(double));

                    printf("Vector 1:\n");
                    get_vec(v1, n);

                    printf("\nVector 2:\n");
                    get_vec(v2, n);
                    putchar('\n');

                    printf("Press 'a to add or 's' to substract.\n");
                    char sel;
                    fflush(stdin);
                    scanf("%c", &sel);

                    while(sel!='a' && sel!='s'){

                        printf("\n '%c' was not a valid choice\n", sel);
                        fflush(stdin);
                        sel = getchar();
                        //Δεκτές μόνο οι τιμές: a, s.
                    }

                    if(sel=='a')
                        for(i=0; i<n; i++)
                            v3[i] = v1[i]+v2[i];

                    else if(sel=='s')
                        for(i=0; i<n; i++)
                            v3[i] = v1[i]-v2[i];

                    print_vec(v3, n);

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);
                    free(v1);
                    free(v2);
                    free(v3);
                }
                else if(menu21=='2'){

                    printf("You have chosen to multiply vector with number.\n");

                    int n, i;
                    printf("Insert the dimension of the vector:");
                    //scanf("%d", &n);
                    get_int(&n);

                    double* v1 = (double*) malloc(n*sizeof(double));

                    printf("Vector [%d] :\n", n);
                    fflush(stdin);
                    get_vec(v1, n);
                    putchar('\n');

                    double l;
                    printf("Input the real number with which you want to multiply the vector:");
                    //scanf("%lf",&l);
                    fflush(stdin);
                    get_double(&l);

                    for(i=0; i<n; i++)
                        v1[i] *= l;

                    putchar('\n');
                    print_vec(v1, n);

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);
                    free(v1);
                }
                else if(menu21=='3'){

                    printf("You have chosen dot product.\n");

                    int n=dim_vec();
                    double* v1 = malloc(n*sizeof(double));
                    double* v2 = malloc(n*sizeof(double));

                    printf("Vector 1:\n");
                    get_vec(v1, n);
                    putchar('\n');
                    printf("Vector 2:\n");
                    get_vec(v2, n);
                    putchar('\n');

                    printf("This is the dot product: %.3lf", dot(v1, v2, n));

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);
                    free(v1);
                    free(v2); //Αποφεύγω το memory leak
                }
                else if(menu21=='4'){

                    printf("You have chosen cross product.\nNote: cross product is defined only for 3D vectors.\n\n");

                    double v1[3], v2[3], v3[3];
                    printf("Vector 1:\n");
                    get_vec(v1, 3);
                    printf("Vector 2:\n");
                    get_vec(v2, 3);
                    putchar('\n');

                    cross(v1, v2, v3);
                    print_vec(v3, 3);

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);
                }
                else if(menu21=='5'){

                    printf("You have chosen mixed product.\n\nNote: Mixed product is defined only for 3D vectors.\n");
                    printf("Please first input the two vectors you want to dot multiply and then the third for cross multiplication.\n\n");

                    double v1[3], v2[3], v3[3];

                    printf("Vector 1:\n");
                    get_vec(v1, 3);
                    printf("Vector 2:\n");
                    get_vec(v2, 3);
                    printf("Vector 3:\n");
                    get_vec(v3, 3);

                    printf("\nMixed product is %.3lf", mix(v1, v2, v3));

                    fflush(stdin);
                    printf ("\n\nPress 'enter' to go back to the selection menu.\n");
                    scanf("%c", &buffer);

                }
                break;

			case '6':

			    clrscr();

			    fflush(stdin);
			    printf("You opted to exit\n\nPress 'c' to confirm or 'm' to go back to the main menu:");
				scanf("%c", &buffer);
				if(buffer=='c')loop=0;
				break;

			default:

				printf ("Your selection was invalid.\n");

				fflush(stdin);
				printf ("Press 'enter' to try again.\n");
				scanf("%c", &buffer);
				break;
		}
	}while(loop);

    return 0;
}
