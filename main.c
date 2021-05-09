#include <stdio.h>
#include <stdlib.h>

int greedy_travers_agent(int l);
int a_star_travers_agent(int l);
int greedy_best_node(int l);
int a_star_best_node(int l);

// for state's name & their heuristic cost

struct STATE
{
    char name[50];
    int straight_cost;
} states[20];

// for second best node of a*

struct a_star_second_best_node
{
    int node;
    int value;
}a_star_second_best;

int visited[21],a[21][21],n=20,g[20];
int c=0,x=0;

int main()
{
    int i,j;

    for(int k=1;k<=n;k++)
    {
        visited[k]=0;
        g[k]=0;
    }

// taking nodes name and their heuristic value from 'state.txt' file

    FILE *st;

    st=fopen("state.txt","r");

    if(st==NULL) exit(1);

    for(i=1;i<=n;i++)
    {
            fscanf(st,"%s",&states[i].name);
            fscanf(st,"%d",&states[i].straight_cost);
    }

//print

    printf("\n heuristic cost : \n");

    for(i=1;i<=n;i++)
    {
            printf("\n %s \n",states[i].name);
            printf("\n %d \n",states[i].straight_cost);
    }

// taking romania map from 'file.txt' file.

    FILE *fp;

    fp=fopen("file.txt","r");

    if(fp==NULL) exit(1);

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            fscanf(fp,"%d",&a[i][j]);
        }
    }

//print

    printf("\n\n\n");

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            printf(" %d ",a[i][j]);
        }
        printf("\n");
    }

    // call functions

    printf(" \n # greedy search visiting path : \n\n");

    int start=1;

    greedy_travers_agent(start);

    for(int k=1;k<=n;k++)
    {
        visited[k]=0;
    }

    printf(" \n\n\n # a star search visiting path : \n\n");

    g[start]=0;

    a_star_second_best.value=99999;

    a_star_travers_agent(start);

    printf("\n\n");

    return 0;
}

// greedy search travers agent

int greedy_travers_agent(int l)
{
    if(c==0)

    {

      printf(" --> %s ",states[l].name);
      visited[l]=1;

// give the sates for reaching goal

   if(states[l].straight_cost==0)
   {
       c=1;
   }

   if(c!=1)
   {
             int i=greedy_best_node(l);

              greedy_travers_agent(i);
   }

    }

}

// find best node of greedy search

int greedy_best_node(int l)
{
   int min=99999;
   int best;

   for(int i=1;i<=n;i++)
  {
       if((a[l][i]!=0)&&(visited[i]==0))
          {
              if(states[i].straight_cost<min)
              {
                  min=states[i].straight_cost;
                  best=i;
              }
          }
  }

  return best;
}

// a star travers agent

int a_star_travers_agent(int l)
{
    if(x==0)
    {
      int v=g[l]+states[l].straight_cost;

      printf(" --> %s (%d) ",states[l].name,v);
      visited[l]=1;

// give the sates for reaching goal

   if(states[l].straight_cost==0)
   {
       x=1;
   }

   if(x!=1)
   {
             int i=a_star_best_node(l);

             a_star_travers_agent(i);
   }

    }
}

// find best node of a star

int a_star_best_node(int l)
{
   int min=99999;
   int second_min=999999;
   int best=0,second_best=0,m,v,i;
   int gn=0,gnn=0;

// find first best node

   for(i=1;i<=n;i++)
  {
       if((a[l][i]!=0)&&(visited[i]==0))
          {
              v=g[l]+a[l][i];
              m=states[i].straight_cost+v;

              if(m<min)
              {
                   min=m;
                   best=i;
                   gn=v;
              }
          }
   }

   // add path cost of node : g(n)

 g[best]=gn;

// check with a_star_second_best of node

          if(a_star_second_best.value<min)
          {
              int r=a_star_second_best.node;

              a_star_second_best.node=best;
              a_star_second_best.value=min;

              a_star_travers_agent(r);

          }

// find second best node

    else
        {
    for(i=1;i<=n;i++)
    {
       if((a[l][i]!=0)&&(visited[i]==0))
          {
              v=g[l]+a[l][i];
              m=states[i].straight_cost+v;

           if((m<second_min)&&(m>min))
              {
                   second_min=m;
                   second_best=i;
                   gnn=v;
              }

              }
          }

  g[second_best]=gnn;

  a_star_second_best.node=second_best;
  a_star_second_best.value=second_min;

        }

  return best;
}
