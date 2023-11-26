#include <bits/stdc++.h>
using namespace std;

void shuffle_vector(std::vector<int>& vec) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(vec.begin(), vec.end(), gen);
}

int count_visited_neighbours(int x, int y, vector<vector<int>>& maze) {
  int N = maze.size();
  int M = maze[0].size();
  vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  int count = 0;
  for (int k = 0; k < 4; ++k) {
    int nx = x + dirs[k][0];
    int ny = y + dirs[k][1];
    if (nx < 0 || nx >= N || ny < 0 || ny >= M) {
      continue;
    }
    if (maze[nx][ny] == 0) {
      count++;
    }
  }
  return count;
}

void generate_maze_dfs(int x, int y, vector<vector<int>>& maze) {
  int N = maze.size();
  int M = maze[0].size();
  if (x < 0 || x >= N || y < 0 || y >= M) {
    return;
  }
  if (maze[x][y] == 0) {
    return;
  }
  if (count_visited_neighbours(x, y, maze) > 1) {
    return;
  }
  maze[x][y] = 0;
  vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  vector<int> visit_order = {0, 1, 2, 3};
  shuffle_vector(visit_order);

  for (int k = 0; k < 4; ++k) {
    int nx = x + dirs[visit_order[k]][0];
    int ny = y + dirs[visit_order[k]][1];
    generate_maze_dfs(nx, ny, maze);
  }
}
vector<vector<int>> generate_maze(int N, int M) {
  vector<vector<int>> maze(N, vector<int>(M, 1));
  generate_maze_dfs(0, 0, maze);
  return maze;
}

bool generate_solution_dfs(int x, int y, vector<vector<int>>& maze,
                           vector<vector<int>>& solution) {
  int N = maze.size();
  int M = maze[0].size();
  if (x < 0 || x >= N || y < 0 || y >= M) {
    return false;
  }
  if (maze[x][y] == 1) {
    return false;
  }
  if (solution[x][y] == 1) {
    return false;
  }
  if (x == N - 1 && y == M - 1) {
    solution[x][y] = 1;
    return true;
  }
  solution[x][y] = 1;
  vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  for (int k = 0; k < 4; ++k) {
    int nx = x + dirs[k][0];
    int ny = y + dirs[k][1];
    if (generate_solution_dfs(nx, ny, maze, solution)) {
      return true;
    }
  }
  solution[x][y] = 0;
  return false;
}

vector<vector<int>> generate_solution(vector<vector<int>>& maze) {
  int N = maze.size();
  int M = maze[0].size();
  vector<vector<int>> solution(N, vector<int>(M, 0));
  generate_solution_dfs(0, 0, maze, solution);
  return solution;
}

int main() {
  int N, M;
  cout << "Number of Rows in Maze (Suggested 10): ";
  cin >> N;
  cout << "Number of Columns in Maze (Suggested 10): ";
  cin >> M;
  vector<vector<int>> maze = generate_maze(N, M);
  cout << "Maze: 1 Represents Wall and 0 Represents Path" << endl;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cout << maze[i][j] ;
      cout << " ";
    }
    cout << endl;
  }
  cout << endl;

  cout << "Solution: Path cells marked with a + represent the solution to the maze" << endl;
  vector<vector<int>> solution = generate_solution(maze);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if(solution[i][j] == 1) {
        cout << "+";
      } else {
        cout << maze[i][j];
      }
      cout << " ";
    }
    cout << endl;
  }
  return 0;
}