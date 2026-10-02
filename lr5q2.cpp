#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void freeGraph(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(g[i]);
    }
    free(g);
}
int** createGraph(int* n) {
    int** g;
    int i;
    printf("Введите количество вершин графа ");
    do {
        scanf_s("%d", n);
        if ((*n) <= 0) {
            printf("введите положительное ненулевое число! ");
        }
    } while ((*n) <= 0);

    g = (int**)malloc((*n) * sizeof(int*));

    for (i = 0; i < (*n); i++) {
        g[i] = (int*)malloc((*n) * sizeof(int));
    }

    return g;
}

void printGraph(int** g, int n) {
    int i, j;

    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    printf("\nГраф: \n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", g[i][j]);
        }

        printf("\n");
    }
}

void randGraph(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            g[i][j] = rand() % 2;
        }
    }
}

int rcount(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return 0;
    }

    int r = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1) {
                r++;
            }
        }
    }
    return r;
}

void typevertex(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        int t1 = 0; 
        int t2 = 0; 

        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1) t1++;
            if (g[j][i] == 1) t2++;
        }

        if (t1 == 0 && t2 == 0) {
            printf("Вершина %d - изолированная\n", i + 1);
        }
        else if (t1 == 1 && t2 == 1) {
            printf("Вершина %d - концевая\n", i + 1);
        }
        else if (t1 == n - 1 && t2 == n - 1 && n > 1) {
            printf("Вершина %d - доминирующая\n", i + 1);
        }
    }
}



int** createInc(int** g, int n, int* m) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        *m = 0;
        return NULL;
    }

    *m = rcount(g, n); 

    int** inc = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        inc[i] = (int*)calloc(*m, sizeof(int)); 
    }

    int edgeIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && g[i][j] == 1) {
                inc[i][edgeIndex] = -1; 
                inc[j][edgeIndex] = 1;  
                edgeIndex++;
            }
        }
    }

    return inc;
}

void printInc(int** inc, int n, int m) {
    if (inc == NULL || m == 0) {
        printf("Матрица инцидентности пуста\n");
        return;
    }

    printf("Матрица инцидентности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%2d ", inc[i][j]);
        }
        printf("\n");
    }
}

int rcountInc(int** g, int n) {
    if (g == NULL) {
        printf("Граф ещё не был создан\n");
        return 0;
    }

    int r = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1) {
                r++;
            }
        }
    }
    return r;
}

void typevertexInc(int** inc, int n, int m) {
    if (inc == NULL) {
        printf("Матрица инцидентности ещё не была создана\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        int t1 = 0;
        int t2 = 0;
        for (int j = 0; j < m; j++) {
            if (inc[i][j] == -1) t1++; 
            if (inc[i][j] == 1)  t2++; 
        }

        if (t1 == 0 && t2 == 0) {
            printf("Вершина %d - изолированная\n", i + 1);
        }
        if (t1 == 1 && t2 == 1) {
            printf("Вершина %d - концевая\n", i + 1);
        }
        if (t1 == n - 1 && t2 == n - 1 && n > 1) {
            printf("Вершина %d - доминирующая\n", i + 1);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int** g = NULL;
    int** inc = NULL;
    int n = 0;
    int m = 0;
    int r;
    int choice;
    while (1) {
        printf("\nвыберите действие и введите его номер:\n 1 - создать ориентированный граф\n 2 - создать матрицу инцидентности ориентированного графа\n 3 - задать случайные связи вершин графа\n 4 - вывести граф\n 5 - вывести матрицу инцидентности\n 6 - определить размер графа(количество рёбер) по матрице смежности\n 7 - определить размер графа(количество рёбер) по матрице инцидентности\n 8 - определить типы вершин по матрице смежности\n 9 - определить типы вершин по матрице инцидентности\n");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1: g = createGraph(&n); break;
        case 2:
            if (g != NULL) freeGraph(g, n);
            if (inc != NULL) freeGraph(inc, n);
            g = createGraph(&n);
            inc = NULL;
            break;
        case 3:
            randGraph(g, n);
            if (inc != NULL) {
                freeGraph(inc, n);
                inc = NULL;
            }
            inc = createInc(g, n, &m);
            printGraph(g, n);
            printInc(inc, n, m);
            break;
        case 4: printGraph(g, n); break;
        case 5:
            if (inc != NULL) freeGraph(inc, n);
            inc = createInc(g, n, &m);
            printInc(inc, n, m);
            break;
        case 6: r = rcount(g, n); printf("%d", r); break;
        case 7: r = rcountInc(g, n); printf("%d", r); break;
        case 8: typevertex(g, n); break;
        case 9: typevertexInc(inc, n, m); break;
        case 10:
            freeGraph(g, n);
            freeGraph(inc, n);
            return 0;
        default: break;
        }
    }
}
