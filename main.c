#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 1; //解の数をカウント

void print_border(int n);
void print_queen(int q[], int n);

// 盤面の全パターンを生成する処理
void set_queen(int q[], int, int);

// 2つの位置のクイーンが互いに取り合う位置か判定
int safe(int q[], int i, int j);

// 盤面にあるクイーンが互いに取り合う位置にあるか判定
int safe_all(int q[], int n);

// 任意のnでのNクイーン問題を解く
int solve(int n);

//自作関数: Nクイーン問題を満たす盤面を表示
void plt(int q[], n);

//自作関数：改善したアルゴリズムを格納した関数
void Rset_queen(int q[], int m, int n, int w);
int Rsolve(int n);

void plt(int q[], int n){
  
  for (int j = 0; j < n; j++) {
        printf("+-");
      }
      printf("+\n");

      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          if (q[k] == j) {
            printf("|Q");
          } else {
            printf("| ");
          };
        }
        printf("|\n");
      }

      for (int j = 0; j < n; j++) {
        printf("+-");
      }
      printf("+\n");
}


// ある盤面にあるクイーンがお互いに取り合う関係にあるか判定
// mはqが確定した最大要素インデックスを示す
int safe_all(int q[], int m) {

  for (int i = 0; i < m + 1; i++) {
    for (int j = i + 1; j < m + 1; j++) {
      if (safe(q, i, j) == -1) {
        return -1;
      }
    }
  }

  return 1;
}

int safe(int q[], int i, int j) {

  if (q[i] == q[j] || abs(q[i] - q[j]) == abs(i - j)) {
    return -1;
  }

  return 1;
}

// 引数で指定されたnクイーン問題を解く関数
int solve(int n) {
  int *q;
  q = malloc(sizeof(int) * n); // 盤面を表す領域の割り当て

  set_queen(q, 0, n);

  return 0;
}


void set_queen(int q[], int m, int n) {
  int i;

  if (m == n) {
    // 表示
    // plt(q, n);
    // print_queen(q, n);
    return;
  }
  
  for (i = 0; i < n; i++) {
    q[m] = i;
    
    //バックトラック処理
    if (safe_all(q, m) == -1) {
        continue;
    }
    
    set_queen(q, m + 1, n);
  }
  
}


int Rsolve(int n) {
  int *q;
  int w = n*0.5; //nの半分の値をとる定数
  
  q = malloc(sizeof(int) * n); // 盤面を表す領域の割り当て
  
  Rset_queen(q, 0, n, w);

  return 0;
}



//改善後
void Rset_queen(int q[], int m, int n, int w) {
  int i;
 

  if (m == n) {
    // 表示
    plt(q, n);
    // print_queen(q, n);
    
    return;
  }

  
  for (i = 0; i < n; i++) {
    int idx = 0;
    
    q[m] = i;

    //改善策(先に同じ行にqueenが重なっていないか探索)
    if(m > w){
      for(int k = m - 1; k > -1; k--){
        if(q[k] == i){idx = 1; break;}
      }
      if(idx){continue;}
    }
    
    //バックトラック処理
    if (safe_all(q, m) == -1) {
      continue;
    }

    Rset_queen(q, m + 1, n, w);
  }
  
}

// 盤面を表示
void print_queen(int q[], int n) {
  // 課題1を流用
  printf("[queenの配置]\n");
  for (int i = 0; i < n; i++) {
    printf("%d列%d行 ", i + 1, q[i] + 1);
  }
  printf("\n");
}

// main関数
int main(int argc, char **argv) {
  int m;
  int n;
  int start, end;

  // Nを入力
  printf("Input a integer(>=1): ");
  scanf("%d", &n);

  if (n <= 0) // 0以下でないかチェック
  {
    printf("N must be a integer than 1\n");
    return 0;
  }

  //改善前
  
  // start = clock();
  // m = solve(n);
  // end = clock();
  // printf("改善前: %f sec\n", ((double)(end - start) / CLOCKS_PER_SEC));


  //改善後
  
  start = clock();
  m = Rsolve(n);
  end = clock();
  printf("改善後: %f sec\n", ((double)(end - start) / CLOCKS_PER_SEC));

  return 0;
}
