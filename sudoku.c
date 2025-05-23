#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j, k;
    int marked[10];
    for(i = 0; i < 9; i++) 
    {
      for(k = 0; k < 10; k++) marked[k] = 0;
      for(j = 0; j < 9; j++)
      {
        int num = n->sudo[i][j];
        if (num != 0)
        {
          if(marked[num] == 1) return 0;
          marked[num] = 1;
        }
      }
    }
    for(j = 0; j < 9; j++)
    {
      for(k = 0; k < 10; k++) marked[k] = 0;
      for(i = 0; i < 9; i++)
      {
        int num = n->sudo[i][j];
        if(num != 0)
        {
          if(marked[num] == 1) return 0;
          marked[num] = 1;
        }

      }
      
    }
     for(int block_i = 0; block_i < 3; block_i++)
     {
       for(int block_j = 0; block_j < 3; block_j++)
       {
        for(k = 0; k < 10; k++) marked[k] = 0;
        for(i = 0; i < 3; i++)
        {
           for(j = 0; j < 3; j++)
           {
            int row = block_i * 3 + i;
            int col = block_j * 3 + j;
            int num = n->sudo[row][col];
            if(num != 0)
            {
              if(marked[num] == 1) return 0; 
              marked[num] = 1;
            }
           }
        }
       }
     }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j, k;
    for(i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          for(k = 1; k <= 9; k++)
          {
            Node* new_node = (Node*) malloc(sizeof(Node));
            for(int p = 0; p < 9; p++)
            {
              for(int q = 0; q < 9; q++)
              {
                new_node->sudo[p][q] = n->sudo[p][q];
              }
            }
             new_node->sudo[i][j] = k;
             if(is_valid(new_node))
             {
               pushBack(list, new_node);
             }
             else free(new_node);
          }
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
    int i, j;
    for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
      {
         if(n->sudo[i][j] == 0)
         {
          return 0;
         }
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont) {
    *cont = 0;
    Stack* S = createStack();
    push(S, initial);
    
    while(!is_empty(S)) {
        (*cont)++;
        Node* current = top(S);
        pop(S);
    
        if(is_final(current)) {
            while(!is_empty(S)) {
                Node* temp = top(S);
                pop(S);
                free(temp);
            }
            free(S);
            return current;
        }
        
        List* adj_nodes = get_adj_nodes(current);
        Node* adj_node = first(adj_nodes);
        while(adj_node != NULL) {
            push(S, adj_node);
            adj_node = next(adj_nodes);
        }
        free(adj_nodes);
        free(current);
    }
    
    free(S);
    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/