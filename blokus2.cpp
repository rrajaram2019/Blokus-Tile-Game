#include <iostream>
#include <string>
#include <vector>
// allowed includes
// tuple, utility, vector, map, set, unordered_map,
// unordered_set, algorithm
using std::cin;
using std::cout;
using std::string;
using std::vector;

int number_of_play = 0;

typedef int TileID;

class Tile {
  // common interface. required.
 public:
  vector<string> tile;
  TileID Tilenumber;
  int weight;

  // print out tile in tilebox format
  void show() const {
    for (int s = 0; s < this->tile.size(); s++) {
      cout << this->tile.at(s) << '\n';
    }
  }

  vector<string> rotated(vector<string> g) {
    vector<string> out = g;
    {
      for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++)
          out.at(g.size() - 1 - j).at(i) = g.at(i).at(j);
      }
    }
    out = upperleft(out);
    return out;
  }

  void rotate() {
    tile = rotated(tile);
  }

  void flipud() {
    vector<string> flipud;
    flipud.clear();
    for (int v = this->tile.size() - 1; v >= 0; v--) {
      flipud.push_back(this->tile.at(v));
    }
    flipud = upperleft(flipud);
    this->tile = flipud;
  }

  void fliplr() {
    vector<string> flip;
    flip.clear();
    string flipbin;
    for (int d = 0; d < this->tile.size(); d++) {
      for (int f = this->tile.size() - 1; f >= 0; f--) {
        flipbin += this->tile.at(d).at(f);
      }
      flip.push_back(flipbin);
      flipbin.clear();
    }
    flip = upperleft(flip);
    this->tile = flip;
  }

  vector<string> upperleft(vector<string> g) {
    int n, x = -1, y = -1, X = -1, Y = -1;
    int gsize = g.size();
    vector<string> out;
    for (int r = 0; r < gsize; r++) {
      for (int c = 0; c < gsize; c++) {
        if (g.at(r).at(c) == '*' && x == -1)
          x = r;
      }
    }
    for (int c = 0; c < gsize; c++) {
      for (int r = 0; r < gsize; r++) {
        if (g.at(r).at(c) == '*' && y == -1)
          y = c;
      }
    }
    for (int r = gsize - 1; r >= 0; r--) {
      for (int c = gsize - 1; c >= 0; c--) {
        if (g.at(r).at(c) == '*' && X == -1)
          X = r;
      }
    }
    for (int c = gsize - 1; c >= 0; c--) {
      for (int r = gsize - 1; r >= 0; r--) {
        if (g.at(r).at(c) == '*' && Y == -1)
          Y = c;
      }
    }
    if ((X - x + 1) > (Y - y + 1)) {
      n = (X - x + 1);
    } else {
      n = (Y - y + 1);
    }
    for (int r = 0; r < n; r++) {
      string s;
      for (int c = 0; c < n; c++) {
        s.push_back('.');
      }
      out.push_back(s);
    }
    for (int r = 0; r < n && (r + x) < gsize; r++) {
      for (int c = 0; c < n && (c + y) < gsize; c++) {
        //  cout<< g.at(x + r).at(y + c)<<"   g.at(x + r).at(y + c) \n";
        out.at(r).at(c) = g.at(x + r).at(y + c);
      }
    }
    return out;
  }
};


class Blokus {
  // common interface. required.
  // collection of Tiles
  vector<string> board;
  vector<Tile> tile_storage;
  int TheTileIDCounter;
  vector<int> Xx;
  vector<int> Yy;
  vector<int> vec_played_ID;
  vector<int> vec_played_Rindex;
  vector<int> vec_played_Cindex;

 public:
  void reset() {
    board.clear();
    tile_storage.clear();
    cout << "game reset\n";
  }


