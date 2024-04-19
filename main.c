///Khuffash

/*
 * NV -> Number of Vertex.
 *
 * Structs at line 25
 *
 * Global Variable Decleration at line 33
 *
 * General Functions at line 42
 *
 * Dijkstra at line at line 156
 *
 * Main at line 324
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 500
#define NV  count_vert()
#define INF 999999

///--------------------------------------------------------- STRUCTS ---------------------------------------------------------//
//this struct to keep track of cities in numbers
struct ident
{
    int id;
    char city[MAX];
};

///---------------------------------------------------------Global Variable Decleration-------------------------------------------------------//
//input file
FILE *cities_file;
//output file
FILE *shortest_path;
//array to keep track of cities
struct ident *IDZ[15];


///---------------------------------------------------------General Functions---------------------------------------------------------//

void sys()
{
    system("color a");
    system("title Khuffash-Graphs Project");
}

//this function will intialaize IDZ array and locate memory location for it
void Intialaize_Everything()
{
    int count = NV;

    //this for loop to locate a memory location in memory cell
    for(int i=0; i<count; i++)
    {
        IDZ[i]=(struct ident *)malloc(sizeof(struct ident));//allocating space 'malloc'
    }


}


//this function will count the vertices in the file and return the number of it.
int count_vert()
{
    cities_file=fopen("Cities.txt","r");
    int count;

    //To store the line in it
    char line[MAX];

    //this string to keep track of the last city that has been read
    char city[MAX];

    //the initial value of it is empty -> no previous city.
    strcpy(city,"");


    char city2[MAX];

    //Keep reading until  the file is empty
    while(!feof(cities_file))
    {
        //this will get the line
        fgets(line,500,cities_file);

        //this will cut the line for spaces
        int *cutter=strtok(line,"  \n");

        //store the first vertex in city2
        strcpy(city2,cutter);

        //if statement to check if the city2 is not equal to the previuos city that has been read, if so then increment the counter and change "city"
        if(strcmp(city2,city)!=0)
        {
            count++;
            strcpy(city,city2);

        }

    }

    //close the file
    fclose(cities_file);
    return count;
}

//this function will give identites to citys , according to its location in file, st : akka-> 0, Yafa->14 and so on.
void give_Ident()
{
    //setting the file to read data only.
    cities_file=fopen("Cities.txt","r");

    //intialaising needed variables
    int count=0;
    char line[MAX];

    char city[MAX];

    strcpy(city,"");

    char city2[MAX];

    while(!feof(cities_file))//keep reading data untill the file is empty
    {

        fgets(line,500,cities_file);

        int *cutter=strtok(line,"  \n");
        strcpy(city2,cutter);

        //if statement to check if the city that has been read equal to "city", if not then incremnet counter and add it to IDZ struct, st Akka->0  idz[0]->id=0, idz[0]->city=akka and so on
        if(strcmp(city2,city)!=0)
        {
            IDZ[count]->id=count;
            strcpy(IDZ[count]->city,city2);

            count++;
            strcpy(city,city2);
        }
    }

}

//this function will print the menu
void print_Menu()
{
    printf("1. Load cities: loads the file and construct the graph\n");
    printf("2. Enter source city: read the source city and compute the Dijkstra algorithm (single source shortest path)\n");
    printf("3. Enter destination city: print the full route of the shortest path including the distance between each two cities and the total shortest cost\n");
    printf("4. Exit: prints the information of step 3 to a file called shortest_path.txt and exits the program");
}

///---------------------------------------------------------Dijkstra---------------------------------------------------------\\

//this function will find the shortest path of a given source, According to Greedy algo.
void Dijkstra_Function(int cities[NV][NV],int source,int destination,int Vert_Count)
{
    //setting the file to "append", hence every time we write on the file we will not lose the data.
    shortest_path=fopen("shortest_path.txt","a");

    //this array will contain the shortest distance from source to each vert.
    int Shortest_distance[Vert_Count]; ///int array

    //this array will contain the "shortest" path from source to each vert, including the vert and its cost.
    // char path[Vert_Count][MAX];

    //this array will contain a " checker " if the vert is included in "shortest distance array" , hence vistied . or not. BOOL -> true : vistited , False: not visited
    bool visited[Vert_Count]; ///boolean array

    //this array will keep the track of the path
    int path[Vert_Count];  ///int array

    //
    int cost[Vert_Count];///int array


    //this for loop will itialaize the arrays, shortest distance -> INF , cuz at fist we dont know the distances and it will be infenity
    //path array will be empty at fist , and checker array will be false , cuz non vert is visted -> included in shortest distance
    for(int i=0; i<Vert_Count; i++)
    {
        Shortest_distance[i]=INF;//set every index to INF , at first no vertex visited , hence infenity cost
        path[i]=-1;//set every index to -1
        cost[i]=-1;
        visited[i]=false;
    }

    //updating the distance from source to source :0 , cuz the distance from city to it self is 0
    Shortest_distance[source]=0;

    //this for loop will find the shortest distance from source to all vertices.
    for(int i=0; i<Vert_Count-1; i++)
    {
        //intialaizing variables
        int index,min=INF,mIndex;

        //this for loop and according to "greedy algo"  will find the shortest path "minimum cost", and not visited-> checker is false for it.
        for(int g=0; g<Vert_Count; g++)
        {
            if(visited[g]==false && Shortest_distance[g] <= min)
            {
                min=Shortest_distance[g];
                mIndex=g;
            }
        }

        //change the index to minimum index
        index=mIndex; //greedy algo

        //change the checker to true ,cuz its visited
        visited[index]=true; //is visited

        //this for loop will update the shortest distance array
        for(int j=0; j<Vert_Count; j++)
        {
            //conditions, 1. to check if the vert is visited, 2. to check if there is connection betwen source and vert .(!=0) , 3.to check if the path need to be selected is less than the one has been recorded
            if(!visited[j] && cities[index][j] && Shortest_distance[index] != INF && Shortest_distance[index]+cities[index][j] < Shortest_distance[j])
            {
                //add the route in array path
                path[j]=index;
                //add the shortest path 'cost' to array shortest_distance
                Shortest_distance[j]=Shortest_distance[index]+cities[index][j];
            }
        }

    }

    //this to convert id back to cities and print the required
    char from[50];
    char to[50];

    for(int i=0; i<Vert_Count; i++)
    {
        if(source==IDZ[i]->id)
        {
            strcpy(from,IDZ[i]->city);
        }
        if(destination==IDZ[i]->id)
        {
            strcpy(to,IDZ[i]->city);
        }

    }

    //--------------------------------------printing formula--------------------------//

    printf("The distance from Source( ");

    //Set the text to the color red
    printf("\033[0;31m");
    printf("%s",from);
    //Resets the text to default color
    printf("\033[0m");

    printf(") to Destination(");

    //Set the text to the color red
    printf("\033[0;31m");
    printf("%s",to);
    //Resets the text to default color
    printf("\033[0m");

    printf(") : ");

    //Set the text to the color red
    printf("\033[0;31m");
    printf("%d KM\n",Shortest_distance[destination]);
    //Resets the text to default color
    printf("\033[0m");

    //this line will print in file the shortest distance from source to distination
    fprintf(shortest_path,"The shortest path from (%s) to (%s) is: %d KM\n",from,to,Shortest_distance[destination]);

    //callling the function that will find the route from source to destination
    Cost_path(path,destination,cost,1);

    printf("Path: ");

    //Set the text to the color red
    printf("\033[0;31m");

    printf("%s",from);
    fprintf(shortest_path,"Path: %s",from);

    int k=source;
    int l=0;

    //for loop to print the path and cost;
    for(int i=Vert_Count-1;i>0;i--)
    {
        if(cost[i]!=-1)
        {
            l=cost[i];
            //print the path at console
            printf("--(%d)-->%s",cities[k][l],IDZ[cost[i]]->city);
            //print the path at file
            fprintf(shortest_path,"--(%d)-->%s",cities[k][l],IDZ[cost[i]]->city);
            k=cost[i];
        }
    }
    fprintf(shortest_path,"\n");
    printf("\n");

    //Resets the text to default color
    printf("\033[0m");

}

//this Function will find the path and cost for every route that the dijkstra took, via recursion.
void Cost_path(int path[],int des,int cost[],int index)
{
    //if path ==-1 then return *end* , base case
    if(path[des]==-1)
        return ;

    Cost_path(path,path[des],cost,index+1);

    //adding the route , so it will be used in finding the cost.
    cost[index]=des;
}

///---------------------------------------------------------Main---------------------------------------------------------\\

int main()
{
    sys();
    //store the number of vert in another variable
    int Ver_count=NV;

    //calling function to intialize IDZ.
    Intialaize_Everything();

    //calling function to give the identities for every city
    give_Ident();

    //intialaising the Adj matrix, every index =0
    int Cities[Ver_count][Ver_count]; ///ADJ - MATRIX

    for(int i=0; i<Ver_count; i++)
    {
        for(int j=0; j<Ver_count; j++)
        {
            Cities[i][j]=0; //will be intialiesed to 0 ,and then changed
        }
    }

    //flag to check if file is loaded or not
    int flag=0;

    //while loop to keep looping
    while (1)
    {
        //display the menu
        print_Menu();

        int choice;
        printf("\nPlease Enter Your Choice: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            system("cls");//clear console

            //change the flag

            flag=1;

            //intialize the file to read.
            cities_file=fopen("Cities.txt","r");

            //variables
            char line[500];
            char city1[50];
            char city2[50];
            int dis;


            //intializing the Adj Matrix 'cities'
            while(!feof(cities_file))
            {
                fgets(line,500,cities_file);

                int *cutter=strtok(line,"  \n");
                strcpy(city1,cutter);

                cutter=strtok(NULL," \n");
                strcpy(city2,cutter);


                cutter=strtok(NULL," \n");
                dis=atoi(cutter);

                int s,d;

                for(int i=0; i<Ver_count; i++)
                {
                    //comparing the city that has been read from the file to get its id. st. Akka -> 0 and so on
                    if(strcmp(IDZ[i]->city,city1)==0)
                    {
                        s=IDZ[i]->id;
                    }
                    if(strcmp(IDZ[i]->city,city2)==0)
                    {
                        d=IDZ[i]->id;
                    }
                }
                Cities[s][d]=dis;
            }

            printf("\033[0;31m");//Set the text to the color red
            printf("File Has Been Loaded!\n");
            printf("\033[0m");


            break;

        case 2:
            system("cls");

            if(flag==0)
            {
                printf("\033[0;31m"); //Set the text to the color red
                printf("Please Load the File First!\n");
                printf("\033[0m"); //Resets the text to default color
                break;
            }
            char from[50];
            char to[50];
            printf("Please Enter Your Source city: ");
            getchar();
            gets(from);

            int k=-1;

            for(int i=0; i<Ver_count; i++)
            {
                if(strcmp(from,IDZ[i]->city)==0)
                    k=1;
            }
            system("cls");
            if(k==1)
            {
                printf("%s ",from);
                printf("\033[0;31m");//Set the text to the color red
                printf(":Source Accepted!\n");
                printf("\033[0m"); //Resets the text to default color

            }
            else
            {
                printf("%s ",from);
                printf("\033[0;31m");//Set the text to the color red
                printf(":Source Not Found!\n");
                printf("\033[0m"); //Resets the text to default color
            }


            break;

        case 3:
            system("cls");
            if(flag==0)
            {
                printf("\033[0;31m"); //Set the text to the color red
                printf("Please Load the File First!\n");
                printf("\033[0m"); //Resets the text to default color
                break;
            }

            if(k!=1)
            {
                printf("\033[0;31m"); //Set the text to the color red
                printf("Please Enter a correct source!\n");
                printf("\033[0m"); //Resets the text to default color
                break;
            }


            printf("\033[0;31m");//Set the text to the color red
            printf("Source: ");
            printf("\033[0m"); //Resets the text to default color
            printf("%s\n",from);
            printf("Please Enter Your Destination city: ");
            getchar();
            gets(to);



            int source=0;
            for(int i=0; i<Ver_count; i++)
            {
                if(strcmp(IDZ[i]->city,from)==0)
                    source=i;
            }

            int destination=0;
            for(int i=0; i<Ver_count; i++)
            {
                if(strcmp(IDZ[i]->city,to)==0)
                    destination=i;
            }

            Dijkstra_Function(Cities,source,destination,Ver_count); ///dijkstra function call


            break;

        case 4:
            //to free the location of idz
             for(int i=0;i<Ver_count;i++)
             {
                 free(IDZ[i]);
             }

              printf("\033[0;31m"); //Set the text to the color red
              printf("Thank you for your Time & Patience!");
              printf("\033[0m"); //Resets the text to default color


            exit(0);
            break;

        default:
            system("cls");
            printf("\033[0;31m"); //Set the text to the color red
            printf("WRONG CHOICE - Re-Enter\n");
            printf("\033[0m"); //Resets the text to default color
        }
    }

    return 0;
}

