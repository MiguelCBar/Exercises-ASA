#include <iostream>
#include <vector>
using namespace std;

int knapsack(vector<vector<int>> &matrix, int lines, int columns) {

    for (int i = 1; i <= lines; i++) {
        for (int j = i; j <= columns; j++) {

            int maxCut = matrix[i][j];

            for (int cutX = 1; cutX <= j/2; cutX++) 
                maxCut = max(maxCut, matrix[i][cutX] + matrix[i][j - cutX]);

            for (int cutY = 1; cutY <= i/2; cutY++) 
                maxCut = max(maxCut, matrix[cutY][j] + matrix[i - cutY][j]);

            matrix[i][j] = maxCut;
        
            if (j <= lines)
                matrix[j][i] = matrix[i][j];
        }
    }
    return matrix[lines][columns];
}

int main() {

    int maxLines, maxColumns, numberPieces, x, y, value;

    scanf("%d %d", &maxLines, &maxColumns);

    // set an horizontal matrix
    if (maxLines > maxColumns) {
        int aux = maxLines;
        maxLines = maxColumns;
        maxColumns = aux;
    }
    
    // initialize null matrix
    vector<std::vector<int>> matrix(maxLines + 1, std::vector<int>(maxColumns + 1, 0));

    scanf("%d", &numberPieces);
    for(int i = 0; i < numberPieces; i++) {
        scanf("%d %d %d", &x, &y, &value);

        if(x <= maxLines && y <= maxColumns) 
            matrix[x][y] = value;

        if(y <= maxLines && x <= maxColumns) 
            matrix[y][x] = value;
    }

    printf("%d\n", knapsack(matrix, maxLines, maxColumns));
    
    return 0;
}