  void create_piece() {  // how to get a function to take inputs from the user
    Tile t;
    int n;
    bool invalid = false, ansI = true, ansD = true, ansDis = true;
    cin >> n;
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      if (s.size() != n) {
        invalid = true;
      } else {
        t.tile.push_back(s);
      }
    }
    if (invalid) {
      cout << "invalid tile\n";
    } else {
      t.tile = t.upperleft(t.tile);
      ansI = InVal(t.tile);
      ansD = Dup(t.tile);
      ansDis = Dis(t.tile);  // Dis(t.tile);
    }
    // not disconnected
    if (ansI && ansDis && ansD && !invalid) {
      t.Tilenumber = 100 + tile_storage.size();
      find_Size(t.tile);
      tile_storage.push_back(t);
      cout << "created tile " << t.Tilenumber << '\n';
    }
  }

  bool Dup(vector <string> in) {
    Tile t;
    bool duplicate = false;
    bool ans = true;
    int x;
    for (x = 0; x < tile_storage.size(); x++) {
      if (in == t.upperleft(tile_storage.at(x).tile))
        duplicate = true;
      if (in == t.upperleft(rotated(tile_storage.at(x).tile)))
        duplicate = true;
      if (in == t.upperleft(rotated(rotated(tile_storage.at(x).tile))))
        duplicate = true;
      if (in == t.upperleft(rotated(rotated(rotated(tile_storage.at(x).tile)))))
        duplicate = true;
      if (in == t.upperleft(fliplred(tile_storage.at(x).tile)))
        duplicate = true;
      if (in == t.upperleft(fliplred(rotated((tile_storage.at(x).tile)))))
        duplicate = true;
      if (in == t.upperleft(fliplred
                            (rotated(rotated((tile_storage.at(x).tile))))))
        duplicate = true;
      if (in ==
          t.upperleft(fliplred(rotated
                               (rotated(rotated((tile_storage.at(x).tile)))))))
        duplicate = true;
      if (duplicate)
        break;
    }
    x += 100;
    if (duplicate) {
      cout << "duplicate of " << x << " discarded\n";
      ans = false;
    }
    return ans;
  }



  vector<string> reduce(vector<string> g) {
    vector<string> out;
    for (int i = 0; i < g.size(); i++) {
      int j = 0;
      while (j < g.size()) {
        if (g.at(i).at(j) == '.') {
          j++;
        } else {
          break;
        }
      }
      if (j == g.size())
        g.at(i).clear();
    }
    for (int i = 0; i < g.size(); i++) {
      if (g.at(i).size() != 0)
        out.push_back(g.at(i));
    }
    for (int c = 0; c < out.at(0).size(); c++) {
      int r = 0;
      while (r < out.size()) {
        if (out.at(r).at(c) == '.') {
          r++;
        } else {
          break;
        }
      }
      if (r == out.size()) {
        for (int k = 0; k < out.size(); k++)
          out.at(k).erase(c);
      }
    }
    return out;
  }

  vector<string> reshape(vector<string> g, vector<string> temp) {  // GOOD
    vector<string> out = g;
    int r = 0, c = 0;
    for (int i = 0; i < out.size(); i++) {
      for (int j = 0; j < out.at(i).size(); j++) {
        if (out.at(i).at(j) == '*' && r == 0 && c == 0) {
          r = i;
          c = j;
        }
      }
    }
    if (c - 1 >= 0) {
      if (out.at(r).at(c - 1) == '.')  // out.at(r-1).at(c-1)=='*'){
        c = c - 1;
    }
    for (int i = 0; i < temp.size(); i++) {
      for (int j = 0; j < temp.at(i).size(); j++) {
        out.at(r + i).at(c + j) = temp.at(i).at(j);
      }
    }
    return out;
  }

  vector<string> rotated(vector<string> g) {
    vector<string> out = g;
    {
      for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++)
          out.at(g.size() - 1 - j).at(i) = g.at(i).at(j);
      }
    }
    return out;
  }

  vector<string> fliplred(vector<string> g) {
    int gsize = g.size();
    vector<string> temp = g;
    vector<string> out = temp;
    for (int i = 0; i < temp.size(); i++) {
      for (int j = 0; j < temp.at(i).size(); j++) {
        out.at(i).at(temp.at(i).size() - 1 - j) = temp.at(i).at(j);
      }
    }
    if (temp.size() == gsize && temp.at(0).size() == gsize) {
      return out;
    }
    return out;
  }

  vector<string> flipuded(vector<string> g) {
    int gsize = g.size();
    vector<string> temp = g;
    vector<string> out = temp;
    for (int i = 0; i < temp.size(); i++) {
      for (int j = 0; j < temp.at(i).size(); j++) {
        out.at(temp.size() - 1 - i).at(j) = temp.at(i).at(j);
      }
    }
    if (temp.size() == gsize && temp.at(0).size() == gsize)
      return out;
    return out;
  }

  bool InVal(vector<string> in) {
    bool ans = true;
    bool invalid = false;  // true if invalid
    // bool diagAndLone = true;  // true if invalid bc does not connection
    // bool duplicate = false;  // true if title is exactly repeated in board
    // bool Lone = false;  // true if there is only one cell occuppied
    // bool connected = true;
//  INVALID OUTPUT
    int k = 0;
    for (int i = 0; i < in.size(); i++) {
      for (int j = 0; j < in.size(); j++) {
        if (in.at(i).at(j) != '*' && in.at(i).at(j) != '.')
          invalid = true;
        if (in.at(i).at(j) == '*')
          k++;
      }
    }
    if (k == 0 || invalid) {
      cout << "invalid tile\n";
      ans = false;
    }
    return ans;
  }

  bool Dis(vector<string> in) {
    if (in.size() == 1) {
      if (in.at(0).at(0) == '*') {
        return true;
      }
    }
    int ind = 0;
    bool connected = true;
    int row = in.size(), col = in.size();
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '*') {
          in.at(i).at(j) = '#';
          ind = j;
          break;
        }
      }

      if (in.at(i).at(ind) == '#')
        break;
    }

    for (int i = 0; i < row ; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < row) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (j + 1 < row) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }


          if (i - 1 > 0) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }



    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }

    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '#') {
          if (i + 1 < col) {
            if (in.at(i + 1).at(j) == '*')
              in.at(i + 1).at(j) = '#';
          }
          if (i - 1 > -1) {
            if (in.at(i - 1).at(j) == '*')
              in.at(i - 1).at(j) = '#';
          }
          if (j + 1 < col) {
            if (in.at(i).at(j + 1) == '*')
              in.at(i).at(j + 1) = '#';
          }
          if (j - 1 > -1) {
            if (in.at(i).at(j - 1) == '*')
              in.at(i).at(j - 1) = '#';
          }
        }
      }
    }
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (in.at(i).at(j) == '*') {
          cout << "disconnected tile discarded\n";
          return false;
        }
      }
    }
    for (int c = 0; c < row; c++) {
      for (int d = 0; d < col; d++) {
        if (in.at(c).at(d) == '#')
          in.at(c).at(d) = '*';
      }
    }
    return true;
  }
  /* bool Dis(vector <string> in) {
   int countstar = 0;
   int size_row = in.size();
   int last_row = size_row - 1;
   int size_col = in.at(0).length();
   int last_col = size_row - 1;
   vector <string> out = in;

   for (int row = 0; row < in.size(); row++) {
     for (int col = 0; col < in.size(); col++) {
        if (in.at(row).at(col) == '*') {
         // first row first col
         if (row == 0 and col == 0) {
           if (in.at(row).at(col + 1) or in.at(row + 1).at(col) == '*') {
             in.at(0).at(0) == '#';
           }
         }
         if (row == last_row and col == 0) {  // last row first col
           if (in.at(row).at(col + 1) or in.at(row - 1).at(col) == '*') {
             in.at(row).at(col) == '#';
           }
         }  if (row == 0 and col == last_col) {  // first row last col
           if (in.at(row).at(col - 1) or in.at(row + 1).at(col) == '*') {
             in.at(row).at(col) == '#';
           }  // last row last col
         } if (row == last_row and col == last_col) {
           if (in.at(row).at(col - 1)
               or in.at(row - 1).at(col) == '*') {
             in.at(row).at(col) == '#';
           }
         }
        for (int a = 1; a < last_row - 1; a++) {
           if (in.at(a).at(0) == '*') {
             if (in.at(a - 1).at(0) == '*'
                 or in.at(a + 1).at(0) == '*'
                 or in.at(a).at(1) == '*') {
               in.at(a).at(0) == '#';
             }
           }
         }
         for (int b = 1; b < last_row - 1; b++) {
           if (in.at(b).at(last_col) == '*') {
             if (in.at(b - 1).at(last_col) == '*'
                 or in.at(b + 1).at(last_col) == '*'
                 or in.at(b).at(last_col - 1) == '*') {
               in.at(b).at(last_col) == '#';
             }
           }
         }
         for (int c = 1; c < last_col; c++) {
           if (in.at(0).at(c) == '*') {
             if (in.at(0).at(c - 1) == '*'
                 or in.at(0).at(c + 1) == '*'
                 or in.at(1).at(c) == '*') {
               in.at(0).at(c) == '*';
             }
           }
         }
         for (int d = 1; d < last_col; d++) {
           if (in.at(last_row).at(d) == '*') {
             if (in.at(last_row).at(d - 1) == '*'
                 or in.at(last_row).at(d + 1) == '*'
                 or in.at(last_row - 1).at(d) == '*') {
               in.at(last_row).at(d) == '#';
             }
           }
         }
         for (int rr = 1; rr < last_col - 1; rr++) {
           for (int cc = 1; cc < last_row - 1; cc++) {
             if (in.at(rr).at(cc) == '*') {
               if (in.at(rr - 1).at(cc) == '*'
                   or in.at(rr + 1).at(cc) == '*'
                   or in.at(rr).at(cc - 1) == '*'
                   or in.at(rr).at(cc + 1) == '*') {
                 in.at(rr).at(cc) == '#';
               }
             }
           }
         }
          }

     }
   }

   // check if anything is a *

   for (int row = 0; row < in.size(); row++) {
      for (int col = 0; col < in.size(); col++) {
       if (in.at(row).at(col) == '*') {
         countstar = countstar + 1;
       }
     }
   }

   if (countstar == 0) {
     // it is not discconected
     return true;

   } else {
     return false;
   }
  } */
  Tile* find_tile(TileID number) {
    number = number - 100;
    return &tile_storage.at(number);
  }

  void show_tiles() const {
    cout << "tile inventory" << '\n';
    for (int x = 0; x < tile_storage.size(); x++) {
      cout << tile_storage.at(x).Tilenumber << '\n';
      for (int j = 0; j < tile_storage.at(x).tile.size(); j++) {
        cout << tile_storage.at(x).tile.at(j) << '\n';
      }
    }
  }

  void show_board() const {
    for (int y = 0; y < board.size(); y++) {
      for (int z = 0; z < board.at(y).size(); z++) {
        cout << (board.at(y).at(z));
      }
      cout << '\n';
    }
  }

  void find_Size(vector<string> g) {
    int n, x = -1, y = -1, X = -1, Y = -1;
    int gsize = g.size();
    vector<string> out;
    for (int r = 0; r < gsize; r++) {
      for (int c = 0; c < gsize; c++) {
        if (g.at(r).at(c) == '*' && x == -1)
          x = r;
      }
    }
    for (int c = 0; c < gsize; c++) {
      for (int r = 0; r < gsize; r++) {
        if (g.at(r).at(c) == '*' && y == -1)
          y = c;
      }
    }
    for (int r = gsize - 1; r >= 0; r--) {
      for (int c = gsize - 1; c >= 0; c--) {
        if (g.at(r).at(c) == '*' && X == -1)
          X = r;
      }
    }
    for (int c = gsize - 1; c >= 0; c--) {
      for (int r = gsize - 1; r >= 0; r--) {
        if (g.at(r).at(c) == '*' && Y == -1)
          Y = c;
      }
    }
    Xx.push_back(X - x + 1);
    Yy.push_back(Y - y + 1);
  }

  bool Badoverlap(vector<string> in, int intx, int inty) {
    bool ans = false;
    for (int i = 0; i < in.size(); i++) {
      for (int j = 0; j < in.size(); j++) {
        //  char temp= in.at(i-intx).at(j-inty);
        if (in.at(i).at(j) == '*' && board.at(i + intx).at(j + inty) == '*')
          return true;
      }
    }
    return ans;
  }

  void play_tile(TileID input, int intx, int inty) {
    if (input < 100) {
      cout << input << " not played\n";
    } else {
      vector<string> in = tile_storage.at(input - 100).tile;
      if (intx > (board.size() - 1) ||
          inty > board.size() - 1 || intx < 0 || inty < 0) {
        cout << input << " not played\n";
      } else if ( (Xx.at(input - 100) + intx) > board.size()
                  || (Yy.at(input - 100) + inty) > board.size() ) {
        cout << input << " not played\n";
      } else {
        // cout << " Made it here\n";
        int r = in.size() * in.size();
        int k = 0;
        bool ans = Badoverlap(in, intx, inty);
        // cout << " Made it here 2 and ans is " << ans << "\n";
        if (ans == false) {  // if it is not a bad overlap
          //  cout << " Made it here 3\n";
          for (int i = 0; i < in.size(); i++) {
            //  cout << " Made it here 4\n";
            for (int j = 0; j < in.size(); j++) {
              //  if (i >= intx && j >= inty && k<r) {
              //  cout << "played 2" << '\n';
              //  cout<< in.at(i-intx).at(j-inty) <<'\n';
              //  k++;
              if (in.at(i).at(j) == '*')
                board.at(i + intx).at(j + inty) = in.at(i).at(j);
              //  cout << " Made it here 5\n";
            }
          }
          vec_played_ID.push_back(input - 100);
          vec_played_Rindex.push_back(Xx.at(input - 100) + intx - 1);
          vec_played_Cindex.push_back(Yy.at(input - 100) + inty - 1);
          cout << "played " << input << '\n';
        } else {
          cout << input << " not played\n";
        }
      }
      //  for (int i = 0; i < board.size(); i++) {
      //   for (int j = 0; j < board.size(); j++)
      //     cout << board.at(i).at(j);
      //   cout << '\n';
      // }
    }
  }

  void set_size(int num) {
    vector<string> newboard;
    if (board.empty()) {
      for (int r = 0; r < num; r++) {
        string s;
        for (int c = 0; c < num; c++) {
          s.push_back('.');
        }
        board.push_back(s);
      }
    } else if (num > board.size()) {
      int r = 0;
      while (r < board.size()) {
        int c = board.size();
        while (c < num) {
          board.at(r).push_back('.');
          c++;
        }
        r++;
      }
      string s;
      while (s.size() != num)
        s.push_back('.');
      while (board.size() < num)
        board.push_back(s);
    } else if (num < board.size()) {
      for (int k = 0; k < vec_played_Rindex.size(); k++) {
        if (vec_played_Rindex.at(k) > num - 1 ||
            vec_played_Cindex.at(k) > num - 1 ) {
          int ID = vec_played_ID.at(k);
          int StartM = vec_played_Rindex.at(k) - Xx.at(ID) + 1;
          int StartN = vec_played_Cindex.at(k) - Yy.at(ID) + 1;
          for (int m = 0; m < Xx.at(ID); m++) {
            for (int n = 0; n < Yy.at(ID); n++) {
              if (tile_storage.at(ID).tile.at(m).at(n) == '*'
                  && board.size() > (StartM + m)
                  && board.size() > (StartN + n) )
                board.at(StartM + m).at(StartN + n) = '.';
            }
          }
        }
      }
      for (int i = 0; i < num; i++) {
        string s;
        for (int j = 0; j < num; j++) {  // Need to find if its in a tile
          s.push_back(board.at(i).at(j));
        }
        newboard.push_back(s);
      }
      board = newboard;
    } else if (num = board.size()) {
      board = board;
    }
  }
};




// MAIN. Do not change the below.


int main() {
  string command;
  Blokus b;

  while (true) {
    cin >> command;
    if (command == "quit")  {
      break;
    } else if (command == "//") {
      getline(cin, command);
    } else if (command == "board") {
      b.show_board();
    } else if (command == "create") {
      b.create_piece();
    } else if (command == "reset") {
      b.reset();
    } else if (command == "show") {
      string arg;
      cin >> arg;
      if (arg == "tiles") {
        b.show_tiles();
      } else {
        auto g = b.find_tile(std::stoi(arg));
        g->show();
      }
    } else if (command == "resize") {
      int newsize;
      cin >> newsize;
      b.set_size(newsize);
      b.show_board();
    } else if (command == "play") {
      TileID id;
      int row, col;
      cin >> id >> row >> col;
      b.play_tile(id, row, col);
    } else if (command == "rotate") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->rotate();
      cout << "rotated " << id << "\n";
      g->show();
    } else if (command == "fliplr") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->fliplr();
      cout << "fliplr " << id << "\n";
      g->show();
    } else if (command == "flipud") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->flipud();
      cout << "flipud " << id << "\n";
      g->show();
    } else {
      cout << "command not understood.\n";
    }
  }
  cout << "Goodbye\n";
  return 0;
}
